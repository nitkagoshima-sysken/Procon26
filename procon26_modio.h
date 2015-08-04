#ifndef __DEF_IO
#define __DEF_IO

#include "procon26_module.h"

#define block_0    "0"
#define block_1    "1"

Stone *getStoneByString(std::string);
Board *getBoardByString(std::string);
void showStone(const Stone *);
void showBoard(const Board *);
void inputBoard(Board *board);
void inputStone(Stone *stones, int n);

#endif