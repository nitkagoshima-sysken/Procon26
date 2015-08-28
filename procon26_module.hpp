#ifndef __DEF_H
#define __DEF_H

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define STONE_SIZE 8
#define BOARD_SIZE 32
#define NULL_POINT -64

struct Stone
{
	unsigned char zuku[STONE_SIZE];
};

struct State : public Stone
{
	bool flipped;
	int turn;	// 90 * turn;
};

struct Board
{
	unsigned char block[128];
};

struct Problem
{
	Board board;
	int num;
	Stone *stones;
};

class Answer
{
	public:
        // 石が置けない場合は、X = Y = NULL_POINT
		int X;  
		int Y;
		bool flipped;
		int turn;	// 90 * turn;

		string toString();
};

struct Answers
{
	vector<Answer> answers;
};

#endif
