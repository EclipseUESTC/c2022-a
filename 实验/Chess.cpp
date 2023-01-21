#include "Chess.h"
#include<math.h>
#include<mmsystem.h>
#include<algorithm>
#pragma comment(lib,"winmm.lib")
int node[4][2] = { {0,0} , {1,0} , {0,1} , {1,1} };//0.���Ͻ� 1.���½� 2.���Ͻ� 3.���½�
struct {
	int data;
	int i;
}mini;
void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
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
	//������Ϸ����
	initgraph(790, 781);
	//��ʾ����ͼƬ
	loadimage(0, "res/����4.jpg");
	//���ſ�ʼ��ʾ��
	mciSendString("play res/start.wav", 0, 0, 0);
	// ���غ���Ͱ����ͼƬ(initiate)
	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);//ʹ�����̷����С�����Ӵ�С��ͬ
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);
	loadimage(&chessBlackCur, "res/black2.png", chessSize, chessSize, true);
	loadimage(&chessWhiteCur, "res/white2.png", chessSize, chessSize, true);
	loadimage(&chessRed, "res/red.png", chessSize, chessSize, true);
	//������һ�֣����ܵģ�����
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
	//��ȥ��ࡢ�ϲ�߽� ����ÿһ���ȣ��������룩 ���ܵõ���������
	int offset = chessSize * 0.4;
	int len;
	mini.data = 789;
	bool ret = false;//����������ֵ
	for (int i = 0;i < 4;i++) {
		//������Ƿ������Ͻ� ���½� ���Ͻ� ���½ǵ��ж�
		leftTopPosX = marginX + chessSize * (col + node[i][0]);
		leftTopPosY = marginY + chessSize * (row + node[i][1]);
		len = sqrt(pow(x - leftTopPosX, 2) + pow(y - leftTopPosY, 2));
		if (len <= mini.data) {
			mini.data = len;
			mini.i = i;
		}
	}
//	cout << "�� " << row + 1 << " �� " << char('A' + col) << endl;
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
		cout << "�����ڲ��ܳ��أ������µ�һ���塣" << endl;
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
	return gradeSize;//��ĿҪ�����̴�СΪ15
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
		for (int y = -1;y <= 1;y++) { //����ķ������ʽ�� x �� y
			if ((x == 0 && y == 0) || (x == 0 && y == -1)) continue;
//			printf("dir:%d %d \n", x, y);
			//i����˼�������������
			for (int i = 0;i < 5;i++) {
				//һ���жϣ���4�Σ�����5�Ӿ�ͬɫ����Ϸ����
				int cnt = 0;
				ChessPos pos;//ÿһ������ȷ�ϵ����
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
			mciSendString("play res/����.mp3", 0, 0, 0);
			loadimage(0, "res/ʤ��.jpg");
		}
		else {
			mciSendString("play res/ʧ��.mp3", 0, 0, 0);
			loadimage(0, "res/ʧ��.jpg");
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
	loadimage(0, "res/����4.jpg");
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
