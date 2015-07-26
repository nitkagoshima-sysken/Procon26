#pragma once

#define STONE_SIZE 8
#define block_0    "0"
#define block_1    "1"
#define BOARD_SIZE 32

struct Stone
{
	unsigned char zuku[STONE_SIZE];
};

struct Board
{
	unsigned char block[128];
};

/* Definition */
Stone *getStoneByString(std::string);
Board *getBoardByString(std::string board);
void showStone(const Stone *);
void showBoard(const Board *);
int countBit(unsigned char);	// Count-Bit
int countBitOfStone(const Stone *stone);// Count-Bit-Of-Stone
Stone *quarryStone(const Board *, int, int); // Cut-Stone
Stone *shiftUp(const Stone *, int times);		// Shift-Up
Stone *shiftDown(const Stone *, int times);		// Shift-Down
Stone *shiftRight(const Stone *, int times);		// Shift-Right
Stone *shiftLeft(const Stone *, int times);		// Shift-Left
Stone *turn90(const Stone *);			// Turn-90  (deg)
Stone *shiftUp(const Stone *);		// Shift-Up
Stone *shiftDown(const Stone *);	// Shift-Down
Stone *shiftRight(const Stone *);	// Shift-Right
Stone *shiftLeft(const Stone *);	// Shift-Left
Stone *turn(const Stone *, int);	// Turn-90 * n(deg)
Stone *turn90(const Stone *);		// Turn-90  (deg)
Stone *turn180(const Stone *);		// Turn-180 (deg)
Stone *turn270(const Stone *);		// Turn-270 (deg)
Stone *reverce(const Stone *);		// Reverce
Stone *NOT(const Stone *);			// Logic-NOT
Stone *AND(const Stone *, const Stone *);	// Logic-AND
Stone *OR(const Stone *, const Stone *);	// Logic-OR
Stone *XOR(const Stone *, const Stone *);	// Logic-XOR
inline Stone *operator~(Stone);		// Operation Overlord Logic-NOT
inline Stone *operator&(Stone, Stone);	// Operation Overlord Logic-AND
inline Stone *operator|(Stone, Stone);	// Operation Overlord Logic-OR
inline Stone *operator^(Stone, Stone);	// Operation Overlord Logic-XOR
bool isEmptyStone(const Stone *);
Stone *getTouchingStone(const Board *, const Stone *, int, int);
bool canPlace(const Board *, const Stone *, int, int);
int checkPlacingStone(const Board *, const Stone *, int, int);
bool checkEqual(const Stone *, const Stone *);
