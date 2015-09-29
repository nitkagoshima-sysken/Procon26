#ifndef __DEF_IO
#define __DEF_IO

#include "procon26_module.hpp"

#define block_0    "0"
#define block_1    "1"

extern Stone *getStoneByString(std::string);
extern Board *getBoardByString(std::string);
extern void showStone(const Stone *);
extern void showBoard(const Board *);
extern void inputBoard(Board *board);
extern void inputStone(Stone *stones, int n);

#endif
