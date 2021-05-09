#ifndef _CLIENT_H
#define _CLINET_H

#include "raylib.h"
#include "rnet.h"
#include<stdio.h>
#include<iostream>
#include<cstring>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

#define MSG_BUF_SIZE 1204

// data struct for recv data and send data
typedef struct send_data0
{
	unsigned random_seed;
    int player_number;
	int index;
}Send_data0;


typedef struct keys_info
{
	char move[4];
	char change_object[2];
    char pick;
    char throwing;
    char join;
}Keys_info;

//WSA set up
class WSASession
{
public:
	WSASession();
	~WSASession();
private:
	WSAData data;
};


class Myclient{
    public:
        Myclient(const char* ip_add, int port);
        ~Myclient();

        int send_data(const char* buf, int len);
        int recvall(char * buffer0, int length);
    private:
        SOCKET client_sock;
        char recv_buffer[MSG_BUF_SIZE];

};

#endif