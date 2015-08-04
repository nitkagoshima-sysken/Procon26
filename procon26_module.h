#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define STONE_SIZE 8
#define BOARD_SIZE 32

struct Stone
{
	unsigned char zuku[STONE_SIZE];
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

struct Answers
{
	vector<Answer> answers;
};

class Answer
{
	public:
		int X;
		int Y;
		bool flipped;
		int turn;	// 90 * turn;
		
		string toString();	
};

string Answer::toString()
{
	stringstream sout;
	sout << X << " " << Y << " " << (flipped?"T":"H") << " " << turn;
	return sout.str(); 
}
