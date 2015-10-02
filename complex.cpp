#include<iostream>
#include<cmath>
#include "procon26_modio.cpp"
#include "procon26_modlib.cpp"

#define PER_COMP_1 1
#define PER_COMP_2 1
#define PER_COMP_3 2
#define PER_COMP_4 0.2

using namespace std;

struct Rect
{
	int startx,starty,endx,endy;
	int space,round,touchrnd;
};

Rect rect(Stone *);
double complex(Stone *);

int main()
{
	Stone  stone;
	int    i;
	double comp;
	
	for(i = 0; i < STONE_SIZE; i++) stone.zuku[i] = 0;
    stone.zuku[3] = 4;
	stone.zuku[4] = 4;
	stone.zuku[5] = 4;
	stone.zuku[6] = 12;
	
	comp = complex(&stone);
	cout  << "comp   = "<< comp << endl;
	return 0;
}
Rect rect(Stone *stone)
{
	bool flag = 0, flag_1 = 0, flag_2 = 0;
	unsigned char  sample = 0; 
	Rect result;
	for(int i = 0; flag == 0; i++)
	{
		if(stone->zuku[i] != 0)
		{
			 flag          = 1;
			 result.starty = i;
			 while(stone->zuku[i] != 0) i++;
			 result.endy   = i - 1;
			 if(result.endy >= STONE_SIZE) result.endy = STONE_SIZE - 1;
		}
		
	}
	
	for(int i = result.starty; i <= result.endy; i++)
	{
		sample = sample | stone->zuku[i];
	}
	for(int i = 0; i <= STONE_SIZE; i++)
	{
		if((sample >> i) == 0 && flag_1 == 0) 
		{
			result.startx = STONE_SIZE-i;
			flag_1 = 1;
		}
		
		if((sample << i) % 0x100 == 0 && flag_2 == 0)
		{
			 result.endx  = i-1;
			 if(result.endx >= STONE_SIZE) result.endx = STONE_SIZE - 1;
			 flag_2 = 1;
		}
	}
		
	return result;
}	

