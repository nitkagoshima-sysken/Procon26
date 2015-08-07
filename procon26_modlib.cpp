#include <vector>
#include "procon26_modlib.hpp"
#include "procon26_modio.hpp"

const Stone *EMPTY_STONE = getStoneByString("0000000000000000000000000000000000000000000000000000000000000000");
const Board *EMPTY_BOARD = getBoardByString(
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        );

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

int countBitOfBoard(const Board *board)
{
	int sum = 0;
	for (int y = 0; y < BOARD_SIZE ; y++)
	{
		for (int i = 0; i < 4; i++)
		{
			sum += countBit(board->block[i + y * 4]);
		}
	}
	return sum;
}

Stone *quarryStone(const Board *board, int x, int y, bool filler)
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
	if(x < 0){ tmp = shiftRight(quarried, -x, filler); delete quarried; quarried = tmp;}
	else if(x > BOARD_SIZE - STONE_SIZE){ tmp = shiftLeft(quarried, x - BOARD_SIZE + STONE_SIZE, filler); delete quarried; quarried = tmp;}
	if(y < 0){ tmp = shiftDown(quarried, -y, filler); delete quarried; quarried = tmp;}
	else if(y > BOARD_SIZE - STONE_SIZE){ tmp = shiftUp(quarried, y - BOARD_SIZE + STONE_SIZE, filler); delete quarried; quarried = tmp;}
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

Stone *rotate(const Stone *stone, int n)
{
	switch(n % 4)
	{
		case 1:
			// rotate90
			return rotate90(stone);
			
		case 2:
			// rotate180
			return rotate180(stone);
		
		case 3:
			// rotate270
			return rotate270(stone);
		
		default:
			return cloneStone(stone);
	}
}

Stone *rotate90(const Stone *stone)
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

Stone *rotate180(const Stone *stone)
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

Stone *rotate270(const Stone *stone)
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

bool isEmptyStone(const Stone *stone)
{
	for(int i = 0; i < STONE_SIZE; i ++)
	{
		if(stone->zuku[i] != 0) return false;
	}
	return true;
}

bool isEmptyBoard(const Board *board)
{
	for (int y = 0; y < BOARD_SIZE ; y++)
	{
		for (int i = 0; i < 4; i++)
		{
			if(board->block[i + y * 4] != 0) return false;
		}
	}
	return true;
}

