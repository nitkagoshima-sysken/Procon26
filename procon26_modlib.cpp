#include "procon26_modlib.h"

/* Constants */
const Stone *EMPTY_STONE = new Stone;

/* Implementation */
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
	int qX = x, qY = y;
	Stone *tmp;
	if(x < 0) qX = 0;
	else if(x > BOARD_SIZE - STONE_SIZE) qX = BOARD_SIZE - STONE_SIZE;
	if(y < 0) qY = 0;
	else if(y > BOARD_SIZE - STONE_SIZE) qY = BOARD_SIZE - STONE_SIZE;
	Stone *quarried = new Stone;
	for(int i = 0; i < STONE_SIZE; i++)
	{
		quarried->zuku[i] = board->block[qX / STONE_SIZE + qY * (STONE_SIZE / 2) + (i * (STONE_SIZE / 2))] << (qX % STONE_SIZE) | board->block[qX / STONE_SIZE + qY * (STONE_SIZE / 2) + (i * (STONE_SIZE / 2)) + 1] >> (STONE_SIZE - (qX % STONE_SIZE));
	}
	if(x < 0){ tmp = shiftRight(quarried, -x, 1); delete quarried; quarried = tmp;}
	else if(x > BOARD_SIZE - STONE_SIZE){ tmp = shiftLeft(quarried, x - BOARD_SIZE + STONE_SIZE, 1); delete quarried; quarried = tmp;}
	if(y < 0){ tmp = shiftDown(quarried, -y, 1); delete quarried; quarried = tmp;}
	else if(y > BOARD_SIZE - STONE_SIZE){ tmp = shiftUp(quarried, y - BOARD_SIZE + STONE_SIZE, 1); delete quarried; quarried = tmp;}
	return quarried;
}

Stone *shiftUp(const Stone *stone, int times, int filler)
{
	Stone *dist = new Stone;
	for (int i = 0; i < STONE_SIZE - times; i++)
	{
		dist->zuku[i] = stone->zuku[i + times];
	}
	for (int i = STONE_SIZE - times; i < STONE_SIZE; i++)
	{
		dist->zuku[i] = (filler == 0) ? 0 : (unsigned char)0xFF;
	}
	
	return dist;
}

Stone *shiftDown(const Stone *stone, int times, int filler)
{
	Stone *dist = new Stone;
	for (int i = times; i < STONE_SIZE; i++)
	{
		dist->zuku[i] = stone->zuku[i - times];
	}
	for (int i = 0; i < times; i++)
	{
		dist->zuku[i] = (filler == 0) ? 0 : (unsigned char)0xFF;
	}
	
	return dist;
}

Stone *shiftRight(const Stone *stone, int times, int filler)
{
	Stone *dist = new Stone;
	unsigned char filler_char = (filler == 0) ? 0 : (unsigned char)0xFF << (STONE_SIZE - times);
	for (int i = 0; i < STONE_SIZE; i++)
	{
		dist->zuku[i] = (stone->zuku[i] >> times) | filler_char;
	}
	return dist;
}

Stone *shiftLeft(const Stone *stone, int times, int filler)
{
	Stone *dist = new Stone;
	unsigned char filler_char = (filler == 0) ? 0 : (unsigned char)0xFF >> (STONE_SIZE - times);
	for (int i = 0; i < STONE_SIZE; i++)
	{
		dist->zuku[i] = (stone->zuku[i] << times) | filler_char;
	}
	return dist;
}

Stone *turn(const Stone *stone, int n)
{
	switch(n % 4)
	{
		case 1:
			// turn90
			return turn90(stone);
			
		case 2:
			// turn180
			return turn180(stone);
		
		case 3:
			// turn270
			return turn270(stone);
		
		default:
			return cloneStone(stone);
	}
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

Stone *flip(const Stone *stone)
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
            OR(
                OR(
                    quarryStone(board, x - 1, y),
                    quarryStone(board, x + 1, y)),
                OR(
                    quarryStone(board, x, y - 1),
                    quarryStone(board, x, y + 1))),
            stone);
}

Board *placeStone(const Board *board, const Stone *stone, int x, int y)
{
    Stone *stone_copy = cloneStone(stone);
    Stone *tmp;
    if(x < 0){ tmp = shiftLeft(stone_copy, -x); delete stone_copy; stone_copy = tmp; x = 0;}
    else if(x > BOARD_SIZE - STONE_SIZE){ tmp = shiftRight(stone_copy, x - BOARD_SIZE + STONE_SIZE); delete stone_copy; stone_copy = tmp; x = BOARD_SIZE - STONE_SIZE;}
    if(y < 0){ tmp = shiftUp(stone_copy, -y); delete stone_copy; stone_copy = tmp; y = 0;}
    else if(y > BOARD_SIZE - STONE_SIZE){ tmp = shiftDown(stone_copy, y - BOARD_SIZE + STONE_SIZE); delete stone_copy; stone_copy = tmp; y = BOARD_SIZE - STONE_SIZE;}
    Board *new_board = cloneBoard(board);
    for(int i = 0; i < STONE_SIZE; i++)
    {
        new_board->block[x / STONE_SIZE + y * (STONE_SIZE / 2) + (i * (STONE_SIZE / 2))] |= stone_copy->zuku[i] >> (x % STONE_SIZE);
        new_board->block[x / STONE_SIZE + y * (STONE_SIZE / 2) + (i * (STONE_SIZE / 2)) + 1] |= stone_copy->zuku[i] << (STONE_SIZE - (x % STONE_SIZE));
    }
    delete stone_copy;
    return new_board;
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

bool isEqualStone(const Stone *stone1, const Stone *stone2)
{
	for(int i = 0; i < STONE_SIZE; i ++)
	{
		if(stone1->zuku[i] != stone2->zuku[i]) return false;
	}
	return true;
}

bool isEqualBoard(const Board *board1, const Board *board2)
{
    for (int y = 0; y < BOARD_SIZE ; y++)
    {
        for (int i = 0; i < 4; i++)
        {
            if(board1->block[i + y * 4] != board2->block[i + y * 4]) return false;
        }
    }
    return true;
}

Stone *cloneStone(const Stone *stone)
{
	Stone *clone = new Stone;
	for(int i = 0; i < STONE_SIZE; i ++)
	{
		clone->zuku[i] = stone->zuku[i];
	}
	return clone;
}

Board *cloneBoard(const Board *board)
{
    Board *new_board = new Board;
    for (int y = 0; y < BOARD_SIZE ; y++)
    {
        for (int i = 0; i < 4; i++)
        {
            new_board->block[i + y * 4] = board->block[i + y * 4];
        }
    }
    return new_board;
}

inline bool getCellOfStone(const Stone *stone, int x, int y)
{
    return (bool)(stone->zuku[y] & 0x80 >> x);
}

inline bool getCellOfBoard(const Board *board, int x, int y)
{
    return (bool)(board->block[x / 8 + y * 4] & 0x80 >> (x % 8));
}

inline void setCellOfStone(Stone *stone, int x, int y, bool value)
{
    if(value)
        stone->zuku[y] |= 0x80 >> x;
    else
        stone->zuku[y] &= ~(0x80 >> x);
}

inline void setCellOfBoard(Board *board, int x, int y, bool value)
{
    if(value)
        board->block[x / 8 + y * 4] |= 0x80 >> (x % 8);
    else
        board->block[x / 8 + y * 4] &= ~(0x80 >> (x % 8));
}