double complex(Stone *stone)
{

	Rect   rectstate = rect(stone);
	bool   flag_top  = 0, flag_bottom = 0, flag_right = 0, flag_left   = 0;
	int    lefttop   = 0, righttop    = 0, leftbottom = 0, rightbottom = 0;
	double comp_1, comp_2, comp_3, comp_4, comp;
	
	rectstate.space    = 0;
	rectstate.round    = 0;
	rectstate.touchrnd = 0;
	//-----------------------------------//
	//               comp_1              //
	//         外周 / 長方形の周長       //
	//-----------------------------------//
	for(int i = rectstate.starty; i <= rectstate.endy; i++)
	{
		for(int j = rectstate.startx; j <= rectstate.endx; j++)
		{
			if(((stone->zuku[i]) & (1 << (STONE_SIZE-1-j))) == (1 << (STONE_SIZE-1-j))) 
			{
				rectstate.round += 4;
				if(j != rectstate.startx)
				{
					if(((stone->zuku[i]) & (1 << (STONE_SIZE-j))) == (1 << (STONE_SIZE-j))) rectstate.round -= 2;
				}
			}
		}
		
		if(i != rectstate.starty) rectstate.round -= countBit(stone->zuku[i] & stone->zuku[i-1]) * 2;
	}
	comp_1 = (double)(rectstate.round) / ((double)(rectstate.endx-rectstate.startx + rectstate.endy-rectstate.starty + 2) * 2.00 ) ;
	//-----------------------------------//
	//               comp_2              //
	//              空白の数             //
	//-----------------------------------//
	for(int i = rectstate.startx; i <= rectstate.endx; i++)
	{
		if(flag_top == 0) 
		{
			if(((stone->zuku[rectstate.starty]) & (1 << (STONE_SIZE-1-i))) == 0 ) 
			{
				flag_top = 1;
				if(i == rectstate.startx) lefttop++; 
				if(i == rectstate.endx)   righttop++; 
			}
		}else
		{
			if(((stone->zuku[rectstate.starty]) & (1 << (STONE_SIZE-1-i))) != 0 )
			{
				rectstate.space++;
				flag_top = 0;
			}else
			{
				if(i == rectstate.startx) lefttop++; 
				if(i == rectstate.endx)   righttop++;
			}
		}

		if(flag_bottom == 0) 
		{
			if(((stone->zuku[rectstate.endy]) & (1 << (STONE_SIZE-1-i))) == 0 ) 
			{
				flag_bottom = 1;
				if(i == rectstate.startx) leftbottom++;
				if(i == rectstate.endx)   rightbottom++;
			}
		}else
		{
			if(((stone->zuku[rectstate.endy]) & (1 << (STONE_SIZE-1-i))) != 0 )
			{
				rectstate.space++;
				flag_bottom = 0;
			}else
			{
				if(i == rectstate.startx) leftbottom++;
				if(i == rectstate.endx)   rightbottom++;
			}
		}
	}
	for(int i = rectstate.starty; i <= rectstate.endy; i++)
	{
		if(flag_left == 0) 
		{
			if(((stone->zuku[i]) & (1 << (STONE_SIZE-1 - rectstate.startx))) == 0 ) 
			{
				flag_left = 1; 
				if(lefttop == 1 + i - rectstate.starty)
				{
					lefttop++;
					flag_left = 0;
				}
			}
		}else
		{
			if(((stone->zuku[i]) & (1 << (STONE_SIZE-1 - rectstate.startx))) != 0 )
			{
				rectstate.space++; 
				flag_left = 0;
			}
		}
		if(flag_right == 0) 
		{
			if(((stone->zuku[i]) & (1 << (STONE_SIZE-1 - rectstate.endx))) == 0 ) 
			{
				flag_right = 1; 
				if(righttop == 1 + i - rectstate.starty)
				{
					righttop++;
					flag_right = 0;
				}
			}
		}else
		{
			if(((stone->zuku[i]) & (1 << (STONE_SIZE-1 - rectstate.endx))) != 0 )
			{
				rectstate.space++;
				flag_right = 0;
			}
		}
	}
	if(flag_top   == 1)  rectstate.space++;
	if(flag_bottom== 1)  rectstate.space++;
	if(flag_left  == 1 && leftbottom  != 1)  rectstate.space++;
	if(flag_right == 1 && rightbottom != 1)  rectstate.space++;
	
	comp_2 = sqrt((double)(rectstate.space));
	//-----------------------------------//
	//               comp_3              //
	//  長方形の周に接する辺の長さの割合 //
	//-----------------------------------//
	for(int i = rectstate.startx; i <= rectstate.endx; i++)
	{
		if(((stone->zuku[rectstate.starty]) & (1<<(STONE_SIZE-1-i))) == (1<<(STONE_SIZE-1-i))) rectstate.touchrnd++;
		if(((stone->zuku[rectstate.endy  ]) & (1<<(STONE_SIZE-1-i))) == (1<<(STONE_SIZE-1-i))) rectstate.touchrnd++;
	}
	for(int i = rectstate.starty; i <= rectstate.endy; i++)
	{
		if(((stone->zuku[i]) & (1<<(STONE_SIZE-1-rectstate.startx))) == (1<<(STONE_SIZE-1-rectstate.startx))) rectstate.touchrnd++;
		if(((stone->zuku[i]) & (1<<(STONE_SIZE-1-rectstate.endx  ))) == (1<<(STONE_SIZE-1-rectstate.endx  ))) rectstate.touchrnd++;
	}
	comp_3 = ( ((double)(rectstate.endx-rectstate.startx + rectstate.endy-rectstate.starty + 2) * 2.00 ) / (double)(rectstate.touchrnd));
	//-----------------------------------//
	//               comp_4              //
	//            長方形の面積           //
	//-----------------------------------//
	comp_4 = (rectstate.endx - rectstate.startx + 1) * (rectstate.endy - rectstate.starty + 1) ;


	comp = comp_1 * PER_COMP_1 + comp_2 * PER_COMP_2 + comp_3 * PER_COMP_3 + comp_4 * PER_COMP_4;
	return comp;
}

