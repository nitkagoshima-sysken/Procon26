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
void showStone(Stone *);
int countBit(unsigned char);	// Count-Bit
int countBitOfStone(Stone *stone);// Count-Bit-Of-Stone
Stone *quarryStone(Board *, int, int); // Cut-Stone
Stone *shiftUp(Stone *);		// Shift-Up
Stone *shiftDown(Stone *);		// Shift-Down
Stone *shiftRight(Stone *);		// Shift-Right
Stone *shiftLeft(Stone *);		// Shift-Left
Stone *turn90(Stone *);			// Turn-90  (deg)
Stone *turn180(Stone *);		// Turn-180 (deg)
Stone *turn270(Stone *);		// Turn-270 (deg)
Stone *reverce(Stone *);		// Reverce
Stone *NOT(Stone *);			// Logic-NOT
Stone *AND(Stone *, Stone *);	// Logic-AND
Stone *OR(Stone *, Stone *);	// Logic-OR
Stone *XOR(Stone *, Stone *);	// Logic-XOR
inline Stone operator~(Stone);			// Operation Overlord Logic-NOT
inline Stone operator&(Stone, Stone);	// Operation Overlord Logic-AND
inline Stone operator|(Stone, Stone);	// Operation Overlord Logic-OR
inline Stone operator^(Stone, Stone);	// Operation Overlord Logic-XOR
bool isEmptyStone(Stone *);
Stone *getTouchingStone(Board *, Stone *, int, int);
bool canPlace(Board *, Stone *, int, int);
int checkPlacingStone(Board *, Stone *, int, int);
bool checkEqual(Stone *, Stone *);