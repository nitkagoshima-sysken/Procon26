#include "procon26_module.hpp"

string Answer::toString()
{
	stringstream sout;
	sout << X << " " << Y << " " << (flipped ? "T" : "H") << " " << turn;
	return sout.str();
}

StonePicker::StonePicker(std::vector<Stone *> stones_, std::vector<int> zukus_, int blanks_)
{
    stones = stones_; zukus = zukus_; blanks = blanks_;
    dropStones = 0;
    sum = 0;
    sortStones();
    // Skip combinations which is not correct.
    bool done = false; // Skipping is done.
    for(int i = 0; i < stones.size(); i ++) {
        sum += zukus[stones.size() - i - 1];
        if(!done && sum >= blanks) {
            done = true;
            dropStones = 1 << ((stones.size() - i - 1) - 1 - 1); // " - 1" is attached because getNext uses do-while loop.
        }
    }
}

void StonePicker::getNext(std::vector<Stone *> &dest) 
{
    do {
        dropStones ++;
    } while (getSum() > blanks);
    getStones(dest);
}

int StonePicker::getSum()
{
    int result = sum;
    for (int i = 0, b = 1; i < MAX; i ++, b = b << 1) {
        if((dropStones & b) != 0) {
            result -= zukus[i];
        }
    }
    return result;
}

void StonePicker::getStones(std::vector<Stone *> &dest) 
{
    for (int i = 0, b = 1; i < MAX; i ++, b = b << 1) {
        if ((dropStones & b) != 0) {
            dest.push_back(stones[i]);
        }
    }
}

struct stoneData
{
    Stone *myStone;
    int myZuku;
    
    bool operator<(const stoneData& right) const
    {
        return myZuku < right.myStone;
    }
};

void sortStones()
{    
    int num = stones.size();
    vector<stoneData> stoneDatas(num);
    
    for (int i = 0; i < num; i ++)
    {
        stoneData tmp;
        tmp.myStone = stones[i];
        tmp.myZuku  = zukus[i];
    }
    
    sort(stoneDatas.begin(), stoneDatas.end());
    
    stones.clear();
    zukus.clear();
    
    stones = vector<Stone *>(num);
    zukus  = vector<int>(num);
   
    for (int i = 0; i < num; i++)
    {
        stones.push_back(stoneData[i].myStone);
        zukus.push_back(stoneData[i].myZuku);
    }
}