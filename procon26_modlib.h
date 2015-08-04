#ifndef __DEF_LIB
#define __DEF_LIB

#include "procon26_module.h"

int countBit(unsigned char);	// Count-Bit
int countBitOfStone(const Stone *);// Count-Bit-Of-Stone
Stone *quarryStone(const Board *, int, int); // Cut-Stone
Stone *shiftUp(const Stone *, int, int filler = 0);		// Shift-Up
Stone *shiftDown(const Stone *, int, int filler = 0);		// Shift-Down
Stone *shiftRight(const Stone *, int, int filler = 0);		// Shift-Right
Stone *shiftLeft(const Stone *, int, int filler = 0);		// Shift-Left
Stone *turn(const Stone *, int);	// Turn-90 * n(deg)
Stone *turn90(const Stone *);		// Turn-90  (deg)
Stone *turn180(const Stone *);		// Turn-180 (deg)
Stone *turn270(const Stone *);		// Turn-270 (deg)
Stone *flip(const Stone *);		// flip
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
Board *placeStone(const Board *, const Stone *, int, int);
bool canPlace(const Board *, const Stone *, int, int);
int checkPlacingStone(const Board *, const Stone *, int, int);
bool isEqualStone(const Stone *, const Stone *);
Stone *cloneStone(const Stone *);
bool isEqualBoard(const Board *, const Board *);
Board *cloneBoard(const Board *);
inline bool getCellOfStone(const Stone *, int, int);
inline bool getCellOfBoard(const Board *, int, int);
inline void setCellOfStone(Stone *, int, int, bool);
inline void setCellOfBoard(Board *, int, int, bool);
void getGroupsCountStone(Stone *, bool target, int *groups_count, int *count);
int getGroupsCountStoneInternal(Stone *, Stone *, bool target, int x, int y);

#endif
