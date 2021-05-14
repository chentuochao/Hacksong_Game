#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <stdio.h>  
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#define MAX_PLAYER 10
#define MSG_BUF_SIZE 1204
using namespace std;


unsigned seed; // random seed

typedef struct MyData
{
	int sock;
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
extern bool already_recv[MAX_PLAYER];
extern pthread_mutex_t mutex[MAX_PLAYER];  

bool client_working[MAX_PLAYER];
pthread_mutex_t mutex[MAX_PLAYER];  
bool already_recv[MAX_PLAYER];

void check_all_recv(){
    for(int i = 0; i < num_player ; ++i){
        if(! already_recv[i]) return;
    }
    for(int i = 0; i < num_player ; ++i){
        pthread_mutex_unlock(&mutex[i]);
    }

}

bool check_end(Keys_info* p){
    if(p->move[0]==2 || p->move[1]==2 || p->move[2]==2 || p->move[3]==2 
    || p->change_object[0] == 2 || p->change_object[1] == 2 
    || p->pick == 2 || p->throwing == 2 || p->join == 2) return true;
    else return false;
}

int recvall(int sock, char * buffer0, int length)
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
			cerr << "Failed to receive message from client!Error code: " << endl;
			return -1;
		}
	}
	return 1;
}

void* CreateClientThread(void* arg) // for thermal camera
{
	MYDATA *para = (MYDATA*)arg;
	int sock_clt = para->sock;
	int index = para->index;
	char buffer[MSG_BUF_SIZE];

    while(!init_begin) continue;
    Send_data0 data0 = {seed, num_player, index};
    send(sock_clt, &data0, sizeof(Send_data0), 0);
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
        pthread_mutex_lock(&mutex[index]);        
        cout << "sending......." << endl;
        send(sock_clt, (char*)return_info, MAX_PLAYER*sizeof(Keys_info), 0);
        already_recv[index] = false;
    }
    
    close(sock_clt);
	cout << "end this client thread!" << endl;
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

    struct  sockaddr_in server_sockaddr,client_sockaddr;
    //创建套接字  
    int server_sockfd = socket(AF_INET,SOCK_STREAM,0);
  
    //绑定IP和端口  
    sockaddr_in sin;  
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(8888);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    size_t server_len = sizeof(server_sockaddr);

    int on;
    setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR,&on,sizeof(on));


    if(bind(server_sockfd, (struct sockaddr*)&server_sockaddr, server_len)==-1){
        printf("bind error");
        exit(1);
    }

    if(listen(server_sockfd, num_player)==-1){
        printf("listen error");
        exit(1);
    }

    int connfd;
    char cilentIp[20] = {'\0'};
    size_t client_len = sizeof(client_sockaddr);
    cout << "wait for connect..." << endl;

    for(int i = 0; i < num_player; ++i){
        if((connfd = accept(server_sockfd, (struct sockaddr*)&client_sockaddr, &client_len))==-1) {
            printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
        }
        //获取端口
        unsigned short port= ntohs(client_sockaddr.sin_port);
        //网络Ip=>主机Ip
        const char *ip=inet_ntop(AF_INET,(void *)&client_sockaddr.sin_addr,cilentIp,16);
        printf("client %d information: %s:%d\n", i, cilentIp, port);
        
        sock_list[i].sock = connfd;
		sock_list[i].index = i;
        client_working[i] = true;
        pthread_mutex_init(&mutex[i], NULL);
        pthread_mutex_lock(&mutex[i]);
        // create the thread
        pthread_t client_thread;
        int ret = pthread_create( &client_thread, NULL, CreateClientThread, (void *)(sock_list + i) );
        if(ret != 0) cout << "creat thread error!" << endl;
        //HANDLE h_thread = CreateThread(nullptr, 0, CreateClientThread, sock_list + i, 0, nullptr); 
        
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
    close(server_sockfd);  
    return 0;  
}