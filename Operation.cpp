#include "Operation.h"
#include "Finale.h"
#include "Unique.h"
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
int a[81];
int randnum2;

void InputHandler::check(int argc, char** argv) {
	if (argc == 3) {
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		if (parameter1 == "-c") {
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000) {
				cout << "不满足0<n<=1000000！" << endl;
				return;
			}
			else {
				FianlMaker fm;
				fm.make(n);
				cout << "已生成" + parameter2 + "个数独终盘" << endl;
			}
		}
		
	

	else {
		cout << "输入有误！" << endl;
	}
	return;
}

int InputHandler::isNum(const string& s) {
	size_t size = s.size();
	if (size > 7)
		return 0;
	for (size_t i = 0; i < size; i++) {
		int ascii = int(s[i]);
		if (ascii >= 48 && ascii <= 57)
			continue;
		else
			return 0;
	}
	return stoi(s);
}

//随机挖空：生成随机数
void InputHandler::Rand1(int randnum1)
{
	int temp[81];
	srand((unsigned)time(0));
	for (int i = 0; i < 81; ++i) temp[i] = i + 1;//将数值范围中的整数存放于数组
	for (int j = 81 - 1; j >= 1; --j) swap(temp[j], temp[rand() % j]);//随机产生索引脚标的数值与数组值进行交换
	for (int i = 0; i < randnum1; i++)
		a[i] = temp[i];

}
//指定范围内挖空
void InputHandler::Rand2(int m1, int m2)
{
	int temp[81];
	srand((unsigned)time(0));
	for (int i = 0; i < m2 - m1 + 1; ++i)
	{
		temp[i] = m1 + i;//将数值范围中的整数存放于数组
		//cout << temp[i] << " ";
	}

	for (int j = m2 - m1; j >= 1; --j) swap(temp[j], temp[rand() % j]);//随机产生索引脚标的数值与数组值进行交换
	randnum2 = temp[0];//在m1和m2之间生成一个随机数作为挖空的数量
	cout << randnum2 << endl;
	Rand1(randnum2);
}