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
#include "math.h"
#include "time.h"

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
#define pi 3.1415926
int mytime;
int isNearBall = 0;
int isSeeGoal = 0;
int isCatchBall = 0;
int isMove = 0;
char command[20]; // 命令缓冲区
int cnm = 0;
int isLeftOrRight = 0; // 0代表左边踢，1代表右边踢
int isRandMove = true;

struct PR{
    double x;
    double y;
    double length;
    double angle;
    void print(){ // 要切换成全局坐标系
        x = cos(length/180 * pi);
        y = sin(length/180 * pi);
        std::cout<<"("<<x<<","<<")"<<std::endl;
    }
};

char FLAG_C_T[]="flag c t";
char FLAG_C_B[]="flag c b";
char FLAG_R_T[]="flag r t";
char FLAG_R_B[]="flag r b";
char FLAG_L_T[]="flag l t";
char FLAG_L_B[]="flag l b";

char *position[6];
char *place;
double rotation = 0;
double angel = 0;
struct location{
    double x;
    double y;
};

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
        // 设计初始要走的地方
        srand((unsigned)time(0));  
        position[0]=FLAG_C_T;
        position[1]=FLAG_C_B;
        position[2]=FLAG_R_T;
        position[3]=FLAG_R_B;
        position[4]=FLAG_L_T;
        position[5]=FLAG_L_B;
        place = position[0];  
        std::cout <<"[run]enter"<<std::endl;
        sprintf(command, "(init team1)");
        sendMessage(command);
        sprintf(command, "(move 0 0)");
        sendMessage(command);
        std::cout <<"[run]end"<<std::endl; 
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
        std::cout<<msg<<std::endl;
        sprintf(command, "(turn 50)"); // 转50度
        angel += 50;
        if(angel > 180) angel -= 360;
        sendMessage(command);
	}
    // 定位
    void myScanf(char *place, double distance, double direction){
        double x=0;
        double y=0;
        x = (-1)*distance * cos((direction+angel)/180 * pi);
        y = (-1)*distance * sin((direction+angel)/180 * pi);
        if (std::strncmp(place, "flag c t", 8)) { 
            x += 52.5;
        }
        if (std::strncmp(place, "flag c b", 8)) { 
            x -= 52.5;
        }
        if (std::strncmp(place, "flag r t", 8)) { 
            x += 52.5;
            y += 34;
        }
        if (std::strncmp(place, "flag r b", 8)) { 
            x -= 52.5;
            y += 34;
        }
        if (std::strncmp(place, "flag l t", 8)) { 
            x -= 52.5;
            y += 34;
        }
        if (std::strncmp(place, "flag l b", 8)) { 
            x -= 52.5;
            y -= 34;
        }
        else{
            x=0;
            y=0;
        }
        //std::cout << "angel"<<angel<<std::endl;
        //std::cout << "("<<x<<", "<<y<<")"<<std::endl;
        //std::cout<<"("<<x<<", "<<y<<")"<<std::endl;
    }
    location Getlocation(char *msg)
    {
        location l;
        double dis = 0;
        double dir = 0;
        char *p;
        if ((p = strstr(msg, "(flag r t)")) != 0)//可以看到球场右上角
        {
            std::sscanf(p,"(flag r t) %lf %lf", &dis, &dir);
            l.y = dis * sin((dir + angel) / 180 * pi) + 34;
            l.x = 52.5 - dis * cos((dir + angel) / 180 * pi);
        }
        else if ((p = strstr(msg, "(flag r b)")) != 0)//可以看到球场右下角
        {
            std::sscanf(p, "(flag r b) %lf %lf", &dis, &dir);
            l.y = dis * sin((dir + angel) / 180 * pi) + (-34);
            l.x = 52.5 - dis * cos((dir + angel) / 180 * pi);
        }
        else if ((p = strstr(msg, "(flag l t)")) != 0)//可以看到球场左上角
        {
            std::sscanf(p, "(flag l t) %lf %lf", &dis, &dir);
            l.y = dis * sin((dir + angel) / 180 * pi) + 34;
            l.x = -52.5 - dis * cos((dir + angel) / 180 * pi);
        }
        else if ((p = strstr(msg, "(flag l b)")) != 0)//可以看到球场左下角
        {
            std::sscanf(p, "(flag l b) %lf %lf", &dis, &dir);
            l.y = dis * sin((dir + angel) / 180 * pi) + (-34);
            l.x = -52.5 - dis * cos((dir + angel) / 180 * pi);
        }
        std::cout << "("<<l.x<<", "<<l.y<<")"<<std::endl;
        std::cout << "dis"<<dis<<std::endl;
        //
        std::cout<<"dir"<<angel+dir<<std::endl;
        return l;
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
						//std::cout << buf << std::endl;
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
	client->run();
    std::cout << "[main]end" <<std::endl;
	return EXIT_SUCCESS;
}
