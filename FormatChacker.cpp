#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctype.h>
using namespace std;

int  checkStonenum(char *quest);
int  countline(char *answer);
void checkFormat(char *quest, char *answer);

int main(int argc, char *argv[])
{
	checkFormat(argv[1], argv[2]);
	return 0;
}

int checkStonenum(char *quest)
{
	int stone_num;
	ifstream que(quest);
	char temp[10];
	
	que.get(temp, 10);
	stone_num = atoi(temp);
	
	return stone_num;
}

int countline(char *answer)
{
	int i = 0;
	ifstream ans(answer);
	char line[20];
	while(1)
	{
		ans.getline(line, 20);
		i++;
		if(ans.eof())
		{
			break;
		}
	}
	
	return (i-1);
}
void checkFormat(char *quest, char *answer)
{
	int i = 0, n;
	bool flag = 0;
	char str[20], temp[10];
	int stone_num = checkStonenum(quest);
	int line_num = countline(answer);
	
	if(stone_num != line_num)
	{
		cout << "石の数と回答の数が合いません." << endl;
		return;
	}
	ifstream ans(answer);
	
	while(1)
	{
		i++;
		ans.getline(str, 20);
		
		if(ans.eof())
		{
			break;
		}
		
		n = 0;
		if(str[n] == '\0')
		{
			continue;
		}
		else if(str[n] == '-')
		{
			n++;
			if(isdigit(str[n]))
			{
				n++;
				if(str[n] == ' ')
				{
					temp[0] = str[n-1];
					temp[1] = '\0';
					if(atoi(temp) > 7)
					{
						cout << i << "番目:" << str << endl;
						flag = 1;
						continue;
					}
					n++;
				}
				else
				{
					cout << i << "番目:" << str << endl;
					flag = 1;
					continue;
				}
			}
			else
			{
				cout << i << "番目:" << str << endl;
				flag = 1;
				continue;
			}
		}
		else if(isdigit(str[n]))
		{
			n++;
			if(isdigit(str[n]))
			{
				n++;
				if(str[n] == ' ')
				{
					temp[0] = str[n-2];
					temp[1] = str[n-1];
					temp[2] = '\0';
					if(atoi(temp) > 31)
					{
						cout << i << "番目:" << str << endl;
						flag = 1;
						continue;
					}
					n++;
				}
				else
				{
					cout << i << "番目:" << str << endl;
					flag = 1;
					continue;
				}
			}
			else if(str[n] == ' ')
			{
				n++;
			}
			else
			{
				cout << i << "番目:" << str << endl;
				flag = 1;
				continue;
			}
		}
		else
		{
			cout << i << "番目:" << str << endl;
			flag = 1;
			continue;
		}
		//１番目の座標の判定終了
		if(str[n] == '-')
		{
			n++;
			if(isdigit(str[n]))
			{
				n++;
				if(str[n] == ' ')
				{
					temp[0] = str[n-1];
					temp[1] = '\0';
					if(atoi(temp) > 7)
					{
						cout << i << "番目:" << str << endl;
						flag = 1;
						continue;
					}
					n++;
				}
				else
				{
					cout << i << "番目:" << str << endl;
					flag = 1;
					continue;
				}
			}
			else
			{
				cout << i << "番目:" << str << endl;
				flag = 1;
				continue;
			}
		}
		else if(isdigit(str[n]))
		{
			n++;
			if(isdigit(str[n]))
			{
				n++;
				if(str[n] == ' ')
				{
					temp[0] = str[n-2];
					temp[1] = str[n-1];
					temp[2] = '\0';
					if(atoi(temp) > 31)
					{
						cout << i << "番目:" << str << endl;
						flag = 1;
						continue;
					}
					n++;
				}
				else
				{
					cout << i << "番目:" << str << endl;
					flag = 1;
					continue;
				}
			}
			else if(str[n] == ' ')
			{
				n++;
			}
			else
			{
				cout << i << "番目:" << str << endl;
				flag = 1;
				continue;
			}
		}
		else
		{
			cout << i << "番目:" << str << endl;
			flag = 1;
			continue;
		}
		//２番目の座標の判定終了
		
		if(str[n] == 'T' || str[n] == 'H')
		{
			n++;
			if(str[n] == ' ')
			{
				n++;
			}
			else
			{
				cout << i << "番目:" << str << endl;
				flag = 1;
				continue;
			}
		}
		else
		{
			cout << i << "番目:" << str << endl;
			flag = 1;
			continue;
		}
		
		//'H' or 'T'の判定終了
		
		if(str[n] == '0')
		{
			n++;
			if(str[n] == '\0')
			{
				continue;
			}
			else
			{
				cout << i << "番目:" << str << endl;
				flag = 1;
				continue;
			}
		}
		else if(str[n] == '9')
		{
			n++;
			if(str[n] == '0')
			{
				n++;
				if(str[n] == '\0')
				{
					continue;
				}
				else
				{
					cout << i << "番目:" << str << endl;
					flag = 1;
					continue;
				}
			}
			else
			{
				cout << i << "番目:" << str << endl;
				flag = 1;
				continue;
			}
		}
		else if(str[n] == '1')
		{
			n++;
			if(str[n] == '8')
			{
				n++;
				if(str[n] == '0')
				{
					n++;
					if(str[n] == '\0')
					{
						continue;
					}
					else
					{
						cout << i << "番目:" << str << endl;
						flag = 1;
						continue;
					}
				}
				else
				{
					cout << i << "番目:" << str << endl;
					flag = 1;
					continue;
				}
			}
			else
			{
				cout << i << "番目:" << str << endl;
				flag = 1;
				continue;
			}
		}
		else if(str[n] == '2')
		{
			n++;
			if(str[n] == '7')
			{
				n++;
				if(str[n] == '0')
				{
					n++;
					if(str[n] == '\0')
					{
						continue;
					}
					else
					{
						cout << i << "番目:" << str << endl;
						flag = 1;
						continue;
					}
				}
				else
				{
					cout << i << "番目:" << str << endl;
					flag = 1;
					continue;
				}
			}
			else
			{
				cout << i << "番目:" << str << endl;
				flag = 1;
				continue;
			}
		}
		else
		{
			cout << i << "番目:" << str << endl;
			flag = 1;
			continue;
		}
		//角度の判定終了
	}
	
	if(flag != 1)
	{
		cout << "true" << endl;
	}
}