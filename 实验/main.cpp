/*
	������־��
	1.������Ŀ�������ز�
	2.�����Ŀ�Ŀ�ܣ���ơ��ࡱ��
	3.�����Ŀ�Ľӿ�
	4.���ƽӿ� �ḻ���� �޸�BUG
	5.���
*/
#include<iostream>
#include "ChessGame.h"
using namespace std;
int main() {
	Man man;
	Chess chess(15, 45, 45, 50.4);
	AI ai;
	ChessGame game(&man, &ai, &chess);
	game.intro();
	game.play();
	return 0;
}