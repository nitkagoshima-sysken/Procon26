
//盤面の評価値は高いほど大きいブロックを置きやすい、
//置ける場所が広いことを示す。

#include<iostream>
#include "procon26_modio.cpp"
#include "procon26_module.cpp"
#include "procon26_modlib.cpp"

using namespace std;
double evalBoard(Board *);
int main () 
{	
	double eval;
	Board *board = getBoardByString(
        "10000000000000000100000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000001100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000100000000000000011110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000100000000000000110000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000010000000111000000000000011100000000000000000000000000000000000001001000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000001000000000000000000001000000000000000000000100000000000000000000000000000000000000000000000000000000000"
        "00001100000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        );
	
	showBoard(board);
	eval = evalBoard(board);
	cout << endl << "評価値：" << eval << endl;
	return 0;
}
double evalBoard(Board *board)
{
	int	   space;
	int    maxline = 0,line = 0;
	int    column[32],maxcolumn = 0;
	int    cnt,count;
	double density[16],aveden[4];
	double variance[4],allvariance;
	double pergroup;
	double evalation;
	
	getGroupsCountBoard(board, 0, &cnt,&count);
	space = 1024 - countBitOfBoard(board);
	
	for(int i = 0; i <  32; i++) column[i]   = 0;
	for(int i = 0; i <  16; i++) density[i]  = 0;
	for(int i = 0; i <   4; i++) variance[i] = 0;
	for(int i = 0; i < 128; i++)
	{
		if(i % 4 == 0) 
		{
			if(line > maxline) maxline = line;
			line = 0;
		}
		for(int j = 0; j < 8; j++) column[(i%4)*8+j] += (board->block[i] >> (7-j)) % 2;
		density[i%4 + (i/32) * 4] += countBit(board->block[i]);
		line                      += countBit(board->block[i]);
	}
	for(int i = 0; i < 32; i++) 
	{
		if(column[i] > maxcolumn) maxcolumn = column[i];
	}
	for(int i = 0; i < 4; i++)
	{
		 variance[i] = ((density[i*4]-density[i*4 + 1])  * (density[i*4]-density[i*4 + 1])) + ((density[i*4 + 1]-density[i*4 + 2]) * (density[i*4 + 1]-density[i*4 + 2])) + ((density[i*4 + 2]-density[i*4 + 3]) * (density[i*4 + 2]-density[i*4 + 3]));
		 aveden[i]   =  (density[i*4] + density[i*4 + 1] + density[i*4 + 2] + density[i * 4 + 3])  / 4;
		 variance[i] = variance[i] / (aveden[i] + 1);
	}
	allvariance = ((variance[0]-variance[1])  * (variance[0]-variance[1])) + ((variance[1]-variance[2]) * (variance[1]-variance[2])) + ((variance[2]-variance[3]) * (variance[2]-variance[3]));
	allvariance = allvariance  / (1025 - count);
	pergroup    = (double)cnt / ((double)count + 1) * 1000;	
	evalation = space - (maxline + maxcolumn) * 4 + allvariance * 20 - pergroup;
	return evalation;
}