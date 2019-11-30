#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_SIZE_BUF 1024*256

int fun1();

int main() {

	fun1();

	system("pause");
	return 0;
}

int fun1() {
	WSADATA wd;
	WSAStartup(MAKEWORD(2,2), &wd);

	//����һ���׽��� IPV4 ������ TCPЭ��
	SOCKET skt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (skt == INVALID_SOCKET) {
		printf("socket error %d ...\n", GetLastError());
		return -1;
	}
	printf("socket success ...\n");

	//IPV4Э�� ip �˿�
	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;//IPV4
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");//�Զ��󶨱���IP��ַ
	addr.sin_port = htons(8000);//�˿�8000

	//���׽���
	if (bind(skt, (const sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		printf("bind error %d ...\n", GetLastError());
		return -1;
	}
	printf("bind success ...\n");

	//�����׽���
	if (listen(skt, SOMAXCONN) == SOCKET_ERROR) {
		printf("listen error %d ...\n", GetLastError());
		return -1;
	}
	printf("listen success ...\n");

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(skt, &fds);

	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 1000;
	while (true) {
		fd_set readfds = fds;
		if (select(0, &readfds, NULL, NULL, &tv) <= 0) {
			continue;
		}
		for (u_int i = 0; i < readfds.fd_count; ++i) {
			SOCKET tskt = readfds.fd_array[i];
			if (tskt == skt) {//���µĿͻ�����������
				SOCKET cskt = accept(skt, NULL, NULL);
				if (cskt == INVALID_SOCKET) {
					printf("accept error %d ...\n", GetLastError());
					return -1;
				}
				printf("accept success ...\n");
				FD_SET(cskt, &fds);
				continue;
			}
			char buf[MAX_SIZE_BUF];
			int irecv = recv(tskt, buf, sizeof(buf), 0);//����������������Ϣ
			if (irecv > 0) {
				printf("%s\n", buf);
				char page[] = "<html><head><title>���ײ˵�С�������</title></head><body style='color:red;background:#eee;'>���ײ˵�С����</body></html>";
				int length = strlen(page);
				char head[MAX_SIZE_BUF] = { 0 };
				sprintf(head, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n", length);
				send(tskt, head, strlen(head), 0);
				send(tskt, page, strlen(page), 0);
			}
			FD_CLR(tskt, &fds);
			//irecv=0 ��ʾ�ͻ����˳� irecv=-1 ��ʾ�ͻ����쳣�˳�
			closesocket(tskt);
		}
	}

	closesocket(skt);//�ر��׽���
	WSACleanup();
	return 0;
}