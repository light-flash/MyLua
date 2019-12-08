
#ifndef __WebServer_H__
#define __WebServer_H__

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <conio.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_SIZE_BUF 1024*256

class WebServer{
public:
	int start(const char* ip, u_short port);//��ʼ������
	void stop();//ֹͣ����
private:
	bool dispatch(SOCKET skt, char* buf, int length);//�ַ���Ϣ
	static void workthread(void* lpParam);

	uintptr_t threadid;//�߳�ID

	bool m_bExit;//true �߳��˳� false �߳�ִ��
	fd_set m_fds;//socket����
	SOCKET m_skt;//������socket
};


#endif // !__WebServer_H__

