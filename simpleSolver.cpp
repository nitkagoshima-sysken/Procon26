#include <iostream>
#include "procon26_module.h"

using namespace std;

void inputBoard(Board *board)
{
	string data = "";
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		string str;
		cin >> str;
		data += str;
	}
	
	*board = *getBoardByString(data);
}

void inputStone(Stone *stones, int n)
{
	for (int i = 0; i < n; i++)
	{
		string data = "";
		for (int j = 0; j < STONE_SIZE; j++)
		{
			string str;
			cin >> str;
			data += str;
		}
		stones[i] = *getStoneByString(data);
	}
}

int main()
{
	Board *obstacleBoard = new Board;
	Board *putBoard = new Board;
	Stone *stones;
	
	// 初期化
	for (int i = 0; i < 128; i++) putBoard->block[i] = 0;
	
	// ボード読み込み
	inputBoard(obstacleBoard);
	
	// 石の数読み込み
	int n;
	cin >> n;
	stones = new Stone[n];
	
	// 石読み込み
	inputStone(stones, n);
	
	/*test*/
	cout << endl;
	cout << "showBoard" << endl;
	showBoard(obstacleBoard);
	/*test*/
	
	// 実際に解く
	bool *isPut = new bool[n];
	for (int i = 0; i < n; i++) isPut[i] = false;
	
	// 一個目の石は適当に置く
	for (int y = -STONE_SIZE + 1; y < BOARD_SIZE; y++)
	{
		for (int x = -STONE_SIZE + 1; x < BOARD_SIZE; x++)
		{
			if (!isPut[i] && canPlace(obstacleBoard, &stones[0], x, y))
			{
				/* ここにPut関数 ! */
				isPut[i] = true;
			}
		}
	}
	
	// 二個目以降の石はより多く接するように置く
	for (int i = 1; i < n; i++)
	{
		// たくさん接した座標、反転、回転を記憶
		int touching = 0, bestX, bestY, Turn;
		bool canPut = false, flipped = false;
		
		for (int y = -STONE_SIZE + 1; y < BOARD_SIZE; y++)
		{
			for (int x = -STONE_SIZE + 1; x < BOARD_SIZE; x++)
			{
				// 回転(反転なし)
				for (int j = 0; j < 4; j++)
				{
					int toutchNum_obstacle = checkPlacingStone(obstacleBoard, turn(&stones[i], j), x, y);
					int toutchNum_put      = checkPlacingStone(putBoard, turn(&stones[i], j), x, y);
					if ((toutchNum_obstacle != -1) && (toutchNum_put > 0))
					{
						if (touching < (toutchNum_obstacle + toutchNum_put))
						{
							touching = (toutchNum_obstacle + toutchNum_put);
							bestX = x;
							bestY = y;
							Turn = j;
							canPut = true;
							flipped = false;
						}
					}
				}
				
				// 回転(反転あり)
				for (int j = 0; j < 4; j++)
				{
					int toutchNum_obstacle = checkPlacingStone(obstacleBoard, turn(flip(&stones[i]), j), x, y);
					int toutchNum_put      = checkPlacingStone(putBoard, turn(flip(&stones[i]), j), x, y);
					if ((toutchNum_obstacle != -1) && (toutchNum_put > 0))
					{
						if (touching < (toutchNum_obstacle + toutchNum_put))
						{
							touching = (toutchNum_obstacle + toutchNum_put);
							bestX = x;
							bestY = y;
							Turn = j;
							canPut = true;
							flipped = true;
						}
					}
				}				
			}
		}
		
		if (canPut)
		{
			// 石を置く
			if (!flipped)
			{
				/* put(putBoard, turn(&stone[i], Turn), bestX, bestY) */	
			}
			else
			{
				/* put(putBoard, turn(flip(&stone[i]), Turn), bestX, bestY) */
			}
			cout << bestX << " " << bestY << " " << (flipped?"T":"H") << " " << Turn * 90 << endl;
		}
		else
		{
			cout << endl;
		}
	}
	
	// メモリ解放
	delete obstacleBoard;
	delete putBoard;
	delete[] stones;
	delete[] isPut;
	
	return 0;
}
