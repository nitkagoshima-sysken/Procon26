#include <iostream>
#include "../procon26_modlib.hpp"
#include "../procon26_modio.hpp"

using namespace std;

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
	//cout << endl;
	
	// 実際に解く
	bool *isPut = new bool[n];
	for (int i = 0; i < n; i++) isPut[i] = false;
	
	// 一個目の石は適当に置く
	for (int y = -STONE_SIZE + 1; y < BOARD_SIZE; y++)
	{
		for (int x = -STONE_SIZE + 1; x < BOARD_SIZE; x++)
		{
			if (!isPut[0] && canPlace(obstacleBoard, putBoard, &stones[0], x, y))
			{
				obstacleBoard = placeStone(obstacleBoard, turn(&stones[0], 0), x, y);
				putBoard = placeStone(putBoard, &stones[0], x, y);	
				isPut[0] = true;
				cout << x << " " << y << " " << "H" << " " << 0 << endl;
				//showBoard(putBoard);
			}
		}
	}
	
	// 二個目以降の石はより多く接するように置く
	for (int i = 1; i < n; i++)
	{
		// たくさん接した座標、反転、回転を記憶
		int touching = -1, bestX, bestY, Turn;
		bool canPut = false, flipped = false;
		
		for (int y = -STONE_SIZE + 1; y < BOARD_SIZE; y++)
		{
			for (int x = -STONE_SIZE + 1; x < BOARD_SIZE; x++)
			{
				// 回転(反転なし)
				for (int j = 0; j < 4; j++)
				{
					int toutchNum = checkPlacingStone(obstacleBoard, putBoard, turn(&stones[i], j), x, y);
					if (!isPut[i] && (toutchNum != -1))
					{
						if (touching < toutchNum)
						{
							touching = toutchNum;
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
					int toutchNum = checkPlacingStone(obstacleBoard, putBoard, turn(flip(&stones[i]), j), x, y);
					if (!isPut[i] && (toutchNum != -1))
					{
						if (touching < toutchNum)
						{
							touching = toutchNum;
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
				obstacleBoard = placeStone(obstacleBoard, turn(&stones[i], Turn), bestX, bestY);
				putBoard      = placeStone(putBoard, turn(&stones[i], Turn), bestX, bestY);
			}
			else
			{
				obstacleBoard = placeStone(obstacleBoard, turn(flip(&stones[i]), Turn), bestX, bestY);
				putBoard      = placeStone(putBoard, turn(flip(&stones[i]), Turn), bestX, bestY);
			}
			
			cout << bestX << " " << bestY << " " << (flipped?"T":"H") << " " << Turn * 90 << endl;
			
			//showBoard(putBoard);
			
			isPut[i] = true;
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
