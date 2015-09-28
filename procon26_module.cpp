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

BoardBoolean::BoardBoolean()
{
	for(int i = 0; i < BOARD_SIZE + STONE_SIZE - 1; i++)
	{
		for(int j = 0; j < BOARD_SIZE + STONE_SIZE - 1; j++)
		{
			boolean[i][j] = true;
		}
	}
}

BoardBoolean* BoardBoolean::place(int x, int y)
{
	BoardBoolean *temp;
	temp = new BoardBoolean;
	int start_x, start_y, end_x, end_y;
	start_x = x - STONE_SIZE; end_x = x + STONE_SIZE;
	start_y = y - STONE_SIZE; end_y = y + STONE_SIZE;
	if(start_x < -(STONE_SIZE - 1))
	{
		start_x = -(STONE_SIZE - 1);
	}
	if(end_x > BOARD_SIZE - 1)
	{
		end_x = BOARD_SIZE - 1;
	}
	if(start_y < -(STONE_SIZE - 1))
	{
		start_y = -(STONE_SIZE - 1);
	}
	if(end_y > BOARD_SIZE - 1)
	{
		end_y = BOARD_SIZE - 1;
	}
	for(int i = start_y + STONE_SIZE - 1; i <= end_y + STONE_SIZE - 1; i++)
	{
		for(int j = start_x + STONE_SIZE - 1; j <= end_x + STONE_SIZE - 1; j++)
		{
			temp -> boolean[i][j] = false;
		}
	}
	return temp;
}

int BoardBoolean::check(int x, int y)
{
	if(x < - (STONE_SIZE - 1)||x > BOARD_SIZE - 1||y < - (STONE_SIZE - 1)||y > BOARD_SIZE- 1)
	{
		return -1;	//Error
	}
	else
	{
		return (int)boolean[y + STONE_SIZE - 1][x + STONE_SIZE - 1];
	}
}

void *Answers::place(int x, int y, bool flipped, int turn)
{
	Answer newAns;
	newAns.X = x; newAns.Y = y;
	newAns.flipped = flipped;
	newAns.turn = turn;
	answers.push_back(newAns);
}

void *Answers::place(State *status, int x, int y)
{
	Answers ans;
	ans.place(x, y, status->flipped, status->turn);
}
	