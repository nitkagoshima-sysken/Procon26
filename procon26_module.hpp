#ifndef __DEF_H
#define __DEF_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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
