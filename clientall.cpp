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
char command[20]; // 命令缓冲区，一个全局command，这样会方便一些
int cnm = 0;
int isLeftOrRight = 0; // 0代表左边踢，1代表右边踢
int isRandMove = true;
double playerSpeed = 0;
int isOdd = 0; // 这个变量一言难尽啊，因为标记点太少，因此凑活这用
char *position[6];
char *place;
double rotation = 0;
double angel = 0;

double init_x; // 出生时候的初始坐标
double init_y; // 定位时用，防止乱跑
// TODO:
int isGetBall = 0; // 这个全局变量是后卫听是否我方正在掌控着球

struct location{
    double x;
    double y;
};

struct PR{
    double x;
    double y;
    double length;
    double angle;
    void print(){ // 要切换成全局坐标系
        x = cos(length/180 * pi);
        y = sin(length/180 * pi);
    }
};

char FLAG_C_T[]="(flag p r c)";
char FLAG_C_B[]="(flag p l c)";
char FLAG_R_T[]="(flag p r t)";
char FLAG_R_B[]="(flag p l t)";
char FLAG_L_T[]="(flag p r b)";
char FLAG_L_B[]="(flag p l b)";

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
        if(side == 1){ // 代表左边
            if(id == 1){ // 当作守门员
                sprintf(command, "(init team1 (goalie))");
                sendMessage(command);
                sprintf(command, "(move -40 0)");
                sendMessage(command);
            }
            if(id == 2){
                // 需要进行初始position的存储
            }
            if(id == 3){
                
            }
            if(id == 4){
                
            }
            if(id == 5){
                
            }
            if(id == 6){
                
            }
            if(id == 7){
                
            }
            if(id == 8){
                
            }
            if(id == 9){
                
            }
            if(id == 10){
                
            }
            if(id == 11){
                
            }
        } 
        else if(side == 2){ 
            if(id == 1){ // 当作守门员
                sprintf(command, "(init team2 (goalie))");
                sendMessage(command);
                sprintf(command, "(move -40 0)");
                sendMessage(command);
            }
            if(id == 2){

            }
            if(id == 3){
                
            }
            if(id == 4){
                
            }
            if(id == 5){
                
            }
            if(id == 6){
                
            }
            if(id == 7){
                
            }
            if(id == 8){
                
            }
            if(id == 9){
                
            }
            if(id == 10){
                
            }
            if(id == 11){
                
            }
        } 
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
    
	void parseMsg(char * msg, const size_t len) { // 进行消息解析 TODO:
        resetAngle(char *msg); // angel值修正，这个需要每帧运行
        // 守门员代码：一直看球，球到一定距离内进行扑球，扑球之后射出
        if(id == 1){ // 守门员代码
            if (std::strncmp(msg, "(see ", 5)) {return;} // 只有为0的时候才会正确
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

            // 如果与球的角度相差太大，转向球的方向
			if (ball_direction >5 || ball_direction < -5) { 
				sprintf(command, "(turn %lf)", ball_direction);
				sendMessage(command);
				return;
			}
            // 当球非常远的时候
            if(ball_distance>1 && ball_distance<13){
                isMove=0; isCatchBall = 0; // 这里是进行防错处理的
                return;
            }
            // 当球不近也不远的时候
            if(ball_distance>1 && ball_distance<13){
                sprintf(command, "(dash 100)"); // 冲向球的位置
                sendMessage(command);
                isMove=0; isCatchBall = 0; // 这里是进行防错处理的
                return;
            }
            // 当球很近的时候
			if (ball_distance<1 && isCatchBall==0) { // 如果与球的距离小于3
				sprintf(command, "(catch %lf)", ball_direction); //发送catch命令以捕获球
                sendMessage(command);
                isCatchBall = 1; // 抓住球的布尔变量
				return;
			}
            // 抓住球的时候
            if(isCatchBall == 1)
            {   // 如果没有瞬移，先进行瞬移，catch球之后允许瞬移
                if(isMove == 0) // 这个布尔变量是为了防止二次瞬移的
                {  
                    sprintf(command, "(move -40 0)");
                    sendMessage(command);
                    isMove = 1;
                    return;
                }
                // 现在开始看门
                double goal_distance = 0; // 门距离
                double goal_dirction = 0; // 门方向
                if(side == 1) p = strstr(msg, "(goal r)"); // 找到门的字符串地址
                else p = strstr(msg, "(goal l)");
                if (p != 0) // 获取门的位置信息
                {
                    if(side == 1) std::sscanf(p, "(goal r) %lf %lf", &goal_distance, &goal_dirction);
                    else std::sscanf(p, "(goal l) %lf %lf", &goal_distance, &goal_dirction);
                    // 踢球！
                    sprintf(command, "(kick 100 %lf)", goal_dirction); // 朝门的方向踢球
                    sendMessage(command);
                    isCatchBall = 0;
                    isMove = 0;
                }
                else{   // 没看到门，转身看门
                    sprintf(command, "(turn 50)");
                    sendMessage(command);
                }
                return;
            }
        }
        // 球员1代码 // TODO:
        if(id == 2){
            // 接受听的消息
            if (std::strncmp(msg, "(hear", 5) == 0){
                char *p = strstr(msg, "I get ball");
                if(p == 0){ // 表示没有运球
                    isGetBall = 0;
                }
                else{ // 表示运球，就保持在球的附近之内
                    isGetBall = 1;
                }
            }
            // 接受看的消息
            if (std::strncmp(msg, "(see ", 5) == 0){
                if(isGetBall == 1){ // 说明我方正在运球，这时候只保持一定距离，不至于太远就好了
                    char *p = strstr(msg, "(ball)"); 
                    if (p == 0) { // 表示看不见球
                        sprintf(command, "(turn 50)"); // 转50度
                        sendMessage(command);
                        return;
                    }
                    else{ // 看见球了，保持一定距离即可
                        double ball_distance = 0; // 球的方向
                        double ball_direction = 0; // 球的角度
                        std::sscanf(p, "(ball) %lf %lf", &ball_distance, &ball_direction);
                        // 如果与球的角度相差太大，转向球的方向
                        if (ball_direction >5 || ball_direction < -5) { 
                            sprintf(command, "(turn %lf)", ball_direction);
                            sendMessage(command);
                            return;
                        }
                        // 现在就是计算其坐标，以维持在一定距离内
                        // 球距离过大而且自身还在自己的活动区域内
                        location l = Getlocation(msg);
                        if(ball_distance > 52.5 &&  (l.x<init_x+26) && (l.y<init_y+17)){
                            sprintf(command, "(dash 100)"); // 冲向球的位置，就冲一下
                            sendMessage(command); // 可能会冲出去，不过没关系
                        }
                    }
                }
                else if(isGetBall == 0){ // 球并未被我方掌控的时候
                    // 获得球的直角坐标
                    // 看它是否在自己的区域内
                    // 在就进行行动就行
                    double ball_distance = 0; // 球的方向
                    double ball_direction = 0; // 球的角度
                    char *p = strstr(msg, "(ball)"); 
                    if (p == 0) { // 表示看不见球
                        sprintf(command, "(turn 50)"); // 转50度
                        sendMessage(command);
                        return;
                    }
                    std::sscanf(p, "(ball) %lf %lf", &ball_distance, &ball_direction);
                    // 如果与球的角度相差太大，转向球的方向
                    if (ball_direction >5 || ball_direction < -5) { 
                        sprintf(command, "(turn %lf)", ball_direction);
                        sendMessage(command);
                        return;
                    }
                    // 计算球的坐标
                    location l = Getlocation(msg);
                    double A_x = ball_distance * cos(angel);
                    double A_y = ball_distance * sin(angel);
                    double ball_x = l.x + A_x;
                    double ball_y = l.x + A_y;
                    if(ball_x < init_x+26 && ball_y < init_y+17){ // 在范围内
                        if(ball_distance > 0.5){
                            sprintf(command, "(dash 100)"); // 冲向球的位置，就冲一下
                            sendMessage(command); // 可能会冲出去，不过没关系
                            return;
                        }
                        // 现在找门的位置，踢
                        if(ball_distance < 0.5){
                            double goal_distance = 0; 
                            double goal_dirction = 0; // 门方向
                            char *p;
                            if(side == 1) p = strstr(msg, "(goal r)"); // 找到门的字符串地址
                            else p = strstr(msg, "(goal l)");
                            if (p != 0) // 获取门的位置信息
                            {
                                if(side == 1) std::sscanf(p, "(goal r) %lf %lf", &goal_distance, &goal_dirction);
                                else std::sscanf(p, "(goal l) %lf %lf", &goal_distance, &goal_dirction);
                                // 踢球！
                                sprintf(command, "(kick 100 %lf)", goal_dirction); // 朝门的方向踢球
                                sendMessage(command);
                            }
                            else{   // 没看到门，转身看门
                                sprintf(command, "(turn 50)");
                                sendMessage(command);
                            }
                            return;
                        }   
                    }
                }
            }
        }
        if(id == 3){

        }
        if(id == 4){

        }
        if(id == 5){

        }
        if(id == 6){

        }
        if(id == 7){

        }
        if(id == 8){

        }
        if(id == 9){

        }
        if(id == 10){

        }
        if(id == 11){

        }





        if (std::strncmp(msg, "(see ", 5)==0){
            if(isRandMove == 1){
                char *p = strstr(msg, place);
                if(p == 0){
                    sprintf(command, "(turn 50)"); // 转50度
                    angel += 50/(1.0+playerSpeed); //转过角度/(1.0 + 5.0*球员速度)
                    if(angel > 180) angel -= 360; 
                    sendMessage(command);
                    resetAngle(msg);
                    return;
                }
                else{
                    double distance = 0; // 目的地方向
                    double direction = 0; // 目的地角度
                    p += 12;
                    std::sscanf(p, "%lf %lf", &distance, &direction);  
                    //std::cout<<"[parse]"<<distance<<" "<<direction<<std::endl;
                    if (direction >5 || direction < -5) { 
                        sprintf(command, "(turn %lf)", direction);
                        angel += direction/(1.0+playerSpeed);
                        if(angel > 180) angel -= 360; // 这里仅仅是象征性的估计
                        sendMessage(command);
                        resetAngle(msg);
                        return;
                    }
                    if(distance>1){ // 前进到目的地
                        sprintf(command, "(dash 100)"); // 冲向球的位置
                        sendMessage(command);
                        resetAngle(msg);
                        Getlocation(msg);
                        return;
                    }
                    if(distance<2){
                        isRandMove = 0;
                    }
                }
            }
            if(isRandMove == 0){
                int t = 0;
                if(isOdd == 0){ // 表明是偶数
                    while(t%2 != 1)
                        t = rand()%6;
                    isOdd = 1;
                }
                else{           // 表明是奇数
                    while(t%2 != 0)
                        t = rand()%6;
                    isOdd = 0;
                }
                place = position[t];
                std::cout<<"then go to "<<place<<std::endl;
                isRandMove = 1;
            }
        }
        
	}
    // 设四个定位函数
    void resetAngle(char *msg){
        char *p1, *p2;
        double r1, r2, d1, d2;
        if((p1 = strstr(msg, "(flag r t)")) != 0){ // 左边修正
            std::sscanf(p1, "(flag r t) %lf %lf", &d1, &r1);
            if((p2 = strstr(msg, "(flag r b)"))){
                std::sscanf(p2, "(flag r b) %lf %lf", &d2, &r2);
                double angle_t = (pow(d1, 2)+pow(68, 2)-pow(d2, 2))/(2*d1*68); // 余弦算出角度
                angle_t = acos(angle_t); // 反cos化
                angle_t = angle_t*180/pi; // 进行角度化
                angle_t = 180 - abs(r1) - angle_t; // 算出另一个角
                if(angle_t > 90) angle_t = 180 - angle_t; // 转换成锐角
                angle_t = 90 - angle_t; // 得到值
                if(abs(r1) < abs(r2)) angel = angle_t * (-1); // 进行方向赋值
                else  angel = angle_t;
                return;
            }
            return;
        }
        if((p1 = strstr(msg, "(flag l t)")) != 0){ // 右边修正
            std::sscanf(p1, "(flag l t) %lf %lf", &d1, &r1);
            if((p2 = strstr(msg, "(flag l b)"))){
                std::sscanf(p2, "(flag l b) %lf %lf", &d2, &r2);
                double angle_t = (pow(d1, 2)+pow(68, 2)-pow(d2, 2))/(2*d1*68); // 余弦算出角度
                angle_t = acos(angle_t); // 反cos化
                angle_t = angle_t*180/pi; // 进行角度化
                angle_t = 180 - abs(r1) - angle_t; // 算出另一个角
                if(angle_t > 90) angle_t = 180 - angle_t; // 转换成锐角
                angle_t = 90 - angle_t; // 得到值
                if(abs(r1) < abs(r2)) angel = angle_t - 180; // 进行方向赋值
                else  angel = 180 - angle_t;
                return;
            }
            return;
        }
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
        l.y = (-1)*l.y;
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
// 命令行：id id值 left/right
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
    if (std::strcmp(argv[3], "right") == 0) { client->side = 2; } // 2代表右
	client->run();
    std::cout << "[main]end" <<std::endl;
	return EXIT_SUCCESS;
}
