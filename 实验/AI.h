#pragma once
#include "Chess.h"
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<iostream>
using namespace std;
class AI
{
public:
	void init(Chess *chess);//
	void go();
	bool withinBorder(ChessPos pos);
private:
	Chess* chess;
	ChessPos posDown;
	vector<vector<int>> scoreMap;
	ChessPos* pos;
	bool posJudge(ChessPos pos,chess_kind_t kind);
	void calculateScore();
	ChessPos think();
};

