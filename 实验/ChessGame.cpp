#include "ChessGame.h"
ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
	man->init(chess);
	ai->init(chess);
}
//对局（开始五子棋游戏）
void ChessGame::play()
{
	chess->init();
	while (1) {
		//先由棋手落子
		if (chess->playerFlag) {
			man->go();
			if (chess->checkOver()) {
				chess->init();
				continue;
			}
		}
		//再由机器落子
		if (!chess->playerFlag) {
			ai->go();
			if (chess->checkOver()) {
				chess->init();
				continue;
			}
		}
	}
}

void ChessGame::intro()
{
	cout << "欢迎游玩本五子棋游戏。你将与人机对战，下面是一些指示。" << endl;
	cout << "左键下棋、右键悔棋。如果你在开局时悔棋，则视为人机先手。" << endl << "祝您游戏愉快。" << endl;
}
