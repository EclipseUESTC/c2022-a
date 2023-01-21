 #include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;//获取鼠标点击信息
	ChessPos pos;
	//通过chess对象来调用判断落子是否有效，以及落子功能
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
	//黑棋落子
	if (mouse)
		chess->chessDown(&pos, CHESS_BLACK);
	else chess->recall();
}
