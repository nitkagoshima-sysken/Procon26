#include "procon26_module.hpp"

string Answer::toString()
{
	stringstream sout;
	sout << X << " " << Y << " " << (flipped ? "T" : "H") << " " << turn;
	return sout.str();
}

BoardBoolean::BoardBoolean()
{
	for(int i = 0; i < BOARD_SIZE + 19; i++)
	{
		for(int j = 0; j < BOARD_SIZE+19; j++)
		{
			boolean[i][j] = true;
		}
	}
}

BoardBoolean::BoardBoolean(int x, int y)
{
	for(int i = 0; i < BOARD_SIZE + 19; i++)
	{
		for(int j = 0; j < BOARD_SIZE + 19; j++)
		{
			boolean[i][j] = true;
		}
	}
	readCoordinate(x, y);
}

void BoardBoolean::readCoordinate(int x, int y)
{
	int start_x, start_y, end_x, end_y;
	start_x = x - 8; end_x = x + 8;
	start_y = y - 8; end_y = y + 8;
	if(start_x < -7)
	{
		start_x = -7;
	}
	if(end_x > 39)
	{
		end_x = 39;
	}
	if(start_y < -7)
	{
		start_y = -7;
	}
	if(end_y > 39)
	{
		end_y = 39;
	}
	for(int i = start_y + 7; i <= end_y + 7; i++)
	{
		for(int j = start_x + 7; j <= end_x + 7; j++)
		{
			boolean[i][j] = false;
		}
	}
}

int BoardBoolean::checkBoolean(int x, int y)
{
	if(x < -7||x > 39||y < -7||y > 39)
	{
		return -1;	//Error
	}
	else
	{
		return (int)boolean[y + 7][x + 7];
	}
}
