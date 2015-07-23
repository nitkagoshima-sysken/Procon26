#include <iostream>
#include "procon26_module.h"

using namespace std;

/* Constants */
const Stone *EMPTY_STONE = new Stone;

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

int countBit(unsigned char bit)
{
	bit = ((bit & 0xAA) >> 1) + (bit & 0x55);
	bit = ((bit & 0xCC) >> 2) + (bit & 0x33);
	bit = ((bit & 0xF0) >> 4) + (bit & 0x0F);
	return bit;
}

int countBitOfStone(const Stone *stone)
{
	int sum = 0;
	for(int i = 0; i < STONE_SIZE; i ++){
		sum += countBit(stone->zuku[i]);
	}
	return sum;
}

Stone *quarryStone(const Board *board, int x, int y)
{
	Stone *quarried = new Stone;
	for(int i = 0; i < 8; i++)
	{
		quarried->zuku[i] = board->block[x / 8 + y + (i * 4)] << (x % 8) | board->block[x / 8 + y + (i * 4) + 1] >> (8 - (x % 8));
	}
	return quarried;
}

Stone *shiftUp(const Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE - 1; i++)
	{
		dist->zuku[i] = stone->zuku[i + 1];
	}
	dist->zuku[STONE_SIZE - 1] = 0;
	
	return dist;
}

Stone *shiftDown(const Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = STONE_SIZE - 1; i > 0; i--)
	{
		dist->zuku[i] = stone->zuku[i - 1];
	}
	dist->zuku[0] = 0;
	
	return dist;
}

Stone *shiftRight(const Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE; i++)
	{
		dist->zuku[i] = (stone->zuku[i] >> 1);
	}
	return dist;
}

Stone *shiftLeft(const Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE; i++)
	{
		dist->zuku[i] = (stone->zuku[i] << 1);
	}
	return dist;
}

Stone *turn90(const Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE; i++) dist->zuku[i] = 0;
	
	for (int i = 0; i < 64; i++)
	{
		int x = i % STONE_SIZE;
		int y = i / STONE_SIZE;
		
		int nx = STONE_SIZE - 1 - y;
		int ny = x;
		
		if ((stone->zuku[y] << x) & 128)
		{
			dist->zuku[ny] += 128 >> nx;
		}
	}
	
	return dist;
}

Stone *turn180(const Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE; i++) dist->zuku[i] = 0;
	
	for (int i = 0; i < 64; i++)
	{
		int x = i % STONE_SIZE;
		int y = i / STONE_SIZE;
		
		int nx = STONE_SIZE - 1 - x;
		int ny = STONE_SIZE - 1 - y;
		
		if ((stone->zuku[y] << x) & 128)
		{
			dist->zuku[ny] += 128 >> nx;
		}
	}
	
	return dist;
}

Stone *turn270(const Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE; i++) dist->zuku[i] = 0;
	
	for (int i = 0; i < 64; i++)
	{
		int x = i % STONE_SIZE;
		int y = i / STONE_SIZE;
		
		int nx = y;
		int ny = STONE_SIZE - 1 - x;
		
		if ((stone->zuku[y] << x) & 128)
		{
			dist->zuku[ny] += 128 >> nx;
		}
	}
	
	return dist;
}

Stone *reverce(const Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE; i++) dist->zuku[i] = 0;

	for (int i = 0; i < 64; i++)
	{
		int x = i % STONE_SIZE;
		int y = i / STONE_SIZE;

		int nx = STONE_SIZE - 1 - x;
		int ny = y;

		if ((stone->zuku[y] << x) & 128)
		{
			dist->zuku[ny] += 128 >> nx;
		}
	}

	return dist;
}

Stone *NOT(const Stone *stone)
{
	Stone *resultStone = new Stone;
	for(int i = 0; i < STONE_SIZE; i++)
	{
		resultStone->zuku[i] = ~stone->zuku[i];
	}
	return resultStone;
}

Stone *AND(const Stone *stone1, const Stone *stone2)
{
	Stone *resultStone = new Stone;
	for(int i = 0; i < STONE_SIZE; i++)
	{
		resultStone->zuku[i] = stone1->zuku[i] & stone2->zuku[i];
	}
	return resultStone;
}

Stone *OR(const Stone *stone1, const Stone *stone2)
{
	Stone *resultStone = new Stone;
	for(int i = 0; i < STONE_SIZE; i++)
	{
		resultStone->zuku[i] = stone1->zuku[i] | stone2->zuku[i];
	}
	return resultStone;
}

Stone *XOR(const Stone *stone1, const Stone *stone2)
{
	Stone *resultStone = new Stone;
	for(int i = 0; i < STONE_SIZE; i++)
	{
		resultStone->zuku[i] = stone1->zuku[i] ^ stone2->zuku[i];
	}
	return resultStone;
}

inline Stone *operator~(Stone stone)
{
	return NOT(&stone); 
}

inline Stone *operator&(Stone stone1, Stone stone2)
{
	return AND(&stone1, &stone2);
}

inline Stone *operator|(Stone stone1, Stone stone2)
{
	return OR(&stone1, &stone2);
}

inline Stone *operator^(Stone stone1, Stone stone2)
{
	return XOR(&stone1, &stone2);
}

bool isEmptyStone(const Stone *stone)
{
	for(int i = 0; i < STONE_SIZE; i ++)
	{
		if(stone->zuku[i] != 0) return false;
	}
	return true;
}

Stone *getTouchingStone(const Board *board, const Stone *stone, int x, int y)
{
	Stone *center = quarryStone(board, x, y);
	return AND(
			XOR(
				center,
				OR(
					OR(
						x == 0 ? shiftLeft(center) : quarryStone(board, x - 1, y),
						x == BOARD_SIZE - STONE_SIZE - 1 ? shiftRight(center) : quarryStone(board, x + 1, y)),
					OR(
						y == 0 ? shiftUp(center) : quarryStone(board, x, y - 1),
						y == BOARD_SIZE - STONE_SIZE - 1 ? shiftDown(center) : quarryStone(board, x, y + 1)))),
			stone);
}

bool canPlace(const Board *board, const Stone *stone, int x, int y)
{
	if(isEmptyStone(*stone & *quarryStone(board, x, y))) return true;
	return false;
}

/*
 * その場所にブロックが置ける時はいくつのブロックが触れているかを返す
 * おけない時には-1を返す
*/
int checkPlacingStone(const Board *board, const Stone *stone, int x, int y)
{
	if(! canPlace(board, stone, x, y)) return -1;
	return countBitOfStone(getTouchingStone(board, stone, x, y));
}

bool checkEqual(const Stone *stone1, const Stone *stone2)
{
	for(int i = 0; i < STONE_SIZE; i ++)
	{
		if(stone1->zuku[i] != stone2->zuku[i]) return false;
	}
	return true;
}
