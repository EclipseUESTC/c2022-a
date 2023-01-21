#include "AI.h"

void AI::init(Chess* chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0;i < size;i++) {
		vector<int> row;
		for (int j = 0;j < size;j++) {
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}
	

void AI::go()
{
	ChessPos pos;
	if (chess->chessRecord.empty()) {
		pos.col = 7;
		pos.row = 7;
	}
	else {
		pos = think();
		srand((unsigned)time(NULL));
		int stime = rand() % 3000;
		Sleep(stime);
	}
	chess->chessDown(&pos, CHESS_WHITE);
}

bool AI::withinBorder(ChessPos pos)
{
	return  (pos.row >= 0 && pos.row < scoreMap.size() && pos.col >= 0 && pos.col < scoreMap.size());
}

bool AI::posJudge(ChessPos pos,chess_kind_t kind)
{
	if (withinBorder(pos)) {
//		printf("judge %d %d\n", pos.row, pos.col);
		return chess->getChessData(&pos) == kind;
	}
//	printf("outOfBorder\n");
	return false;
}//�жϸ�λ���Ƿ񳬳��߽缰�������������AI����

void AI::calculateScore()
{
	//������������
	for (int i = 0;i < scoreMap.size();i++) {
		for (int j = 0;j < scoreMap[i].size();j++) {
			scoreMap[i][j] = 0;
		}
	}
	ChessPos pos_t, curPos;
	int score[2][2][5] = 
	{ 
		{ { 0,10,30,60,20000 }/*һ���հ�λ��*/,{ 0,10,40,150,20000 }/*�����հ�λ��*/ }, //����
		{ { 5,10,50,200,30000 }/*һ���հ�λ��*/,{ 5,10,75,10000,30000 }/*�����հ�λ��*/ },//����
	};//��һά�ȣ��ڰ�0/1���ڶ�ά��0/1���հ�λ�ø���-1������ά�ȣ����Ӹ�����Ӧ������	
	int size = chess->getGradeSize();
	for (curPos.row = 0;curPos.row < size;curPos.row++) {
		for (curPos.col = 0;curPos.col < size;curPos.col++) {
			//��ÿ�������ϵĵ����
			if (chess->getChessData(&curPos) != 0) continue;//���������Ϊ�� �ż���
			for (int y = -1;y <= 1;y++) {
				for (int x = 0;x <= 1;x++) {
					
					int personNum = 0/*��������������������ж��ٸ�����*/, AINum = 0,/*����������������ж��ٸ�����������*/emptyNum = 0;//�÷����Ͽհ�λ�õĸ���
					if (x == 0 && y == 0) continue;
					if (y == -1 && x == 0) continue;
					//�����ڸ�λ�����ӻṹ��ʲô����
					for (int dir = -1;dir <= 1;dir += 2) {
						for (int i = 1;i <= 4;i++) {
							pos_t.row = curPos.row + i * y * dir;
							pos_t.col = curPos.col + i * x * dir;
							if (posJudge(pos_t, CHESS_BLACK)) {
								personNum++;
							}
							else if (posJudge(pos_t, EMPTY)) {
								emptyNum++;
								break;
							}
							else {//���߽�ͳ�ѭ��
								break;
							}
						}
					}
					if (personNum == 1 || personNum == 4) {
						scoreMap[curPos.row][curPos.col] += score[0][0][personNum];
					}
					else if (emptyNum == 1 || emptyNum == 2) {
						scoreMap[curPos.row][curPos.col] += score[0][emptyNum - 1][personNum];
					}
					emptyNum = 0;
					for (int dir = -1;dir <= 1;dir += 2) {
						for (int i = 1;i <= 4;i++) {
							pos_t.row = curPos.row + i * y * dir;
							pos_t.col = curPos.col + i * x * dir;
							if (posJudge(pos_t, CHESS_WHITE)) {
								AINum++;
							}
							else if (posJudge(pos_t, EMPTY)) {
								emptyNum++;
								break;
							}
							else {
								break;
							}
						}
					}
							//if (chess->lastPos.col <= curPos.col + 1 && chess->lastPos.col >= curPos.col - 1 && chess->lastPos.row <= curPos.row + 1 && chess->lastPos.row >= curPos.row - 1) {
							//	printf("<curPos:%d %d> ", curPos.row, curPos.col);
							//	printf("<direction:x=%d y=%d>\n", x, y);
							//	printf("emptyNum:%d,personNum:%d,AiNum:%d\n", emptyNum, personNum, AINum);
							//	printf("personScore:+%d,AIScore:+%d\n", score[0][0][personNum], score[1][0][AINum]);
							//}
					if (AINum <= 1 || AINum >= 4) {
						scoreMap[curPos.row][curPos.col] += score[1][0][AINum];
					}
					else if (emptyNum == 1 || emptyNum == 2) {
						scoreMap[curPos.row][curPos.col] += score[1][emptyNum - 1][AINum];
					}
				}
			}
		}
	}


}

ChessPos AI::think()
{
//	printf("\n\n");
	AI::calculateScore();
	ChessPos pos = { 0,0 };
	int maxScore = 0;
	vector<ChessPos> record;
	printf("      ");
	for (int i = 65;i < scoreMap.size()+65;i++) {
		printf("%-6c", i);
	}
	cout << endl;
	for (int j = 0;j < scoreMap.size();j++) {
		printf("%-6d", j+1);
		for (int i = 0;i < scoreMap.size();i++) {
			printf("%-6d", scoreMap[j][i]);
			if (maxScore < scoreMap[j][i]) {
				record.clear();
				pos.row = j;
				pos.col = i;
				record.push_back(pos);
				maxScore = scoreMap[j][i];
			}
			else if (maxScore == scoreMap[j][i]) {
				pos.row = j;
				pos.col = i;
				record.push_back(pos);
			}
		}
		cout << endl;
	}
	printf("maxscore:%d\n", maxScore);
//	for (int i = 0;i < record.size();i++) cout << record[i].row << " " << record[i].col<<endl;
	srand((unsigned)time(NULL));
	int index = rand() % record.size();
//	cout << record.size() << " " << index << endl;
	return record[index];
}
