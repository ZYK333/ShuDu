#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include<iostream>
#include<fstream>
using namespace std;
int sudo[9][9], total, flag;
static char result[163];

int bfs(int x, int y, int num) {
	int m, n, time = 0;
	int dir[9][2] = { {1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,1},{-1,0},{-1,-1},{0,0} };
	for (int i = 0; i < 9; ++i) {
		m = x + dir[i][0], n = y + dir[i][1];
		if (num == sudo[n][m]) {
			++time;
		}
		if (time > 1) {
			return 0;
		}
	}
	return 1;
}

int judge(int x, int y, int n) {
	int t = 0;
	for (int i = 0; i < 9; ++i) {
		if (sudo[y][i] == n) {
			++t;
			if (t > 1) {
				return 1;
			}
		}
	}
	t = 0;
	for (int i1 = 0; i1 < 9; ++i1) {
		if (sudo[i1][x] == n) {
			++t;
			if (t > 1) {
				return 1;
			}
		}
	}
	if (bfs(1 + (x / 3) * 3, 1 + (y / 3) * 3, n) == 0) {
		return 1;
	}
	return 0;
}


void sel(int x, int y) {
	if (total > 1)
		return;
	if (y < 9) {
		if (x < 9) {
			if (sudo[y][x] == 0) {
				for (int i = 1; i <= 9; ++i) {
					sudo[y][x] = i;
					if (judge(x, y, i) == 0) {
						sel(x + 1, y);
					}
					sudo[y][x] = 0;
				}
			}
			else {
				sel(x + 1, y);
			}
		}
		else {
			sel(0, y + 1);
		}
	}
	else {
		++total;
		if (total > 1)
			return;
		int index = 0;
		if (flag == 1)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					result[index++] = sudo[i][j] + '0';
					result[index++] = ' ';
				}
				result[index++] = '\n';
			}
			result[index] = '\n';
		}
	}
}

bool unique(char ch[])
{
	flag = 0;
	total = 0;
	int index = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (ch[index] == '$')
				ch[index] = '0';
			sudo[i][j] = ch[index++] - '0';
		}
	}
	sel(0, 0);
	if (total == 1)
		return true;
	else
		return false;
}

char* solution(char ch[])
{
	flag = 1;
	total = 0;
	int index = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (ch[index] == '$')
				ch[index] = '0';
			sudo[i][j] = ch[index++] - '0';
		}
	}
	sel(0, 0);
	return result;
}
