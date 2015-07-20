#include <iostream>
#define STONE_SIZE 8

#define block_0    "0"
#define block_1    "1"

using namespace std;

struct Stone
{
	unsigned char zuku[STONE_SIZE];
};

Stone inputStone()
{ 
	Stone ret = {{0,0,0,0,0,0,0,0}};
	for (int y = 0; y < STONE_SIZE; y++)
	{
		for (int x = 0; x < STONE_SIZE; x++)
		{
			char c;
			cin >> c;
			if (c != '0')
			{
				ret.zuku[y] += (0x80 >> x);
			}
		}
	}
	
	return ret;
}

void showStone(Stone *stone)
{
	for (int y = 0; y < STONE_SIZE; y++)
	{
		for (int x = 0; x < STONE_SIZE; x++)
		{
			cout << (((stone -> zuku[y] << x) & 0x80) ? block_1 : block_0);
		}
		cout << endl;
	}
	cout << endl;
}

void printStoneArray(Stone *stone)
{
	cout << "Stone s = {{" << endl;
	for (int y = 0; y < STONE_SIZE; y++)
	{
		cout << "\t";
		for (int x = 0; x < STONE_SIZE; x++)
		{
			cout << (((stone -> zuku[y] << x) & 0x80) ? "1" : "0");
			if (x != STONE_SIZE - 1) cout << ", ";
		}
		cout << endl;
	}
	cout << "}};" << endl;
}

int main()
{
	Stone s = inputStone();
	//showStone(&s);
	printStoneArray(&s);
	return 0;
}