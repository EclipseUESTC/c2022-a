#pragma once
#include<Windows.h>
#include<stack>
#include<graphics.h>
#include<easyx.h>
#include<conio.h>
#include<iostream>
#include<vector>
using namespace std;
//��ʾ����λ��
struct ChessPos {
	int row;//��
	int col;//��
};
typedef enum {
	CHESS_WHITE = -1,//����
	CHESS_BLACK = 1,//����
	EMPTY = 0//�հ�
}chess_kind_t;
class Chess
{
public:
	Chess(int gradeSize, int margin_x, int margin_y, float chessSize);
	ChessPos lastPos;
	stack<ChessPos> chessRecord;
	void init();
	bool clickBoard(int x, int y, ChessPos *pos);//�ж������Ƿ���Ч
	void recall();
	void chessDown(ChessPos *pos, chess_kind_t kind);
	int getGradeSize();//��ȡ���̴�С��15��
	int getChessData(ChessPos* pos);//��ȡλ���Ǻ��廹�ǰ���or�հ�
	bool borderCheck(int row, int col);
	bool checkWin();
	void showResult(int x,int y,ChessPos pos);
	bool checkOver();//�������Ƿ����
	bool playerFlag; //�棺��ִ�ӣ��٣���ִ��
	bool firstStrike;//�棺������֣��٣�AI����
private:
	IMAGE chessBlackImg; //��������
	IMAGE chessWhiteImg; //��������
	IMAGE chessBlackCur; //����Ŀǰλ��
	IMAGE chessWhiteCur; //����Ŀǰλ��
	IMAGE chessRed;//ʤ��������
	int gradeSize; //���̵Ĵ�С = 15;
	int marginX;//���̵���߽�
	int marginY;//���̵��ϱ߽�
	float chessSize; //���ӵĴ�С ������С������ͬ
	vector<vector<int>> chessMap; //�洢��ǰ������ӷֲ�����
	void updateGameMap(ChessPos *pos);
	void drawMap();
};

