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

/* 定義部 */
void showStone(Stone *);
int bitCount(unsigned char);// ビットを数える 
Stone cutBoard(Board *, int, int); // 石を切り取る
Stone shift_up(Stone);		// 上シフト
Stone shift_down(Stone);	// 下シフト
Stone shift_right(Stone);	// 右シフト
Stone shift_left(Stone);	// 左シフト
Stone turn_90(Stone);		// 90度回転 
Stone turn_180(Stone);		// 180度回転
Stone turn_270(Stone);		// 270度回転
Stone reverce(Stone);		// 反転

/* 実装部 */
void showStone(Stone *stone)
{
	for (int y = 0; y < STONE_SIZE; y++)
	{
		for (int x = 0; x < STONE_SIZE; x++)
		{
			cout << ((stone -> zuku[y] << x) & 0x80) ? block_1 : block_0;
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

Stone shift_up(Stone quest)
{
	for (int i = 0; i < STONE_SIZE - 1; i++)
	{
		quest.zuku[i] = quest.zuku[i + 1];
	}
	quest.zuku[STONE_SIZE - 1] = 0;
	
	return quest;
}

Stone shift_down(Stone quest)
{
	for (int i = STONE_SIZE - 1; i > 0; i--)
	{
		quest.zuku[i] = quest.zuku[i - 1];
	}
	quest.zuku[0] = 0;
	
	return quest;
}

Stone shift_right(Stone quest)
{
	for (int i = 0; i < STONE_SIZE; i++)
	{
		quest.zuku[i] = (quest.zuku[i] >> 1);
	}
	return quest;
}

Stone shift_left(Stone quest)
{
	for (int i = 0; i < STONE_SIZE; i++)
	{
		quest.zuku[i] = (quest.zuku[i] << 1);
	}
	return quest;
}

Stone turn90(Stone source)
{
	Stone dist;
	for (int i = 0; i < N; i++) dist.zuku[i] = 0;
	
	for (int i = 0; i < 64; i++)
	{
		int x = i % N;
		int y = i / N;
		
		int nx = N - 1 - y;
		int ny = x;
		
		if ((source.zuku[y] << x) & 128)
		{
			dist.zuku[ny] += 128 >> nx;
		}
	}
	
	return dist;
}

Stone turn180(Stone source)
{
	Stone dist;
	for (int i = 0; i < N; i++) dist.zuku[i] = 0;
	
	for (int i = 0; i < 64; i++)
	{
		int x = i % N;
		int y = i / N;
		
		int nx = N - 1 - x;
		int ny = N - 1 - y;
		
		if ((source.zuku[y] << x) & 128)
		{
			dist.zuku[ny] += 128 >> nx;
		}
	}
	
	return dist;
}

Stone turn270(Stone source)
{
	Stone dist;
	for (int i = 0; i < N; i++) dist.zuku[i] = 0;
	
	for (int i = 0; i < 64; i++)
	{
		int x = i % N;
		int y = i / N;
		
		int nx = y;
		int ny = N - 1 - x;
		
		if ((source.zuku[y] << x) & 128)
		{
			dist.zuku[ny] += 128 >> nx;
		}
	}
	
	return dist;
}

Stone reverce(Stone source)
{
	Stone dist;
	for (int i = 0; i < N; i++) dist.zuku[i] = 0;

	for (int i = 0; i < 64; i++)
	{
		int x = i % N;
		int y = i / N;

		int nx = N - 1 - x;
		int ny = y;

		if ((source.zuku[y] << x) & 128)
		{
			dist.zuku[ny] += 128 >> nx;
		}
	}

	return dist;
}