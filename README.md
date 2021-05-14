# Hacksong_Game
games for PKU hacksong

一、编译
1.windows 上编译
服务器端：
打开server_win文件夹，然后编译用到：之后运行./server.exe
g++ network_tcp_server.cpp -o server -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32
客户端：在本地运行编译，之后在运行./game.exe
g++ game.cpp game.h init.cpp Classes.h Classes.cpp dataset.h dataset.cpp myDrawGame.cpp  myUpdate.cpp Classes.h client.h client.cpp -o game -lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32

2.在linux/max上跑
服务器端，进入server_unix，然后运行g++ network_tcp_server.cpp -o server -lpthread进行编译，之后在运行./server(如果出一些问题，可以尝试删除三个文件libraylib.a、rnet.h、raylib.h，因为这三个文件只有在window下用到，linux不需要)
客户端编译直接运行 make，之后在运行./game

二、运行
1.首先查看服务器端ip地址，如果服务器端和客服端都在本机上跑，就查看本机ip地址，如果在内网下不同机器跑，注意要链接同一个内网，然后记下运行./server那个机器的ip
2.在game.cpp中的Game::Game（）函数的第一行char ip_add[20] = "10.0.2.15";将期中的“10.0.2.15”改成你自己的ip，在编译一下。
3.先跑./server，他会问你有多少player参加，你在命令行输入人数就好（一般debug时候输入1）
4.然后根据你要跑的人数，打开相应数量的terminal，然后输入./game运行（注意，有时候linux，无法多个客户端运行同一个文件，会报permission denied，这时候你可以复制game文件，重命名，这样就可以同时运行了）