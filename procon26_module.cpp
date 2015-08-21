#include "procon26_module.hpp"

string Answer::toString()
{
	stringstream sout;
	sout << X << " " << Y << " " << (flipped ? "T" : "H") << " " << turn;
	return sout.str();
}

BoardBoolean::BoardBoolean()
{
	for(int i = 0; i < BOARD_SIZE + (STONE_SIZE - 1) * 2; i++)
	{
		for(int j = 0; j < BOARD_SIZE + (STONE_SIZE - 1) * 2; j++)
		{
			boolean[i][j] = true;
		}
	}
}

BoardBoolean::BoardBoolean(int x, int y)
{
	for(int i = 0; i < BOARD_SIZE + (STONE_SIZE - 1) * 2; i++)
	{
		for(int j = 0; j < BOARD_SIZE + (STONE_SIZE - 1) * 2; j++)
		{
			boolean[i][j] = true;
		}
	}
	readCoordinate(x, y);
}

void BoardBoolean::readCoordinate(int x, int y)
{
	int start_x, start_y, end_x, end_y;
	start_x = x - STONE_SIZE; end_x = x + STONE_SIZE;
	start_y = y - STONE_SIZE; end_y = y + STONE_SIZE;
	if(start_x < -(STONE_SIZE - 1))
	{
		start_x = -(STONE_SIZE - 1);
	}
	if(end_x > BOARD_SIZE + STONE_SIZE - 1)
	{
		end_x = BOARD_SIZE + STONE_SIZE - 1;
	}
	if(start_y < -(STONE_SIZE - 1))
	{
		start_y = -(STONE_SIZE - 1);
	}
	if(end_y > BOARD_SIZE + STONE_SIZE - 1)
	{
		end_y = BOARD_SIZE + STONE_SIZE - 1;
	}
	for(int i = start_y + STONE_SIZE - 1; i <= end_y + STONE_SIZE - 1; i++)
	{
		for(int j = start_x + STONE_SIZE - 1; j <= end_x + STONE_SIZE - 1; j++)
		{
			boolean[i][j] = false;
		}
	}
}

int BoardBoolean::checkBoolean(int x, int y)
{
	if(x < - (STONE_SIZE - 1)||x > BOARD_SIZE + STONE_SIZE - 1||y < - (STONE_SIZE - 1)||y > BOARD_SIZE + STONE_SIZE - 1)
	{
		return -1;	//Error
	}
	else
	{
		return (int)boolean[y + STONE_SIZE - 1][x + STONE_SIZE - 1];
	}
}
