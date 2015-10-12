#include "Procon26_modio.hpp"
#include <iostream>
#include <fstream>

using namespace std;

/* Implementation */
Stone *getStoneByString(string stone)
{
    Stone *returnStone = new Stone;
    for (int y = 0; y < STONE_SIZE; y++)
    {
        returnStone->zuku[y] = 0;
        for (int x = 0; x < STONE_SIZE; x++)
        {
            char c = stone[x + y * STONE_SIZE];
            if (c == '1')
            {
                returnStone->zuku[y] += (0x80 >> x);
            }
        }
    }
    return returnStone;
}

Board *getBoardByString(string board)
{
    Board *returnBoard = new Board;
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int i = 0; i < 4; i++)
        {
            returnBoard->block[i + y * 4] = 0;
            for (int x = 0; x < 8; x++)
            {
                char c = board[x + 8 * i  + y * BOARD_SIZE];
                if (c == '1')
                {
                    returnBoard->block[i + y * 4] += (0x80 >> x);
                }
            }
        }
    }
    return returnBoard;
}

void showStone(const Stone *stone)
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

void showBoard(const Board *board)
{
    for (int y = 0; y < BOARD_SIZE ; y++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int x = 0; x < 8; x++)
            {
                cout << (((board -> block[i + y * 4] << x) & 0x80) ? block_1 : block_0);
            }
        }
        cout << endl;
    }
    cout << endl;
}

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

Problem *readProblem(string filePath)
{
    Problem *ret = new Problem;
    ifstream ifs(filePath.c_str());

    string data = "";
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        string str;
        ifs >> str;
        data += str;
    }
    ret->board = *getBoardByString(data);

    ifs >> ret->num;
    ret->stones = new Stone[ret->num];

    for (int i = 0; i < ret->num; i++)
    {
        data = "";
        for (int j = 0; j < STONE_SIZE; j++)
        {
            string str;
            ifs >> str;
            data += str;
        }
        ret->stones[i] = *getStoneByString(data);
    }

    return ret;
}
