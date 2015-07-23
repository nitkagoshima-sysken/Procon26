#include <iostream>
#include "../procon26_module.h"

using namespace std;

// 64文字の文字列を入力
Stone *getStoneByString(string stone)
{
	Stone *returnStone = new Stone;
	for (int y = 0; y < STONE_SIZE; y++)
	{
		returnStone->zuku[y] = 0;
		for (int x = 0; x < STONE_SIZE; x++)
		{
			char c = stone[x + y * STONE_SIZE];
			if (c != '0')
			{
				returnStone->zuku[y] += (0x80 >> x);
			}
		}
	}
	return returnStone;
}
