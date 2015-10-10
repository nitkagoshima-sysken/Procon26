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
#define INT_SIZE 32

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
		int stoneNumber;
		
		string toString();
};

class Answers
{
	public:
	int num;
	vector<Answer> answers;
	Answers(int num);
	void place(int stoneNumber, int x, int y, bool flipped, int turn);
	void place(int stoneNumber, State *, int x, int y);
	void print(ostream &os);
};

class StonePicker
{
    private:
        static const int MAX = 256;
        unsigned int dropStones[8]; // MAX / INT_SIZE
        unsigned int dropStonesMax;
        int num;
        int sum;
        int blanks;
        std::vector<std::vector<State *> > stones;
        std::vector<int> indexes;
        std::vector<int> zukus;
        void sortStones();
        int getSum();
        void getStones(std::vector<std::vector<State *> > &stones, std::vector<int> &stoneNumbers);
        bool isDrop(int num);
        void increment(int index);
    public:
        StonePicker(std::vector<std::vector<State *> > stones, std::vector<int> zukus, int blanks);
        void getNext(std::vector<std::vector<State *> > &stones, std::vector<int> &stoneNumbers);
};

class BoardBoolean
{
	public:
		char boolean[40*40/sizeof(char)];
		BoardBoolean();
		BoardBoolean *place(int x, int y);
		bool check(int x, int y);
};

class SubmissionManager
{
    private:
        int cnt;
        string fileName;

    public:
        SubmissionManager(string _fileName);
        string submit(Answers *answer);
};

#endif
