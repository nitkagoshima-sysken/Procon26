#include "procon26_module.hpp"
#include <fstream>
#include <iostream>
using namespace std;

string Answer::toString()
{
	stringstream sout;
	sout << X << " " << Y << " " << (flipped ? "T" : "H") << " " << turn * 90;
	return sout.str();
}

StonePicker::StonePicker(std::vector<std::vector<State *> > stones_, std::vector<int> zukus_, int blanks_)
{
    stones = stones_; zukus = zukus_; blanks = blanks_;
    num = stones.size();
    dropStonesMax = (1 << num) - 1;
    dropStones = 0;
    sum = 0;
    sortStones();
    // Skip combinations which is not correct.
    bool done = false; // Skipping is done.
    for(int i = 0; i < num; i ++) {
        sum += zukus[num - i - 1];
        if(!done && sum >= blanks ) {
            done = true;
            dropStones = (1 << (num - i - 1)) - 1;
        }
    }
}

void StonePicker::getNext(std::vector<std::vector<State *> > &dest)
{
    while(true){
        if(dropStones > dropStonesMax){
            return;
        }
        if(getSum() <= blanks){
            getStones(dest);
            dropStones ++;
            return;
        }
        dropStones ++;
    }
}

int StonePicker::getSum()
{
    int result = sum;
    for (int i = 0, b = 1; i < MAX && i < num; i ++, b = b << 1) {
        if((dropStones & b) != 0) {
            result -= zukus[i];
        }
    }
    return result;
}

void StonePicker::getStones(std::vector<std::vector<State *> > &dest)
{
    std::vector<int> drops;
    for (int i = 0, b = 1; i < MAX && i < num; i ++, b = b << 1) {
        if ((dropStones & b) != 0) {
            drops.push_back(indexes[i]);
        }
    }
    sort(drops.begin(), drops.end());
    for (int i = 0, j = 0, dlen = drops.size(); i < num; j++) {
        for (; i < num && (j >= dlen || i < drops[j]); i++) {
            dest.push_back(stones[i]);
        }
        i++;
    }
}

struct stoneData
{
    int index;
    int myZuku;
    
    bool operator<(const stoneData& right) const
    {
        return myZuku < right.myZuku;
    }
};

void StonePicker::sortStones()
{    
    std::vector<stoneData> stoneDatas;
    
    for (int i = 0; i < num; i ++)
    {
        stoneData tmp;
        tmp.index   = i;
        tmp.myZuku  = zukus[i];
        stoneDatas.push_back(tmp);
    }

    sort(stoneDatas.begin(), stoneDatas.end());

    indexes.clear();
    zukus.clear();

    for (int i = 0; i < num; i++)
    {
        indexes.push_back(stoneDatas[i].index);
        zukus.push_back(stoneDatas[i].myZuku);
    }
}

BoardBoolean::BoardBoolean()
{
	for(int i = 0; i < 40 * 39 / sizeof(int); i++)
	{
		boolean[i] = 0;
	}
}

BoardBoolean* BoardBoolean::place(int x, int y)
{
	BoardBoolean *temp;
	temp = new BoardBoolean;
	int start_x, start_y, end_x, end_y;
	x += STONE_SIZE;
	y += STONE_SIZE - 1;
	start_x = x - STONE_SIZE; end_x = x + STONE_SIZE;
	start_y = y - STONE_SIZE; end_y = y + STONE_SIZE;
	if(start_x < 1)
	{
		start_x = 1;
	}
	if(end_x > 39)
	{
		end_x = 39;
	}
	if(start_y < 0)
	{
		start_y = 0;
	}
	if(end_y > 38)
	{
		end_y = 38;
	}
	for(int y = start_y; y <= end_y; y++)
	{
		for(int x = start_x; x <= end_x; x++)
		{
			temp -> boolean[x / 8 + y * 5] |= 0x80 >> (x % 8);
		}
	}
	return temp;
	
}

bool BoardBoolean::check(int x, int y)
{
	x += STONE_SIZE;
	y += STONE_SIZE - 1;
	return (bool)(boolean[x / 8 + y * 5] & 0x80 >> (x % 8));
}

Answers::Answers(int _num) {
    num = _num;
}

void Answers::place(int stoneNumber, int x, int y, bool flipped, int turn)
{
	Answer newAns;
	newAns.X = x; newAns.Y = y;
	newAns.flipped = flipped;
    newAns.stoneNumber = stoneNumber;
	newAns.turn = turn;
	answers.push_back(newAns);
}

void Answers::place(int stoneNumber, State *status, int x, int y)
{
	(*this).place(stoneNumber, x, y, status->flipped, status->turn);
}
	
void Answers::print(ostream &os)
{
    int j = 0;
    for (int i = 0; i < num; i++)
    {
        if (j < answers.size() && answers.at(j).stoneNumber == i)
        {
            os << answers.at(j).toString();
            j++;
        }
        os << endl;
    }
}

SubmissionManager::SubmissionManager(string _fileName)
{
    cnt = 0;
    fileName = _fileName;
}

string SubmissionManager::submit(Answers *answer)
{
    stringstream sout;
    sout << fileName << cnt++ << ".txt";
    ofstream ofs(sout.str().c_str());
    answer->print(ofs);
    return sout.str();
}
