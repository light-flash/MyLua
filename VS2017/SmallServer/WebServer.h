
#ifndef __WebServer_H__
#define __WebServer_H__

#include "common.h"
#include "WebRequest.h"

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

