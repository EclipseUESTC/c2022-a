 #include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;//��ȡ�������Ϣ
	ChessPos pos;
	//ͨ��chess�����������ж������Ƿ���Ч���Լ����ӹ���
	bool mouse;
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_RBUTTONDOWN) {
			mouse = false;
			break;
		}
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			mouse = true;
			break;
		}
	}
	system("cls");
	//��������
	if (mouse)
		chess->chessDown(&pos, CHESS_BLACK);
	else chess->recall();
}
