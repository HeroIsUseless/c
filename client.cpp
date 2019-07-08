// -*-c++-*-

/***************************************************************************
 client.cpp  -  A basic client that connects to
 the server
 -------------------
 begin                : 27-DEC-2001
 copyright            : (C) 2001 by The RoboCup Soccer Server
 Maintenance Group.
 email                : sserver-admin@lists.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU LGPL as published by the Free Software  *
 *   Foundation; either version 3 of the License, or (at your option) any  *
 *   later version.                                                        *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "compress.h"

#include <rcssbase/net/socketstreambuf.hpp>
#include <rcssbase/net/udpsocket.hpp>
#include <rcssbase/gzip/gzstream.hpp>

#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include <strstream>
#endif
#include <iostream>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string.h>

#ifdef __CYGWIN__
// cygwin is not win32
#elif defined(_WIN32) || defined(__WIN32__) || defined (WIN32)
#  define RCSS_WIN
#  include <winsock2.h>
#endif

#ifndef RCSS_WIN
#  include <unistd.h> // select()
#  include <sys/select.h> // select()
#  include <sys/time.h> // select()
#  include <sys/types.h> // select()
#endif

int iPlayerId = 0;
int currentCycle = 0;
int lastCycle = 0;
int kickWait = 0;
int turnToSeeGoal = 0;
int iSide = 0;//1:left;2:right

//????????????????
void poly2vector(double dLen, double dAngle, double &dX, double &dY) {
	
}

class Client {
private:
	rcss::net::Addr M_dest;
	rcss::net::UDPSocket M_socket;
	rcss::net::SocketStreamBuf * M_socket_buf;
	rcss::gz::gzstreambuf * M_gz_buf;
	std::ostream * M_transport;
	int M_comp_level;
	bool M_clean_cycle;

#ifdef HAVE_LIBZ
	Decompressor M_decomp;
#endif

	Client();
	Client(const Client &);
	Client & operator=(const Client &);
public:
	Client(const std::string & server, const int port) :
		M_dest(port), M_socket(), M_socket_buf(NULL), M_gz_buf(NULL),
				M_transport(NULL), M_comp_level(-1), M_clean_cycle(true) {
		M_dest.setHost(server);
		open();
		bind();

		M_socket_buf->setEndPoint(M_dest);
	}

	virtual ~Client() {
		close();
	}

	bool sendCmd(char *command) {
		int len;
		len = strlen(command) + 1; // 那么现在的len包括\0
		printf("command:%s\n", command); // 直接先打印出命令
		M_transport->write(command, len); // 发送命令
		M_transport->flush();
		if (!M_transport->good()) { // 错误处理，很简单的函数
			printf("error send socket\n");
			return false;
		}
		return true;
	}

	void run() {
        std::cout << "[run]enter" <<std::endl;
		char command[20]; 
		if (iSide == 1) { // 初始化所有球员
			if (iPlayerId == 1) {sprintf(command, "(init team1 (goalie))");}// 第一个球员是守门员
			else {sprintf(command, "(init team1)");}
		} else if (iSide == 2) {
			if (iPlayerId == 1) {sprintf(command, "(init team2 (goalie))");}
			else {sprintf(command, "(init team2)");}
		} else {return;}
        std::cout << "[run]flag1" <<std::endl;
		if (!sendCmd(command)) return;
        std::cout << "[run]flag2" <<std::endl;

		if (iPlayerId == 1) {sprintf(command, "(move -45 0)");} // 球员的放置，守门员单独放到一个地方
		else {sprintf(command, "(move -3 0)");} // 其他的都放到一个地方
		if (!sendCmd(command)) return;
        std::cout << "[run]messageLoop" <<std::endl;

		messageLoop();
	}

private:

	int open() {
		if (M_socket.open()) {
			if (M_socket.setNonBlocking() < 0) {
				std::cerr << __FILE__ << ": " << __LINE__
						<< ": Error setting socket non-blocking: " << strerror(
						errno) << std::endl;
				M_socket.close();
				return -1;
			}
		} else {
			std::cerr << __FILE__ << ": " << __LINE__
					<< ": Error opening socket: " << strerror(errno)
					<< std::endl;
			M_socket.close();
			return -1;
		}

		M_socket_buf = new rcss::net::SocketStreamBuf(M_socket);
		M_transport = new std::ostream(M_socket_buf);
		return 0;
	}

	bool bind() {
		if (!M_socket.bind(rcss::net::Addr())) {
			std::cerr << __FILE__ << ": " << __LINE__
					<< ": Error connecting socket" << std::endl;
			M_socket.close();
			return false;
		}
		return true;
	}

	void close() {
		M_socket.close();

		if (M_transport) {
			delete M_transport;
			M_transport = NULL;
		}

		if (M_gz_buf) {
			delete M_gz_buf;
			M_gz_buf = NULL;
		}

		if (M_socket_buf) {
			delete M_socket_buf;
			M_socket_buf = NULL;
		}
	}

	int setCompression(int level) {
#ifdef HAVE_LIBZ
		if ( level >= 0 )
		{
			if ( ! M_gz_buf )
			{
				M_gz_buf = new rcss::gz::gzstreambuf( *M_socket_buf );
			}
			M_gz_buf->setLevel( level );
			M_transport->rdbuf( M_gz_buf );
		}
		else
		{
			M_transport->rdbuf( M_socket_buf );
		}
		return M_comp_level = level;
#endif
		return M_comp_level = -1;
	}

	void processMsg(char * msg, const size_t len) {
#ifdef HAVE_LIBZ
		if ( M_comp_level >= 0 )
		{
			M_decomp.decompress( msg, len, Z_SYNC_FLUSH );
			char * out;
			int size;
			M_decomp.getOutput( out, size );
			if ( size > 0 )
			{
				parseMsg( out, size );
			}
		}
		else
#endif
		{
			parseMsg(msg, len);
		}
	}

	void parseMsg(char * msg, const size_t len) { // 进行消息解析
        // 输出到终端
        system("clear");
		std::cout << std::string( msg, len - 1 ) << std::endl; 
        // 这段代码不用管
		if (!std::strncmp(msg, "(ok compression", 15)) { 
			int level;
			if (std::sscanf(msg, " ( ok compression %d )", &level) == 1) { 
				setCompression(level); 
			}
		} else if (!std::strncmp(msg, "(sense_body", 11) 
				|| !std::strncmp(msg, "(see_global", 11) || !std::strncmp(msg,
				"(init", 5)) {
			M_clean_cycle = true; 
		}
        // 守门员的代码
		if (iPlayerId == 1) { 
			if (std::strncmp(msg, "(see ", 5)) { // 只接受see的感知信息
				return;
			}
			double ball_dist = 0; // 球的方向
			double ball_dir = 0; // 球的角度
			char command[20]; // 命令缓冲区
			char *pball; 
			pball = strstr(msg, "(ball)"); // ball是msg的一个子串，是则返回"ball"地址pball
			if (pball == 0) { // 如果看不见就一直转圈了，直到看见为止
				sprintf(command, "(turn 60)"); // 转60度
				if (!sendCmd(command)) return; // 发送数据
				return;
			}

			if (std::sscanf(pball, "(ball) %lf %lf", &ball_dist, &ball_dir)!= 2) { // 如果没有辨别出球的方位和角度
				printf("get ball error\n"); // 获取球失败
				return;
			}

			if (ball_dist < 3) { // 如果与球的距离小于3
				sprintf(command, "(catch %lf)", ball_dir); //发送catch命令以捕获球
				if (!sendCmd(command)) return; // 发送数据
				return;
			}
			if (ball_dir > 10 || ball_dir < -10) { // 如果与球的角度相差太大
				sprintf(command, "(turn %lf)", ball_dir); // 转向球的方向
				if (!sendCmd(command)) return;
				return;
			}
		} 
        else { // 其他队员的代码
			if (!std::strncmp(msg, "(see ", 5)) { // 只解析视觉信息
				if (std::sscanf(msg, "(see  %d )", &currentCycle) == 1) { // 在计时开始前什么也不干
					if (currentCycle == 0) { // before_kick_off
						return;
					}
					if (currentCycle == lastCycle) { // before_kick_off
						return;
					}
                     // 开始踢球
					if (currentCycle > lastCycle) {
						kickWait++;
						if (kickWait < 3) // 在开始后再延时三个时间周期
							return;
						double goal_dist = 0; // 门距离
						double goal_dir = 0; // 门方向
						double ball_dist = 0; // 球距离
						double ball_dir = 0; // 球方向
						char command[20]; // 命令缓冲区
						int len;
						int canSeeGoal; // 是否能看见门
						lastCycle = currentCycle; // kick_off开球
						//search goal
						char *pgoal;
						pgoal = strstr(msg, "(goal r)"); // 找到门的字符串地址
						if (pgoal != 0) { // 获取门的位置信息
							if (std::sscanf(pgoal, "(goal r) %lf %lf",
									&goal_dist, &goal_dir) != 2) {
								printf("get goal error\n"); // 这里是发送来的信息的格式错误
							}
							canSeeGoal = 1; // 能够看见门
						} else {
							canSeeGoal = 0; // 没有解析到门的字符串，看不见门
						}
						char *pball;
						if (!turnToSeeGoal) { // 如果这是一个全局变量
							pball = strstr(msg, "(ball)");
							if (pball != 0) { // 获取球的位置信息
								if (std::sscanf(pball, "(ball) %lf %lf",
										&ball_dist, &ball_dir) != 2) {
									printf("get ball error\n");
								}
							} 
                            else { // 如果看不见球，则转50度，看看能不能看见球
								sprintf(command, "(turn 50)");
								if (!sendCmd(command))
									return;
								printf("turn to see ball\n");
								return;
							}
							printf("%s\t%lf\t%lf\t%lf\t%lf\n", msg, goal_dist,
									goal_dir, ball_dist, ball_dir); // 打印出消息和门，球的位置信息
							//ball turn
							if (ball_dir > 2 || ball_dir < -2) { // 如果球的角度离自己太大的话
								sprintf(command, "(turn %lf)", ball_dir); // 进行转身看球
								if (!sendCmd(command))
									return;
								return;
							}
							//ball dash
							if (ball_dist > 0.5) { // 如果离球太远
								sprintf(command, "(dash 100)"); // 冲向球的位置
								if (!sendCmd(command))
									return;
								return;
							}
						}
						//kick
						turnToSeeGoal = 1; // 开始踢球了
						if (!canSeeGoal) { // 如果看不见球门
							sprintf(command, "(turn 50)"); // 转50度
							len = strlen(command) + 1;
							printf("command:%s\n", command); // 打印出来
							M_transport->write(command, len); // 进行发送，这里没有用封装的函数发送
							M_transport->flush();
							if (!M_transport->good()) {
								printf("error send socket\n");
								return;
							}
							printf("turn to see goal\n");
							return;
						}
						sprintf(command, "(kick 100 %lf)", goal_dir); // 朝门的方向踢球
						if (!sendCmd(command))
							return;
						kickWait = 0;
						turnToSeeGoal = 0; 
					}
				}
			}
		}
	}

	void messageLoop() { // 这个函数是不断接受消息并调用process，而process调用parse
        std::cout << "[messageLoop]enter" <<std::endl;
		fd_set read_fds;
		fd_set read_fds_back;
		char buf[8192];
		std::memset(&buf, 0, sizeof(char) * 8192);

		int in = fileno( stdin );
		FD_ZERO(&read_fds);
		FD_SET(in, &read_fds);
		FD_SET(M_socket.getFD(), &read_fds);
		read_fds_back = read_fds;

#ifdef RCSS_WIN
		int max_fd = 0;
#else
		int max_fd = M_socket.getFD() + 1;
#endif
		while (1) {

			read_fds = read_fds_back;
			int ret = ::select(max_fd, &read_fds, NULL, NULL, NULL);
			if (ret < 0) {
				perror("Error selecting input");
				break;
			} else if (ret != 0) {
				// read from stdin
				if (FD_ISSET(in, &read_fds)) {
					if (std::fgets(buf, sizeof(buf), stdin) != NULL) {
						size_t len = std::strlen(buf);
						if (buf[len - 1] == '\n') {
							buf[len - 1] = '\0';
							--len;
						}

						M_transport->write(buf, len + 1);
						M_transport->flush();
						if (!M_transport->good()) {
							if (errno != ECONNREFUSED) {
								std::cerr << __FILE__ << ": " << __LINE__
										<< ": Error sending to socket: "
										<< strerror(errno) << std::endl
										<< "msg = [" << buf << "]\n";
							}
							M_socket.close();
						}
						std::cout << buf << std::endl;
					}
				}

				// read from socket
				if (FD_ISSET(M_socket.getFD(), &read_fds)) {
					rcss::net::Addr from;
					int len = M_socket.recv(buf, sizeof(buf) - 1, from);
					if (len == -1 && errno != EWOULDBLOCK) {
						if (errno != ECONNREFUSED) {
							std::cerr << __FILE__ << ": " << __LINE__
									<< ": Error receiving from socket: "
									<< strerror(errno) << std::endl;
						}
						M_socket.close();
					} else if (len > 0) {
						M_dest.setPort(from.getPort());
						M_socket_buf->setEndPoint(M_dest);
						processMsg(buf, len);
					}
				}
			}
		}
        std::cout << "[messageLoop]end" <<std::endl;
	}
};

namespace {
Client * client = static_cast<Client *> (0);

void sig_exit_handle(int) {
	std::cerr << "\nKilled. Exiting..." << std::endl;
	if (client) {
		delete client;
		client = static_cast<Client *> (0);
	}
	std::exit(EXIT_FAILURE);
}
}

int main(int argc, char **argv) {
    std::cout << "[main]enter" <<std::endl;
	if (std::signal(SIGINT, &sig_exit_handle) == SIG_ERR || std::signal(
			SIGTERM, &sig_exit_handle) == SIG_ERR || std::signal(SIGHUP,
			&sig_exit_handle) == SIG_ERR) {
		std::cerr << __FILE__ << ": " << __LINE__
				<< ": could not set signal handler: " << std::strerror(errno)
				<< std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::cerr << "Hit Ctrl-C to exit." << std::endl;

	std::string server = "localhost";
	int port = 6000;

	for (int i = 0; i < argc; ++i) { // 进行id分配，这里的意思是说连自己文件名也要解析啊
		if (std::strcmp(argv[i], "-server") == 0) { // 这是它自己的信号连接机制
			if (i + 1 < argc) {
				server = argv[i + 1]; // 那么下一个就是这个，service是字符串没错
				++i;
			}
		} else if (std::strcmp(argv[i], "-port") == 0) {
			if (i + 1 < argc) {
				port = std::atoi(argv[i + 1]); // 端口号是整型这个差不了
				++i;
			}
		}
		if (std::strcmp(argv[i], "id") == 0) { // id是球员的id，iplayerid也是全局变量
			if (i + 1 < argc) {
				iPlayerId = std::atoi(argv[i + 1]);
				++i;
			}
		}
		if (std::strcmp(argv[i], "left") == 0) { // 是左边的还是右边的
			iSide = 1;
		}
		if (std::strcmp(argv[i], "right") == 0) { // 这个是右边的，但这个iSide是全局变量
			iSide = 2;
		}
	}

	client = new Client(server, port);
	client->run();

    std::cout << "[main]end" <<std::endl;
	return EXIT_SUCCESS;
}
