#ifndef __DEF_H
#define __DEF_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#define STONE_SIZE 8
#define BOARD_SIZE 32
#define BOARD_LOOP 128 //BOARD_SIZE * (BOARD_SIZE / sizeof(char)) 
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
		int X;
		int Y;
		bool flipped;
		int turn;	// 90 * turn;

		string toString();
};

class Answers
{
	private:
		vector<Answer> answers;
	
	public:
		void place(State *, int, int);
		void place(int, int, bool, int);
		void print(int);
};

class BoardBoolean
{
	private:
		bool boolean[BOARD_SIZE + (STONE_SIZE - 1) * 2][BOARD_SIZE + (STONE_SIZE - 1) * 2];
	public:
		BoardBoolean();
		BoardBoolean(int x, int y);
		void place(int x, int y);	//石を置いた座標を入力し、bool型の2次元配列に反映する
		int check(int x, int y);	//ボードの座標を入力し、その座標に石が置けるかどうかを確認する
};

#endif
