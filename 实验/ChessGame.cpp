#include "ChessGame.h"
ChessGame::ChessGame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
	man->init(chess);
	ai->init(chess);
}
//�Ծ֣���ʼ��������Ϸ��
void ChessGame::play()
{
	chess->init();
	while (1) {
		//������������
		if (chess->playerFlag) {
			man->go();
			if (chess->checkOver()) {
				chess->init();
				continue;
			}
		}
		//���ɻ�������
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
	cout << "��ӭ���汾��������Ϸ���㽫���˻���ս��������һЩָʾ��" << endl;
	cout << "������塢�Ҽ����塣������ڿ���ʱ���壬����Ϊ�˻����֡�" << endl << "ף����Ϸ��졣" << endl;
}