Stone *getTouchingStone(const Board *board, const Stone *stone, int x, int y, bool filler)
{
    Stone *center = quarryStone(board, x, y, filler);
    Stone *a, *b, *c, *d, *e, *f, *g;
    Stone *result = AND(
            g = OR(
                e = OR(
                    a = quarryStone(board, x - 1, y, filler),
                    b = quarryStone(board, x + 1, y, filler)),
                f = OR(
                    c = quarryStone(board, x, y - 1, filler),
                    d = quarryStone(board, x, y + 1, filler))),
            stone);
    delete a; delete b; delete c; delete d; delete e; delete f; delete g;
    return result;
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

bool canPlace(const Board *board, const Board *board_diff, const Stone *stone, int x, int y, bool first)
{
    Stone *a, *b, *c;
    if(isEmptyStone(a = AND(stone, b = quarryStone(board, x, y)))){
        delete a; delete b;
        if(first){
            return true;
        }else if(! isEmptyStone(c = getTouchingStone(board_diff, stone, x, y, 1))){
            delete c;
            return true;
        }
    }
    return false;
}

/*
 * その場所にブロックが置ける時はいくつのブロックが触れているかを返す
 * おけない時には-1を返す
 * board_diffにはこれまで置いたブロックのみのボードを渡す
*/
int checkPlacingStone(const Board *board, const Board *board_diff, const Stone *stone, int x, int y)
{
	if(! canPlace(board, board_diff, stone, x, y)) return -1;
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

void getGroupsCountStone(Stone *stone, bool target, int *groups_count, int *count)
{
    *groups_count = *count = 0;
    Stone *done = cloneStone(EMPTY_STONE);
    int tmp_count;
    for(int x = 0; x < STONE_SIZE; x ++){
        for(int y = 0; y < STONE_SIZE; y ++){
            tmp_count = getGroupsCountStoneInternal(stone, done, target, x, y);
            if(tmp_count != 0){
                (*groups_count) ++;
                (*count) += tmp_count;
            }
        }
    }
    delete done;
}

int getGroupsCountStoneInternal(Stone *stone, Stone *done, bool target, int x, int y)
{
    if(x < 0 || y < 0 || x >= STONE_SIZE || y >= STONE_SIZE) return 0;
    if(getCellOfStone(done, x, y)) return 0;
    setCellOfStone(done, x, y, true);
    if(getCellOfStone(stone, x, y) == target)
        return 1 +
            getGroupsCountStoneInternal(stone, done, target, x - 1, y) +
            getGroupsCountStoneInternal(stone, done, target, x + 1, y) +
            getGroupsCountStoneInternal(stone, done, target, x, y - 1) +
            getGroupsCountStoneInternal(stone, done, target, x, y + 1);
    else
        return 0;
}

void getGroupsCountBoard(Board *board, bool target, int *groups_count, int *count)
{
    *groups_count = *count = 0;
    Board *done = cloneBoard(EMPTY_BOARD);
    int tmp_count;
    for(int x = 0; x < BOARD_SIZE; x ++){
        for(int y = 0; y < BOARD_SIZE; y ++){
            tmp_count = getGroupsCountBoardInternal(board, done, target, x, y);
            if(tmp_count != 0){
                (*groups_count) ++;
                (*count) += tmp_count;
            }
        }
    }
    delete done;
}

int getGroupsCountBoardInternal(Board *board, Board *done, bool target, int x, int y)
{
    if(x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE) return 0;
    if(getCellOfBoard(done, x, y)) return 0;
    setCellOfBoard(done, x, y, true);
    if(getCellOfBoard(board, x, y) == target)
        return 1 +
            getGroupsCountBoardInternal(board, done, target, x - 1, y) +
            getGroupsCountBoardInternal(board, done, target, x + 1, y) +
            getGroupsCountBoardInternal(board, done, target, x, y - 1) +
            getGroupsCountBoardInternal(board, done, target, x, y + 1);
    else
        return 0;
}

void getGroupsStone(Stone *stone, bool target, std::vector<Stone *> &stones, int *groups_count, int *count)
{
    *groups_count = *count = 0;
    Stone *done = cloneStone(EMPTY_STONE);
    Stone *result = cloneStone(EMPTY_STONE);
    int tmp_count;
    for(int x = 0; x < STONE_SIZE; x ++){
        for(int y = 0; y < STONE_SIZE; y ++){
            tmp_count = getGroupsStoneInternal(stone, done, result, target, x, y);
            if(tmp_count != 0){
                stones.push_back(result);
                result = cloneStone(EMPTY_STONE);
                (*groups_count) ++;
                (*count) += tmp_count;
            }
        }
    }
    if(isEmptyStone(result)) delete result;
}

int getGroupsStoneInternal(Stone *stone, Stone *done, Stone *result, bool target, int x, int y)
{
    if(x < 0 || y < 0 || x >= STONE_SIZE || y >= STONE_SIZE) return 0;
    if(getCellOfStone(done, x, y)) return 0;
    setCellOfStone(done, x, y, true);
    if(getCellOfStone(stone, x, y) == target){
        setCellOfStone(result, x, y, true);
        return 1 +
            getGroupsStoneInternal(stone, done, result, target, x - 1, y) +
            getGroupsStoneInternal(stone, done, result, target, x + 1, y) +
            getGroupsStoneInternal(stone, done, result, target, x, y - 1) +
            getGroupsStoneInternal(stone, done, result, target, x, y + 1);
    }else{
        return 0;
    }
}

void getGroupsBoard(Board *board, bool target, std::vector<Board *> &boards, int *groups_count, int *count)
{
    *groups_count = *count = 0;
    Board *done = cloneBoard(EMPTY_BOARD);
    Board *result = cloneBoard(EMPTY_BOARD);
    int tmp_count;
    for(int x = 0; x < BOARD_SIZE; x ++){
        for(int y = 0; y < BOARD_SIZE; y ++){
            tmp_count = getGroupsBoardInternal(board, done, result, target, x, y);
            if(tmp_count != 0){
                boards.push_back(result);
                result = cloneBoard(EMPTY_BOARD);
                (*groups_count) ++;
                (*count) += tmp_count;
            }
        }
    }
    if(isEmptyBoard(result)) delete result;
}

int getGroupsBoardInternal(Board *board, Board *done, Board *result, bool target, int x, int y)
{
    if(x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE) return 0;
    if(getCellOfBoard(done, x, y)) return 0;
    setCellOfBoard(done, x, y, true);
    if(getCellOfBoard(board, x, y) == target){
        setCellOfBoard(result, x, y, true);
        return 1 +
            getGroupsBoardInternal(board, done, result, target, x - 1, y) +
            getGroupsBoardInternal(board, done, result, target, x + 1, y) +
            getGroupsBoardInternal(board, done, result, target, x, y - 1) +
            getGroupsBoardInternal(board, done, result, target, x, y + 1);
    }else{
        return 0;
    }
}

Stone *normalizeStone(const Stone *stone)
{
    Stone *source = cloneStone(stone), *shifted1, *shifted2;
    while(true){
        shifted1 = shiftLeft(source, 1);
        shifted2 = shiftRight(shifted1, 1);
        if(! isEqualStone(source, shifted2)){
            delete shifted1; delete shifted2;
            break;
        }
        delete source;
        delete shifted2;
        source = shifted1;
    }
    while(true){
        shifted1 = shiftUp(source, 1);
        shifted2 = shiftDown(shifted1, 1);
        if(! isEqualStone(source, shifted2)){
            delete shifted1; delete shifted2;
            break;
        }
        delete source;
        delete shifted2;
        source = shifted1;
    }
    return source;
}

void getStatesOfStone(const Stone *source, std::vector<Stone *> &states)
{
    Stone *stone, *stone90, *stone180, *stone270, *flipped_stone, *flipped_stone90, *flipped_stone180, *flipped_stone270;
    Stone *stone_n, *stone90_n, *stone180_n, *stone270_n, *flipped_stone_n, *flipped_stone90_n, *flipped_stone180_n, *flipped_stone270_n;
    stone = cloneStone(source); stone_n = normalizeStone(stone);
    stone90 = rotate90(stone); stone90_n = normalizeStone(stone90);
    stone180 = rotate180(stone); stone180_n = normalizeStone(stone180);
    stone270 = rotate270(stone); stone270_n = normalizeStone(stone270);
    flipped_stone = flip(stone); flipped_stone_n = normalizeStone(flipped_stone);
    if(isEqualStone(stone_n, flipped_stone_n)){
        if(isEqualStone(stone_n, stone90_n)){
            states.push_back(stone);
            delete stone90; delete stone180; delete stone270; delete flipped_stone;
            delete stone_n; delete stone90_n; delete stone180_n; delete stone270_n;
        }else if(isEqualStone(stone_n, stone180_n)){
            states.push_back(stone); states.push_back(stone90);
            delete stone180; delete stone270; delete flipped_stone;
            delete stone_n; delete stone90_n; delete stone180_n; delete stone270_n;
        }else{
            states.push_back(stone); states.push_back(stone90); states.push_back(stone180); states.push_back(stone270);
            delete flipped_stone;
            delete stone_n; delete stone90_n; delete stone180_n; delete stone270_n;
        }
    }else{
        if(isEqualStone(stone_n, stone90_n)){
            states.push_back(stone); states.push_back(flipped_stone);
            delete stone90; delete stone180; delete stone270;
            delete stone_n; delete stone90_n; delete stone180_n; delete stone270_n;
        }else if(isEqualStone(stone_n, stone180_n)){
            states.push_back(stone); states.push_back(stone90); states.push_back(flipped_stone); states.push_back(rotate90(flipped_stone));
            delete stone180; delete stone270;
            delete stone_n; delete stone90_n; delete stone180_n; delete stone270_n;
        }else{
            states.push_back(stone); states.push_back(stone90); states.push_back(stone180); states.push_back(stone270);
            states.push_back(flipped_stone); states.push_back(rotate90(flipped_stone)); states.push_back(rotate180(flipped_stone)); states.push_back(rotate270(flipped_stone));
            delete stone_n; delete stone90_n; delete stone180_n; delete stone270_n;
        }
    }
}
