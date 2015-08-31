#ifndef __DEF_H
#define __DEF_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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

class BoardBoolean
{
	public:
		bool boolean[BOARD_SIZE + STONE_SIZE - 1][BOARD_SIZE + STONE_SIZE - 1];
		BoardBoolean();
		BoardBoolean *place(int x, int y);	//石を置いた座標を入力し、bool型の2次元配列に反映する
		int check(int x, int y);	//ボードの座標を入力し、その座標に石が置けるかどうかを確認する
};

class StonePicker
{
    private:
        static const int MAX = 32;
        unsigned int dropStones;
        unsigned int dropStonesMax;
        int num;
        int sum;
        int blanks;
        std::vector<std::vector<State *> > stones;
        std::vector<int> indexes;
        std::vector<int> zukus;
        void sortStones();
        int getSum();
        void getStones(std::vector<std::vector<State *> > &stones);
    public:
        StonePicker(std::vector<std::vector<State *> > stones, std::vector<int> zukus, int blanks);
        void getNext(std::vector<std::vector<State *> > &stones);
};

#endif
