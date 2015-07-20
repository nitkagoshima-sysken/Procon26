#include <iostream>

using namespace std;

#define STONE_SIZE 8
#define block_0    "0"
#define block_1    "1"

struct Stone
{
	unsigned char zuku[STONE_SIZE];
};

struct Board
{
	unsigned char block[128];
};

/* Constants */
const Stone *EMPTY_STONE = new Stone;

/* Definition */
void showStone(Stone *);
int countBit(unsigned char);// Count-Bit
int countBitOfStone(Stone *stone);// Count-Bit-Of-Stone
Stone *quarryStone(Board *, int, int); // Cut-Stone
Stone *shift_up(Stone *);		// Shift-Up
Stone *shift_down(Stone *);	// Shift-Down
Stone *shift_right(Stone *);	// Shift-Right
Stone *shift_left(Stone *);	// Shift-Left
Stone *turn_90(Stone *);		// Turn-90  (deg)
Stone *turn_180(Stone *);		// Turn-180 (deg)
Stone *turn_270(Stone *);		// Turn-270 (deg)
Stone *reverce(Stone *);		// Reverce
Stone *NOT(Stone *);			// Logic-NOT
Stone *AND(Stone *, Stone *);	// Logic-AND
Stone *OR(Stone *, Stone *);	// Logic-OR
Stone *XOR(Stone *, Stone *);	// Logic-XOR
bool isEmptyStone(Stone *);

/* Implementation */
void showStone(Stone *stone)
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

int countBitOfStone(Stone *stone)
{
	int sum = 0;
	for(int i = 0; i < STONE_SIZE; i ++){
		sum += countBit(stone->zuku[i]);
	}
	return sum;
}

Stone *quarryStone(Board *board, int x, int y)
{
	Stone *quarried = new Stone;
	for(int i = 0; i < 8; i++)
	{
		quarried->zuku[i] = board->block[x / 8 + y + (i * 4)] << (x % 8) | board->block[x / 8 + y + (i * 4) + 1] >> (8 - (x % 8));
	}
	return quarried;
}

Stone *shift_up(Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE - 1; i++)
	{
		dist->zuku[i] = stone->zuku[i + 1];
	}
	dist->zuku[STONE_SIZE - 1] = 0;
	
	return dist;
}

Stone *shift_down(Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = STONE_SIZE - 1; i > 0; i--)
	{
		dist->zuku[i] = stone->zuku[i - 1];
	}
	dist->zuku[0] = 0;
	
	return dist;
}

Stone *shift_right(Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE; i++)
	{
		dist->zuku[i] = (stone->zuku[i] >> 1);
	}
	return dist;
}

Stone *shift_left(Stone *stone)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE; i++)
	{
		dist->zuku[i] = (stone->zuku[i] << 1);
	}
	return dist;
}

Stone *turn90(Stone *stone)
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

Stone *turn180(Stone *stone)
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

Stone *turn270(Stone *stone)
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

Stone *reverce(Stone *stone)
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

Stone *NOT(Stone *stone)
{
	Stone *resultStone = new Stone;
	for(int i = 0; i < STONE_SIZE; i++)
	{
		resultStone->zuku[i] = ~stone->zuku[i];
	}
	return resultStone;
}

Stone *AND(Stone *stone1, Stone *stone2)
{
	Stone *resultStone = new Stone;
	for(int i = 0; i < STONE_SIZE; i++)
	{
		resultStone->zuku[i] = stone1->zuku[i] & stone2->zuku[i];
	}
	return resultStone;
}

Stone *OR(Stone *stone1, Stone *stone2)
{
	Stone *resultStone = new Stone;
	for(int i = 0; i < STONE_SIZE; i++)
	{
		resultStone->zuku[i] = stone1->zuku[i] | stone2->zuku[i];
	}
	return resultStone;
}

Stone *XOR(Stone *stone1, Stone *stone2)
{
	Stone *resultStone = new Stone;
	for(int i = 0; i < STONE_SIZE; i++)
	{
		resultStone->zuku[i] = stone1->zuku[i] ^ stone2->zuku[i];
	}
	return resultStone;
}

bool isEmptyStone(Stone *stone)
{
	for(int i = 0; i < STONE_SIZE; i ++)
	{
		if(stone->zuku[i] != 0) return false;
	}
	return true;
}
