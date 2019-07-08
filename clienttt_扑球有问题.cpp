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

int mytime;
int isNearBall = 0;
int isSeeGoal = 0;
int isCatchBall = 0;
char command[20]; // 命令缓冲区
int cnm = 0;

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
public:
    int id;
    int side;

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

	void sendMessage(char *command) {
		int len = strlen(command) + 1;
		M_transport->write(command, len); // 发送命令
		M_transport->flush();
	}

	void run() {
        std::cout <<"[run]enter"<<std::endl;
        if(id == 1)
        {
            if(side == 1) {sprintf(command, "(init team1 (goalie))");std::cout<<"(init team1 (goalie))"<<std::endl;}
            else {sprintf(command, "(init team2 (goalie))");std::cout<<"(init team2 (goalie))"<<std::endl;}
            sendMessage(command);
            sprintf(command, "(move -45 0)");
            sendMessage(command);
        }
        else
        {
            if(side == 1) {sprintf(command, "(init team1)");}
            else {sprintf(command, "(init team2)"); }
            sendMessage(command);
            sprintf(command, "(move -3 0)");
            sendMessage(command);
        }
        std::cout <<"[run]send success"<<" side:" <<side<<std::endl; 
        std::cout <<"[run]send success"<<" id:" <<id<<std::endl; 
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
        //system("clear");
		//std::cout << std::string( msg, len - 1 ) << std::endl; 
        if(id == 1) // 守门员代码
        {
            if (std::strncmp(msg, "(see ", 5)) {return;}
			double ball_distance = 0; // 球的方向
			double ball_direction = 0; // 球的角度
			char *p; 
			p = strstr(msg, "(ball)"); 
			if (p == 0) { // 表示看不见球
				sprintf(command, "(turn 50)"); // 转50度
				sendMessage(command);
                return;
			}
			std::sscanf(p, "(ball) %lf %lf", &ball_distance, &ball_direction);

            // 如果与球的角度相差太大
			if (ball_direction >5 || ball_direction < -5) { 
				sprintf(command, "(turn %lf)", ball_direction); // 转向球的方向
				sendMessage(command);
				return;
			}
            // 当球不近也不远的时候
            if(ball_distance>1 && ball_distance<10){
                sprintf(command, "(dash 100)"); // 冲向球的位置
                sendMessage(command);
                return;
            }
            // 当球很近的时候
			if (ball_distance<1 && isCatchBall==0) { // 如果与球的距离小于3
				sprintf(command, "(catch %lf)", ball_direction); //发送catch命令以捕获球
                sendMessage(command);
                isCatchBall = 1;
                std::cout << "I catch the ball" <<std::endl;
				return;
			}
            // 抓住球的时候
            if(isCatchBall == 1)
            {
				sprintf(command, "(kick 100 0)"); //踢出球
                sendMessage(command);
                isCatchBall = 0;
                std::cout << "I kick the ball" <<std::endl;
                return;
            }
        }
        else // 其他球员代码
        {
            // 踢球的代码
            if (!std::strncmp(msg, "(see ", 5)) { // 只解析视觉信息
                std::sscanf(msg, "(see  %d )", &mytime);
                if (mytime == 0) return; // 在计时开始前什么也不干
                // 开始踢球
                if (mytime > 0) {
                    // 获取球的位置
                    // 找到球带上球
                    double distance = 0; // 球距离
                    double direction = 0; // 球方向
                    char *p = strstr(msg, "(ball)");
                    if (p !=0 )  // 获取球的位置信息
                    {
                        std::sscanf(p, "(ball) %lf %lf", &distance, &direction);
                        // 如果球的角度离自己太大的话
                        if (direction > 2 || direction < -2) { 
                            sprintf(command, "(turn %lf)", direction); // 看球
                            sendMessage(command);
                            return;
                        }
                        // 球不在身边，冲向球
                        if (distance > 0.5) // 如果离球太远
                        {
                            isNearBall = 0;
                            sprintf(command, "(dash 100)"); // 冲向球的位置
                            sendMessage(command);
                            //std::cout <<"I can not get near ball, now I dash. "<<distance<<std::endl;
                            return;
                        }
                        else
                        isNearBall = 1;
                    }
                    else { // 如果看不见球，则转50度，看看能不能看见球
                        if(!isNearBall)
                        {
                            //std::cout <<"[ball]I can not see ball, now I turn 50."<<std::endl;
                            sprintf(command, "(turn 50)");
                            sendMessage(command);
                            return;
                        }
                    }
                    // 找到球门的位置
                    // 找到球门转向球门
                    // 向球门那里带球
                    // 小于一定距离进行射门
                    double goal_distance = 0; // 门距离
                    double goal_dirction = 0; // 门方向
                    if(side == 1) p = strstr(msg, "(goal r)"); // 找到门的字符串地址
                    else p = strstr(msg, "(goal l)");
                    if (p != 0) { // 获取门的位置信息
                        if(side == 1) std::sscanf(p, "(goal r) %lf %lf", &goal_distance, &goal_dirction);
                        else std::sscanf(p, "(goal l) %lf %lf", &goal_distance, &goal_dirction);
                        //std::cout <<"ball_direction: " <<direction<<std::endl;
                        //std::cout <<"goal_dirction: " <<goal_dirction<<std::endl;
                        if (direction > 2 || direction < -2) { 
                            sprintf(command, "(turn %lf)", direction); // 进行转身看门
                            sendMessage(command);
                            return;
                        }
                            //std::cout <<"Yes I kick! " <<std::endl;
                            sprintf(command, "(kick 100 %lf)", goal_dirction); // 朝门的方向踢球
                            sendMessage(command);  
                            isNearBall = 0;
                        return;
                    } else {
                        std::cout <<"[goal]I can not see goal, now I turn 50." <<std::endl;
                        sprintf(command, "(turn 50)");
                        sendMessage(command);
                        isSeeGoal = 0; // 没有解析到门的字符串，看不见门
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

	client = new Client(server, port);
    // 1为id，2为id值，3为左右
    if (std::strcmp(argv[1], "id") == 0) { client->id = std::atoi(argv[2]);}
    if (std::strcmp(argv[3], "left") == 0) { client->side = 1; } // 1代表左边
    if (std::strcmp(argv[3], "right") == 0) { client->side = 2; } // 2代表右边
	client->run();

    std::cout << "[main]end" <<std::endl;
	return EXIT_SUCCESS;
}
