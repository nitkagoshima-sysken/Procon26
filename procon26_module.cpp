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

/* Definition */
void showStone(Stone *);
int bitCount(unsigned char);// Count-Bit 
Stone cutBoard(Board *, int, int); // Cut-Stone
Stone shift_up(Stone);		// Shift-Up
Stone shift_down(Stone);	// Shift-Down
Stone shift_right(Stone);	// Shift-Right
Stone shift_left(Stone);	// Shift-Left
Stone turn_90(Stone);		// Turn-90  (deg) 
Stone turn_180(Stone);		// Turn-180 (deg)
Stone turn_270(Stone);		// Turn-270 (deg)
Stone reverce(Stone);		// Reverce
Stone NOT(Stone);			// Logic-NOT 
Stone AND(Stone, Stone);	// Logic-AND
Stone  OR(Stone, Stone);	// Logic-OR
Stone XOR(Stone, Stone);	// Logic-XOR

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

int bitCount(unsigned char bit)
{
	bit = ((bit & 0xAA) >> 1) + (bit & 0x55);
	bit = ((bit & 0xCC) >> 2) + (bit & 0x33);
	bit = ((bit & 0xF0) >> 4) + (bit & 0x0F);
	return bit;
}

Stone cutBoard(Board *board, int x, int y)
{
	Stone Cut;
	
	for(int i = 0; i < 8; i++)
	{
		Cut.zuku[i] = board.block[x / 8 + y + (i * 4)] << (x % 8) | board.block[x / 8 + y + (i * 4) + 1] >> (8 - (x % 8));
	}
	
	return Cut;
}

Stone shift_up(Stone stone)
{
	for (int i = 0; i < STONE_SIZE - 1; i++)
	{
		stone.zuku[i] = stone.zuku[i + 1];
	}
	stone.zuku[STONE_SIZE - 1] = 0;
	
	return stone;
}

Stone shift_down(Stone stone)
{
	for (int i = STONE_SIZE - 1; i > 0; i--)
	{
		stone.zuku[i] = stone.zuku[i - 1];
	}
	stone.zuku[0] = 0;
	
	return stone;
}

Stone shift_right(Stone stone)
{
	for (int i = 0; i < STONE_SIZE; i++)
	{
		stone.zuku[i] = (stone.zuku[i] >> 1);
	}
	return stone;
}

Stone shift_left(Stone stone)
{
	for (int i = 0; i < STONE_SIZE; i++)
	{
		stone.zuku[i] = (stone.zuku[i] << 1);
	}
	return stone;
}

Stone turn90(Stone stone)
{
	Stone dist;
	for (int i = 0; i < STONE_SIZE; i++) dist.zuku[i] = 0;
	
	for (int i = 0; i < 64; i++)
	{
		int x = i % STONE_SIZE;
		int y = i / STONE_SIZE;
		
		int nx = STONE_SIZE - 1 - y;
		int ny = x;
		
		if ((stone.zuku[y] << x) & 128)
		{
			dist.zuku[ny] += 128 >> nx;
		}
	}
	
	return dist;
}

Stone turn180(Stone stone)
{
	Stone dist;
	for (int i = 0; i < STONE_SIZE; i++) dist.zuku[i] = 0;
	
	for (int i = 0; i < 64; i++)
	{
		int x = i % STONE_SIZE;
		int y = i / STONE_SIZE;
		
		int nx = STONE_SIZE - 1 - x;
		int ny = STONE_SIZE - 1 - y;
		
		if ((stone.zuku[y] << x) & 128)
		{
			dist.zuku[ny] += 128 >> nx;
		}
	}
	
	return dist;
}

Stone turn270(Stone stone)
{
	Stone dist;
	for (int i = 0; i < STONE_SIZE; i++) dist.zuku[i] = 0;
	
	for (int i = 0; i < 64; i++)
	{
		int x = i % STONE_SIZE;
		int y = i / STONE_SIZE;
		
		int nx = y;
		int ny = STONE_SIZE - 1 - x;
		
		if ((stone.zuku[y] << x) & 128)
		{
			dist.zuku[ny] += 128 >> nx;
		}
	}
	
	return dist;
}

Stone reverce(Stone stone)
{
	Stone dist;
	for (int i = 0; i < STONE_SIZE; i++) dist.zuku[i] = 0;

	for (int i = 0; i < 64; i++)
	{
		int x = i % STONE_SIZE;
		int y = i / STONE_SIZE;

		int nx = STONE_SIZE - 1 - x;
		int ny = y;

		if ((stone.zuku[y] << x) & 128)
		{
			dist.zuku[ny] += 128 >> nx;
		}
	}

	return dist;
}

Stone NOT(Stone stone)
{
	for(int i = 0; i < STONE_SIZE; i++)
	{
		stone.zuku[i] = ~stone.zuku[i];
	}
	return stone;
}

Stone AND(Stone stone1, Stone stone2)
{
	for(int i = 0; i < STONE_SIZE; i++)
	{
		stone1.zuku[i] = stone1.zuku[i] & stone2.zuku[i];
	}
	return stone1;
}

Stone OR(Stone stone1, Stone stone2)
{
	for(int i = 0; i < STONE_SIZE; i++)
	{
		stone1.zuku[i] = stone1.zuku[i] | stone2.zuku[i];
	}
	return stone1;
}

Stone XOR(Stone stone1, Stone stone2)
{
	for(int i = 0; i < STONE_SIZE; i++)
	{
		stone1.zuku[i] = stone1.zuku[i] ^ stone2.zuku[i];
	}
	return stone1;
}
