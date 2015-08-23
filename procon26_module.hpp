#ifndef __DEF_H
#define __DEF_H

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

struct Answers
{
	vector<Answer> answers;
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
