#ifndef __DEF_LIB
#define __DEF_LIB

#include "procon26_module.h"

extern int countBit(unsigned char);	// Count-Bit
extern int countBitOfStone(const Stone *);// Count-Bit-Of-Stone
extern Stone *quarryStone(const Board *, int, int); // Cut-Stone
extern Stone *shiftUp(const Stone *, int, int filler = 0);		// Shift-Up
extern Stone *shiftDown(const Stone *, int, int filler = 0);		// Shift-Down
extern Stone *shiftRight(const Stone *, int, int filler = 0);		// Shift-Right
extern Stone *shiftLeft(const Stone *, int, int filler = 0);		// Shift-Left
extern Stone *turn(const Stone *, int);	// Turn-90 * n(deg)
extern Stone *turn90(const Stone *);		// Turn-90  (deg)
extern Stone *turn180(const Stone *);		// Turn-180 (deg)
extern Stone *turn270(const Stone *);		// Turn-270 (deg)
extern Stone *flip(const Stone *);		// flip
extern Stone *NOT(const Stone *);			// Logic-NOT
extern Stone *AND(const Stone *, const Stone *);	// Logic-AND
extern Stone *OR(const Stone *, const Stone *);	// Logic-OR
extern Stone *XOR(const Stone *, const Stone *);	// Logic-XOR
extern Stone *operator~(Stone);		// Operation Overlord Logic-NOT
extern Stone *operator&(Stone, Stone);	// Operation Overlord Logic-AND
extern Stone *operator|(Stone, Stone);	// Operation Overlord Logic-OR
extern Stone *operator^(Stone, Stone);	// Operation Overlord Logic-XOR
extern bool isEmptyStone(const Stone *);
extern Stone *getTouchingStone(const Board *, const Stone *, int, int);
extern Board *placeStone(const Board *, const Stone *, int, int);
extern bool canPlace(const Board *, const Stone *, int, int);
extern int checkPlacingStone(const Board *, const Stone *, int, int);
extern bool isEqualStone(const Stone *, const Stone *);
extern Stone *cloneStone(const Stone *);
extern bool isEqualBoard(const Board *, const Board *);
extern Board *cloneBoard(const Board *);
extern bool getCellOfStone(const Stone *, int, int);
extern bool getCellOfBoard(const Board *, int, int);
extern void setCellOfStone(Stone *, int, int, bool);
extern void setCellOfBoard(Board *, int, int, bool);
extern void getGroupsCountStone(Stone *, bool target, int *groups_count, int *count);
extern int getGroupsCountStoneInternal(Stone *, Stone *, bool target, int x, int y);

#endif
