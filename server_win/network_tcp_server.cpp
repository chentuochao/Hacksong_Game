
#include <stdio.h>  
#include <winsock2.h>  
#include <iostream>
#include <Windows.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")  

#define MAX_PLAYER 10
#define MSG_BUF_SIZE 1204

unsigned seed; // random seed

typedef struct MyData
{
	SOCKET sock;
	int index;
}MYDATA;

MYDATA sock_list[MAX_PLAYER];

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

Keys_info return_info[MAX_PLAYER];

bool init_begin = 0;
bool recv_all_data = 0;
int num_player = 0;
extern HANDLE g_hSemaphore[MAX_PLAYER];                      //声明信号量变量
extern bool already_recv[MAX_PLAYER];
bool client_working[MAX_PLAYER];

HANDLE g_hSemaphore[MAX_PLAYER];  
bool already_recv[MAX_PLAYER];

void check_all_recv(){
    for(int i = 0; i < num_player ; ++i){
        if(! already_recv[i]) return;
    }
    for(int i = 0; i < num_player ; ++i){
        ReleaseSemaphore(
          g_hSemaphore[i], // handle to semaphore - hSemaphore是要增加的信号量句柄
          1, // increase count by one - lReleaseCount是增加的计数
          NULL);// not interested in previous count - lpPreviousCount是增加前的数值返回
    }

}

bool check_end(Keys_info* p){
    if(p->move[0]==2 || p->move[1]==2 || p->move[2]==2 || p->move[3]==2 
    || p->change_object[0] == 2 || p->change_object[1] == 2 
    || p->pick == 2 || p->throwing == 2 || p->join == 2) return true;
    else return false;
}

int recvall(SOCKET sock, char * buffer0, int length)
{
	char *buffer = buffer0;
	while (length>0) {
		int ret_val = recv(sock, buffer, length , 0);
		if (ret_val > 0) {
			buffer += ret_val;
			length -= ret_val;
		}
		else if(ret_val == 0){
			cerr << "Failed to receive data:" << ret_val << endl;
			return -1;
		}
		else {
			cerr << "Failed to receive message from client!Error code: " << GetLastError() << endl;
			return -1;
		}
	}
	return 1;
}

DWORD WINAPI CreateClientThread(LPVOID lpParameter) // for thermal camera
{
	MYDATA *para = (MYDATA*)lpParameter;
	SOCKET sock_clt = para->sock;
	int index = para->index;
	char buffer[MSG_BUF_SIZE];

    while(!init_begin) continue;
    Send_data0 data0 = {seed, num_player, index};
    send(sock_clt, (const char*)&data0, sizeof(Send_data0), 0);
    already_recv[index] = false; 
    int ret = 0;

    while(true){
        memset(buffer, 0, sizeof(char)* MSG_BUF_SIZE);
        ret = recvall(sock_clt, buffer, sizeof(Keys_info));
        memcpy(return_info + index, buffer, sizeof(Keys_info));

        cout << index  << " recv " <<int(return_info[index].move[0])<<  ' ' <<int(return_info[index].move[1]) <<  ' ' <<int(return_info[index].move[2])<<  ' ' <<int(return_info[index].move[3]) << ' ' << int(return_info[index].change_object[0]) << ' ' <<int(return_info[index].change_object[1]) << ' ' <<int(return_info[index].pick) <<  ' ' <<int(return_info[index].throwing) << ' ' <<  int(return_info[index].join) <<  ' ' << endl;
        already_recv[index] = true;
        check_all_recv();
        if(check_end(return_info + index)) {
            client_working[index] = false;
            cout << "recv invalid message, and end!" <<endl;
            break;
        }
        WaitForSingleObject(g_hSemaphore[index], INFINITE); // wait for recv all message
        cout << "sending......."  << index << endl;
        send(sock_clt, (char*)return_info, MAX_PLAYER*sizeof(Keys_info), 0);
        already_recv[index] = false;
    }
    
	int ret_val = shutdown(sock_clt, SD_SEND);
	if (ret_val == SOCKET_ERROR)
	{
		cerr << "Failed to shutdown the client socket!Error code: " << GetLastError() << "\n";
		closesocket(sock_clt);
		system("pause");
		return 1;
	}
	cout << "end this client thread!" << endl;
	return 0;
}


int main(int argc, char* argv[])  
{  
    seed = 199;
    for(int i = 0; i< MAX_PLAYER; ++i) {
        already_recv[i] = true;
        client_working[i] = false;
    }
    
    cout << "How many player will attend?" << endl;
    cin >> num_player;
    
    WORD sockVersion = MAKEWORD(2,2);  
    WSADATA wsaData;  
    if(WSAStartup(sockVersion, &wsaData)!=0)  
    {  
        return 0;  
    }  
  
    //创建套接字  
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(slisten == INVALID_SOCKET)  
    {  
        cout << "socket error !" << endl;  
        return 0;  
    }  
  
    //绑定IP和端口  
    sockaddr_in sin;  
    sin.sin_family = AF_INET;  
    sin.sin_port = htons(8888);  
    sin.sin_addr.S_un.S_addr = INADDR_ANY;   
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)  
    {  
        cout <<  "bind error !" << endl;  
    }  
  
    //开始监听  
    if(listen(slisten, MAX_PLAYER) == SOCKET_ERROR)  
    {  
        cout << "listen error !" << endl;  
        return 0;  
    }  
  
    //循环接收数据  
    SOCKET sClient;  
    sockaddr_in remoteAddr;  
    int nAddrlen = sizeof(remoteAddr);  
    char revData[255];  

    cout << "wait for connect..." << endl;
    for(int i = 0; i < num_player; ++i){
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);  
        if(sClient == INVALID_SOCKET)  
        {  
            cout <<  "accept error !" << endl;  
            continue;  
        }  
        cout << "Player" << i << " connected: " << inet_ntoa(remoteAddr.sin_addr) << endl; 
        
        sock_list[i].sock = sClient;
		sock_list[i].index = i;
        client_working[i] = true;

        HANDLE h_thread = CreateThread(nullptr, 0, CreateClientThread, sock_list + i, 0, nullptr); 
        g_hSemaphore[i] = CreateSemaphore(NULL          //信号量的安全特性
                                , 0            //设置信号量的初始计数。可设置零到最大值之间的一个值
                                , 1            //设置信号量的最大计数
                                , NULL         //指定信号量对象的名称
                                );
		if (h_thread == NULL)
		{
			cerr << "Failed to create a new thread!Error code: " << WSAGetLastError() << "\n";
			WSACleanup();
			system("pause");
			exit(1);
		}
		CloseHandle(h_thread);
    }
    // initialization begin
    init_begin = 1;

    while(true){
        bool still_working = false;
        for(int i = 0; i < num_player; ++i){
            if(client_working[i]) still_working = true;
        }
        if(!still_working) break;
    }

    cout << "All clients end" << endl;
    closesocket(slisten);  
    WSACleanup();  
    return 0;  
}