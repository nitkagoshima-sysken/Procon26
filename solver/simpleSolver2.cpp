#include <iostream>
#include <fstream>
#include "../procon26_modlib.hpp"
#include "../procon26_modio.hpp"

using namespace std;

int main()
{
    Board *obstacleBoard;		// 現在のボードの状態を保持
    Board *putBoard = new Board;	// 今までに置いた石だけを保持
    SubmissionManager sm("answerSimple2");

    // 初期化
    for (int i = 0; i < 128; i++) putBoard->block[i] = 0;

    // 問題読み込み
    string filePath;
    cin >> filePath;
    Problem *prob = readProblem(filePath);
    Answers answer(prob->num);
    obstacleBoard = cloneBoard(&prob->board);

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
                //				cout << x << " " << y << " " << "H" << " " << 0 << endl;
                answer.place(0, x, y, false, 0);
            }
        }
    }

    // 二個目以降の石はぼっち空きマスが少なくなるように置く
    for (int i = 1; i < prob->num; i++)
    {
        // たくさん接した座標、反転、回転を記憶
        int counting = 1000, bestX, bestY, Turn;
        bool canPut = false, flipped = false;
        int touching = -1;

        for (int y = -STONE_SIZE + 1; y < BOARD_SIZE; y++)
        {
            for (int x = -STONE_SIZE + 1; x < BOARD_SIZE; x++)
            {
                // 回転(反転なし)
                for (int j = 0; j < 4; j++)
                {
                    Stone *stonetmp = getTouchingStone(obstacleBoard, rotate(&prob->stones[i], j), x, y, true);
                    int touchNum = countBitOfStone(stonetmp); 
                    delete stonetmp;
                    if (!isPut[i] && canPlace(obstacleBoard, putBoard, rotate(&prob->stones[i], j), x, y))
                    {
                        Board *tmp = cloneBoard(obstacleBoard);
                        tmp = placeStone(obstacleBoard, rotate(&prob->stones[i], j), x, y); 
                        int countNum, cnt;
                        getGroupsCountBoard(tmp, 0, &countNum, &cnt);
                        if (countNum < counting || (countNum == counting && touching < touchNum))
                        {
                            touching = touchNum;
                            counting = countNum;
                            bestX = x;
                            bestY = y;
                            Turn = j;
                            canPut = true;
                            flipped = false;
                        }
                        delete tmp;
                    }
                }

                // 回転(反転あり)
                for (int j = 0; j < 4; j++)
                {
                    Stone *stonetmp = getTouchingStone(obstacleBoard, rotate(flip(&prob->stones[i]), j), x, y, true);
                    int touchNum = countBitOfStone(stonetmp);                    
                    delete stonetmp;
                    if (!isPut[i] && canPlace(obstacleBoard, putBoard, rotate(flip(&prob->stones[i]), j), x, y))
                    {
                        Board *tmp = cloneBoard(obstacleBoard);
                        tmp = placeStone(obstacleBoard, rotate(flip(&prob->stones[i]), j), x, y);
                        int countNum, cnt;
                        getGroupsCountBoard(tmp, 0, &countNum, &cnt); 
                        if (countNum < counting || (countNum == counting && touching < touchNum))
                        {
                            touching = touchNum;
                            counting = countNum;
                            bestX = x;
                            bestY = y;
                            Turn = j;
                            canPut = true;
                            flipped = true;
                        }
                        delete tmp;
                    }
                }
            }
        }

        if (canPut)
        {
            // 石を置く
            if (!flipped)
            {
                obstacleBoard = placeStone(obstacleBoard, rotate(&prob->stones[i], Turn), bestX, bestY);
                putBoard      = placeStone(putBoard, rotate(&prob->stones[i], Turn), bestX, bestY);
            }
            else
            {
                obstacleBoard = placeStone(obstacleBoard, rotate(flip(&prob->stones[i]), Turn), bestX, bestY);
                putBoard      = placeStone(putBoard, rotate(flip(&prob->stones[i]), Turn), bestX, bestY);
            }

            //			cout << bestX << " " << bestY << " " << (flipped?"T":"H") << " " << Turn * 90 << endl;
            answer.place(i, bestX, bestY, flipped, Turn);
            isPut[i] = true;
        }
        else
        {
            //			cout << endl;
        }
    }

    cout << 1024 - countBitOfBoard(obstacleBoard) << " ";
    cout << sm.submit(&answer) << endl;

    // メモリ解放
    delete   obstacleBoard;
    delete   putBoard;
    delete   prob;
    delete[] isPut;

    return 0;
}
