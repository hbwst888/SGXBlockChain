#pragma once
#pragma warning(disable:4996) 
#include <cstdio>
#include<iostream>
#include<string>
//#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
//想要连接的远程服务器IP地址
const char* remote_Addr = "127.0.0.1";
//想要连接的远程服务器端口
const int remote_PORT = 8000;
#define MaxBufSize 1024
#define _CRT_SECURE_NO_WARINGS
int setupClient() {
	WSADATA wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	SOCKET SocketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN  ClientAddr;

	ClientAddr.sin_family = AF_INET;
	
	ClientAddr.sin_addr.S_un.S_addr = inet_addr(remote_Addr);
	ClientAddr.sin_port = htons(remote_PORT);
	int n = 0;
	n = connect(SocketClient, (struct sockaddr*)&ClientAddr, sizeof(ClientAddr));
	if (n == SOCKET_ERROR) {
		cout << "连接失败" << endl;
		return -1;
	}
	cout << "已经连接到服务器，可以向服务器发送消息了！" << endl;
	char info[1024], SendBuff[MaxBufSize], RecvBuff[MaxBufSize];
	while (1) {
		cout << "请输入要发送的信息,按回车结束发送：" << endl;
		cin >> info;
		if (info[0] == '\0')
			break;
		strcpy(SendBuff, info);
		memset(info, 0, sizeof(info));
		int k = 0;
		n = send(SocketClient, SendBuff, sizeof(SendBuff), 0);
		memset(SendBuff, 0, sizeof(SendBuff));
		if (k < 0) {
			cout << "发送失败" << endl;
		}
		Sleep(500);
		int n = 0;
		n = recv(SocketClient, RecvBuff, sizeof(RecvBuff), 0);
		if (n > 0) {
			cout << "接收到来自服务器的消息为：" << RecvBuff << endl;
		}
		memset(RecvBuff, 0, sizeof(RecvBuff));
	}
	closesocket(SocketClient);
	WSACleanup();
	return 0;



}