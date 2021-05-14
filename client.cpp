#include "client.h"
#include <iostream>

using namespace std;


#if defined(_WIN32) // Windows
WSASession::WSASession()
{
	int ret_val = WSAStartup(MAKEWORD(2, 2), &data);
	if (ret_val != 0)
	{
		cerr << "WSA failed to start up!Error code: " << ::WSAGetLastError() << "\n";
		system("pause");
		exit(1);
	}
	cout << "WSA started up successfully...\n";
}
WSASession::~WSASession()
{
	WSACleanup();
}


Myclient::Myclient(const char* ip_add, int port)
{
	client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(client_sock == INVALID_SOCKET)
    {
        printf("invalid socket!");
        return;
    }
    
    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(port);
    serAddr.sin_addr.S_un.S_addr = inet_addr(ip_add);
    if(connect(client_sock, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {  //连接失败 
        printf("connect error !");
        closesocket(client_sock);
        return;
    }
	//
	cout << "Client started successfully..." << endl;
}

Myclient::~Myclient()
{
	closesocket(client_sock);
	cout << "Socket closed..." << endl;
}

#else
Myclient::Myclient(const char* ip_add, int port)
{
	struct sockaddr_in server_addr;
	if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) { 
        perror("socket init error!"); 
        exit(1); 
    }

    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(port); 
    server_addr.sin_addr.s_addr = inet_addr(ip_add); 
    bzero(&(server_addr.sin_zero),sizeof(server_addr.sin_zero)); 

    if (connect(client_sock, (struct sockaddr *)&server_addr,sizeof(struct sockaddr_in)) == -1){
        perror("connect error"); 
        exit(1);
    } 
	cout << "Client started successfully..." << endl;
}

Myclient::~Myclient()
{
	close(client_sock);
	cout << "Socket closed..." << endl;
}

#endif

int Myclient::recvall(char * buffer0, int length)
{
    char *buffer = buffer0;
	while (length>0) {
		//cout << length << endl;
		int ret_val = recv(client_sock, buffer, length , 0);
		if (ret_val > 0) {
			buffer += ret_val;
			length -= ret_val;
		}
		else if(ret_val == 0){
			cerr << "Failed to receive data:" << ret_val << endl;
			return -1;
		}
		else {
			cerr << "Failed to receive message from client!Error code: " << endl;
			return -1;
		}
	}
	return 1;
}

int Myclient::send_data(const char* buf, int len){
    return send(client_sock, buf, len, 0);
}
