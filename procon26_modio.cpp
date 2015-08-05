#include "Procon26_modio.hpp"
#include <iostream>

using namespace std;

/* Implementation */
Stone *getStoneByString(string stone)
{
	Stone *returnStone = new Stone;
	for (int y = 0; y < STONE_SIZE; y++)
	{
		returnStone->zuku[y] = 0;
		for (int x = 0; x < STONE_SIZE; x++)
		{
			char c = stone[x + y * STONE_SIZE];
			if (c != '0')
			{
				returnStone->zuku[y] += (0x80 >> x);
			}
		}
	}
	return returnStone;
}

Board *getBoardByString(string board)
{
	Board *returnBoard = new Board;
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int i = 0; i < 4; i++)
		{
			returnBoard->block[i + y * 4] = 0;
			for (int x = 0; x < 8; x++)
			{
				char c = board[x + 8 * i  + y * BOARD_SIZE];
				if (c != '0')
				{
					returnBoard->block[i + y * 4] += (0x80 >> x);
				}
			}
		}
	}
	return returnBoard;
}

void showStone(const Stone *stone)
{
	for (int y = 0; y < STONE_SIZE; y++)
	{
		for (int x = 0; x < STONE_SIZE; x++)
		{
			cout << (((stone -> zuku[y] << x) & 0x80) ? block_1 : block_0);
		}
		cout << endl;
	}
	cout << endl;
}

void showBoard(const Board *board)
{
	for (int y = 0; y < BOARD_SIZE ; y++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int x = 0; x < 8; x++)
			{
				cout << (((board -> block[i + y * 4] << x) & 0x80) ? block_1 : block_0);
			}
		}
		cout << endl;
	}
	cout << endl;
}

void inputBoard(Board *board)
{
	string data = "";
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		string str;
		cin >> str;
		data += str;
	}
	
	*board = *getBoardByString(data);
}

void inputStone(Stone *stones, int n)
{
	for (int i = 0; i < n; i++)
	{
		string data = "";
		for (int j = 0; j < STONE_SIZE; j++)
		{
			string str;
			cin >> str;
			data += str;
		}
		stones[i] = *getStoneByString(data);
	}
}
