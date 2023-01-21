/*
	开发日志：
	1.创建项目、导入素材
	2.设计项目的框架（设计“类”）
	3.设计项目的接口
	4.完善接口 丰富内容 修复BUG
	5.完成
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