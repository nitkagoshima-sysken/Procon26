#include "procon26_module.hpp"

string Answer::toString()
{
	stringstream sout;
    if (X == NULL_POINT&& Y == NULL_POINT)
    {
        sout << "";
    }
    else
    {
        sout << X << " " << Y << " " << (flipped ? "T" : "H") << " " << turn;
    }
	
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