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

void StonePicker::getNext(std::vector<Stone *> &dest) 
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

void StonePicker::getStones(std::vector<Stone *> &dest) 
{
    for (int i = 0, b = 1; i < MAX && i < num; i ++, b = b << 1) {
        if ((dropStones & b) == 0) {
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
        return myZuku < right.myZuku;
    }
};

void StonePicker::sortStones()
{    
    std::vector<stoneData> stoneDatas;
    
    for (int i = 0; i < num; i ++)
    {
        stoneData tmp;
        tmp.myStone = stones[i];
        tmp.myZuku  = zukus[i];
        stoneDatas.push_back(tmp);
    }

    sort(stoneDatas.begin(), stoneDatas.end());

    stones.clear();
    zukus.clear();

    for (int i = 0; i < num; i++)
    {
        stones.push_back(stoneDatas[i].myStone);
        zukus.push_back(stoneDatas[i].myZuku);
    }
}