

#include "WebServer.h"



int main() {

	WebServer webserver;
	webserver.start("0.0.0.0", 8000);
	while (true) {
		printf("���ո��˳�����...\n");
		if (_kbhit()) {//�������Ƿ������� ������1 ������0
			if (_getch() == VK_SPACE) {
				webserver.stop();
				break;
			}
		}
		Sleep(1000);
	}
	printf("WebServer stop ...\n");
	system("pause");
	return 0;
}
