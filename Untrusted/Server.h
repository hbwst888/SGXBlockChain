#pragma once
#pragma warning(disable:4996) 
#include <cstdio>
#include<iostream>
#include<string>
#include <tchar.h>
#include "Account.h"
#include "sgx_urts.h"
#include "Teechaindemo_u.h"
//#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
const int PORT = 8000;
#define MaxClient 10
#define MaxBufSize 1024
#define _CRT_SECURE_NO_WARINGS
//�����߳�
DWORD WINAPI ServerThread(LPVOID lpParameter) {
	SOCKET* ClientSocket = (SOCKET*)lpParameter;
	int receByt = 0;
	char RecvBuf[MaxBufSize];
	char SendBuf[MaxBufSize];
	while (1) {
		receByt = recv(*ClientSocket, RecvBuf, sizeof(RecvBuf), 0);
		//buf[receByt]='\0';
		if (receByt > 0) {
			cout << "���յ�����Ϣ�ǣ�" << RecvBuf << "            ���Կͻ���:" << *ClientSocket << endl;
			// cout<<receByt<<endl;
		}
		else
		{
			cout << "������Ϣ������" << endl;
			break;
		}
		int ret;
		Ecall_ReceiveTransaction(Eid, &ret, unsigned long long(RecvBuf));

		memset(RecvBuf, 0, sizeof(RecvBuf));
		/*cout << "������Ҫ���͵��ͻ��˵���Ϣ��" << endl;
		cin >> SendBuf;*/
		strcpy(SendBuf, "���׳ɹ�");
		int k = 0;
		k = send(*ClientSocket, SendBuf, sizeof(SendBuf), 0);
		if (k < 0) {
			cout << "����ʧ��" << endl;
		}
		memset(SendBuf, 0, sizeof(SendBuf));
	}//while
	closesocket(*ClientSocket);
	free(ClientSocket);
	return 0;
}

int setupServer() {
	WSAData wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ListenAddr;
	ListenAddr.sin_family = AF_INET;
	ListenAddr.sin_addr.S_un.S_addr = INADDR_ANY;//��ʾ���뱾��ip
	ListenAddr.sin_port = htons(PORT);
	int n;
	n = bind(ListenSocket, (LPSOCKADDR)&ListenAddr, sizeof(ListenAddr));
	if (n == SOCKET_ERROR) {
		cout << "�˿ڰ�ʧ�ܣ�" << endl;
		return -1;
	}
	else {
		cout << "�˿ڰ󶨳ɹ���" << PORT << endl;
	}
	int l = listen(ListenSocket, 20);
	cout << "�����׼���������ȴ���������" << endl;

	while (1) {
		//ѭ�����տͻ����������󲢴��������߳�
		SOCKET* ClientSocket = new SOCKET;
		ClientSocket = (SOCKET*)malloc(sizeof(SOCKET));
		//���տͻ�����������
		int SockAddrlen = sizeof(sockaddr);
		*ClientSocket = accept(ListenSocket, 0, 0);
		cout << "һ���ͻ��������ӵ���������socket�ǣ�" << *ClientSocket << endl;
		CreateThread(NULL, 0, &ServerThread, ClientSocket, 0, NULL);
	}//while
	closesocket(ListenSocket);
	WSACleanup();
	return(0);
}//main