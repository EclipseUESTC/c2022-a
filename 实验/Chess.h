#pragma once
#include<Windows.h>
#include<stack>
#include<graphics.h>
#include<easyx.h>
#include<conio.h>
#include<iostream>
#include<vector>
using namespace std;
//表示棋盘位置
struct ChessPos {
	int row;//行
	int col;//列
};
typedef enum {
	CHESS_WHITE = -1,//白棋
	CHESS_BLACK = 1,//黑棋
	EMPTY = 0//空白
}chess_kind_t;
class Chess
{
public:
	Chess(int gradeSize, int margin_x, int margin_y, float chessSize);
	ChessPos lastPos;
	stack<ChessPos> chessRecord;
	void init();
	bool clickBoard(int x, int y, ChessPos *pos);//判断落子是否有效
	void recall();
	void chessDown(ChessPos *pos, chess_kind_t kind);
	int getGradeSize();//获取棋盘大小（15）
	int getChessData(ChessPos* pos);//获取位置是黑棋还是白棋or空白
	bool borderCheck(int row, int col);
	bool checkWin();
	void showResult(int x,int y,ChessPos pos);
	bool checkOver();//检查棋局是否结束
	bool playerFlag; //真：黑执子；假：白执子
	bool firstStrike;//真：玩家先手；假：AI先手
private:
	IMAGE chessBlackImg; //黑棋棋子
	IMAGE chessWhiteImg; //白棋棋子
	IMAGE chessBlackCur; //黑棋目前位置
	IMAGE chessWhiteCur; //白棋目前位置
	IMAGE chessRed;//胜利的棋子
	int gradeSize; //棋盘的大小 = 15;
	int marginX;//棋盘的左边界
	int marginY;//棋盘的上边界
	float chessSize; //棋子的大小 与棋盘小方格相同
	vector<vector<int>> chessMap; //存储当前棋局棋子分布数据
	void updateGameMap(ChessPos *pos);
	void drawMap();
};

