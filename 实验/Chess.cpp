#include "Chess.h"
#include<math.h>
#include<mmsystem.h>
#include<algorithm>
#pragma comment(lib,"winmm.lib")
int node[4][2] = { {0,0} , {1,0} , {0,1} , {1,1} };//0.左上角 1.左下角 2.右上角 3.右下角
struct {
	int data;
	int i;
}mini;
void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}
Chess::Chess(int gradeSize, int margin_x, int margin_y, float chessSize)
{
	this->gradeSize = gradeSize;
	this->marginX = margin_x;
	this->marginY = margin_y;
	this->chessSize = chessSize;
	playerFlag = true;
	firstStrike = true;
	for (int i = 0;i < gradeSize;i++) {
		vector<int> row;
		for (int j = 0;j < gradeSize;j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
	mciSendString("play res/bg.wav", 0, 0, 0);
	//创建游戏窗口
	initgraph(790, 781);
	//显示棋盘图片
	loadimage(0, "res/棋盘4.jpg");
	//播放开始提示音
	mciSendString("play res/start.wav", 0, 0, 0);
	// 加载黑棋和白棋的图片(initiate)
	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);//使得棋盘方格大小与棋子大小相同
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);
	loadimage(&chessBlackCur, "res/black2.png", chessSize, chessSize, true);
	loadimage(&chessWhiteCur, "res/white2.png", chessSize, chessSize, true);
	loadimage(&chessRed, "res/red.png", chessSize, chessSize, true);
	//清理上一局（可能的）数据
	for (int i = 0;i < gradeSize;i++) {
		for (int j = 0;j < gradeSize;j++) {
			chessMap[i][j] = 0;
		}
	}
	while (!chessRecord.empty())
		chessRecord.pop();
	playerFlag = true;
	firstStrike = true;
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int col = (x - marginX) / chessSize;
	int row = (y - marginY) / chessSize;
	int leftTopPosX;
	int leftTopPosY;
	//减去左侧、上侧边界 整除每一格宽度（四舍五入） 就能得到横纵坐标
	int offset = chessSize * 0.4;
	int len;
	mini.data = 789;
	bool ret = false;//本函数返回值
	for (int i = 0;i < 4;i++) {
		//点击点是否在左上角 左下角 右上角 右下角的判定
		leftTopPosX = marginX + chessSize * (col + node[i][0]);
		leftTopPosY = marginY + chessSize * (row + node[i][1]);
		len = sqrt(pow(x - leftTopPosX, 2) + pow(y - leftTopPosY, 2));
		if (len <= mini.data) {
			mini.data = len;
			mini.i = i;
		}
	}
//	cout << "行 " << row + 1 << " 列 " << char('A' + col) << endl;
//	cout << "mini data " << len << " mini i " << mini.i << endl;
	col += node[mini.i][0];
	row += node[mini.i][1];
	pos->col = col;
	pos->row = row;
	if (!chessMap[pos->row][pos->col]) {
		ret = true;
	}
	return ret;
}

void Chess::recall()
{
//	cout << "hello" << endl;
	if (chessRecord.empty()) {
		playerFlag = !playerFlag;
		firstStrike = false;
		return;
	}
	else if (chessRecord.size() == 1) {
		cout << "你现在不能撤回！请先下第一步棋。" << endl;
		return;
	}	
	for (int i = 0;i < 2;i++) {
		int row = chessRecord.top().row;
		int col = chessRecord.top().col;
		chessMap[row][col] = 0;
		chessRecord.pop();
	}
	drawMap();
}
	

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	mciSendString("play res/down7.wav", 0, 0, 0);
	int x = marginX + chessSize * pos->col - 0.5 * chessSize;
	int y = marginY + chessSize * pos->row - 0.5 * chessSize;
//	if (kind == CHESS_WHITE)
//		putimagePNG(x, y, &chessWhiteImg);
//	else putimagePNG(x, y, &chessBlackImg);
	updateGameMap(pos);
	drawMap();
}

int Chess::getGradeSize()
{
	return gradeSize;//题目要求棋盘大小为15
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

bool Chess::borderCheck(int row, int col)
{
	return (row >= 0 && row < gradeSize && col >= 0 && col < gradeSize);
}

bool Chess::checkWin()
{
	int row = lastPos.row;
	int col = lastPos.col;
//	cout << "lastPos:" << row << " " << col << endl;
//	cout << "JudgeWin:Within Border" << endl;
	for (int x = 0;x <= 1;x++) {
		for (int y = -1;y <= 1;y++) { //经典的方向决定式子 x 和 y
			if ((x == 0 && y == 0) || (x == 0 && y == -1)) continue;
//			printf("dir:%d %d \n", x, y);
			//i的意思是在连续五个点
			for (int i = 0;i < 5;i++) {
				//一次判断，共4次，连续5子均同色则游戏结束
				int cnt = 0;
				ChessPos pos;//每一次连续确认的起点
				pos.row = row - i * y;
				pos.col = col - i * x;
				if (!borderCheck(pos.row, pos.col) || !borderCheck(pos.row + 4 * y, pos.col + 4 * x)) {
//					cout << "Temp Pos is out of border!" << endl;
					continue;
				}
				for (int j = 1;j <= 4;j++) {
					if (chessMap[pos.row][pos.col] == chessMap[pos.row + j * y][pos.col + j * x] && chessMap[pos.row][pos.col] != 0) {
						cnt++;
					}
				}
//				printf("x = %d y = %d cnt = %d\n", x, y, cnt);
				if (cnt == 4) {
					showResult(x, y, pos);
					cout << "Gameover!" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

void Chess::showResult(int x,int y,ChessPos pos)
{
	if (borderCheck(pos.row, pos.col) && borderCheck(pos.row + 4 * y, pos.col + 4 * x)) {
		for (int i = 0;i < 5;i++) {
			chessMap[pos.row + i * y][pos.col + i * x] = 2;
		}
		drawMap();
		Sleep(3000);
	}
}

bool Chess::checkOver()
{
	if (checkWin()) {
		if (!playerFlag) {
			mciSendString("play res/不错.mp3", 0, 0, 0);
			loadimage(0, "res/胜利.jpg");
		}
		else {
			mciSendString("play res/失败.mp3", 0, 0, 0);
			loadimage(0, "res/失败.jpg");
		}
		Sleep(3000);
		return true;
	}
	return false;
}



void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessRecord.push(lastPos);
//	printf("%d %d recorded\n", chessRecord.top().row, chessRecord.top().col);
	if (firstStrike)
		chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	else
		chessMap[pos->row][pos->col] = playerFlag ? CHESS_WHITE : CHESS_BLACK;
	playerFlag = !playerFlag;
}

void Chess::drawMap()
{
	cleardevice();
	loadimage(0, "res/棋盘4.jpg");
	for (int i = 0;i < gradeSize;i++) {
		for (int j = 0;j < gradeSize;j++) {
			int x = marginX + chessSize * j - 0.5 * chessSize;
			int y = marginY + chessSize * i - 0.5 * chessSize;
			switch (chessMap[i][j]) 
			{
			case 1: 
				putimagePNG(x, y, (i == lastPos.row && j == lastPos.col) ? &chessBlackCur : &chessBlackImg);
				break;
			case -1:
				putimagePNG(x, y, (i == lastPos.row && j == lastPos.col) ? &chessWhiteCur : &chessWhiteImg);
				break;
			case 2:
				putimagePNG(x, y, &chessRed);
				break;
			}
			
		}
	}
}
