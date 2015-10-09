#include <iostream>
#include <fstream>
#include "../procon26_modlib.hpp"
#include "../procon26_modio.hpp"

using namespace std;

int main()
{
	Board *obstacleBoard;			// 現在のボードの状態を保持
	Board *putBoard = new Board;	// 今までに置いた石だけを保持

	// 解答出力用ファイルストリーム
	ofstream ofs("answer.txt");
	
	// 初期化
	for (int i = 0; i < 128; i++) putBoard->block[i] = 0;
	
	// 問題読み込み
	string filePath;
	cin >> filePath;
	Problem *prob = readProblem(filePath);
	
	obstacleBoard = cloneBoard(&prob->board);
	
	//showBoard(obstacleBoard);
	
	// 実際に解く
	bool *isPut = new bool[prob->num];
	for (int i = 0; i < prob->num; i++) isPut[i] = false;
	
	// 一個目の石は適当に置く
	for (int y = -STONE_SIZE + 1; y < BOARD_SIZE; y++)
	{
		for (int x = -STONE_SIZE + 1; x < BOARD_SIZE; x++)
		{
			if (!isPut[0] && canPlace(obstacleBoard, putBoard, &prob->stones[0], x, y, true))
			{
				obstacleBoard = placeStone(obstacleBoard, rotate(&prob->stones[0], 0), x, y);
				putBoard = placeStone(putBoard, &prob->stones[0], x, y);	
				isPut[0] = true;
				cout << x << " " << y << " " << "H" << " " << 0 << endl;
				ofs << x << " " << y << " " << "H" << " " << 0 << endl;
				//showBoard(obstacleBoard);
				//showBoard(putBoard);
			}
		}
	}
	
	// 二個目以降の石はより多く接するように置く
	for (int i = 1; i < prob->num; i++)
	{
		// たくさん接した座標、反転、回転を記憶
		int touching = -1, bestX, bestY, rotate;
		bool canPut = false, flipped = false;
		
		for (int y = -STONE_SIZE + 1; y < BOARD_SIZE; y++)
		{
			for (int x = -STONE_SIZE + 1; x < BOARD_SIZE; x++)
			{
				// 回転(反転なし)
				for (int j = 0; j < 4; j++)
				{
					int toutchNum = checkPlacingStone(obstacleBoard, putBoard, rotate(&prob->stones[i], j), x, y);
					if (!isPut[i] && (toutchNum != -1))
					{
						if (touching < toutchNum)
						{
							touching = toutchNum;
							bestX = x;
							bestY = y;
							rotate = j;
							canPut = true;
							flipped = false;
						}
					}
				}
				
				// 回転(反転あり)
				for (int j = 0; j < 4; j++)
				{
					int toutchNum = checkPlacingStone(obstacleBoard, putBoard, rotate(flip(&prob->stones[i]), j), x, y);
					if (!isPut[i] && (toutchNum != -1))
					{
						if (touching < toutchNum)
						{
							touching = toutchNum;
							bestX = x;
							bestY = y;
							rotate = j;
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
				obstacleBoard = placeStone(obstacleBoard, rotate(&prob->stones[i], rotate), bestX, bestY);
				putBoard      = placeStone(putBoard, rotate(&prob->stones[i], rotate), bestX, bestY);
			}
			else
			{
				obstacleBoard = placeStone(obstacleBoard, rotate(flip(&prob->stones[i]), rotate), bestX, bestY);
				putBoard      = placeStone(putBoard, rotate(flip(&prob->stones[i]), rotate), bestX, bestY);
			}
			
			cout << bestX << " " << bestY << " " << (flipped?"T":"H") << " " << rotate * 90 << endl;
			ofs << bestX << " " << bestY << " " << (flipped?"T":"H") << " " << rotate * 90 << endl;
			
			//showBoard(putBoard);
			
			isPut[i] = true;
		}
		else
		{
			cout << endl;
			ofs << endl;
		}
	}
	
	// メモリ解放
	delete   obstacleBoard;
	delete   putBoard;
	delete   prob;
	delete[] isPut;
	
	return 0;
}
