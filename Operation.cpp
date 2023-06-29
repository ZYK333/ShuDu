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
		//新增：挖空→生成数独游戏
		else if (parameter1 == "-n")
		{
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000)
			{
				cout << "不满足0<n<=1000000！" << endl;
				return;
			}
			else {
				ifstream in("finale.txt");
				if (!in.is_open()) {
					cout << "finale.txt 无法打开！" << endl;
					return;
				}
				Rand1(10);//生成随机数成功，1级难度
				char ch[81] = { '0' };
				char c;
				int count = -1;
				int flag = 0;
				//SudokuSolver ss;
				ofstream out("game.txt", ios::trunc);
				while (in.get(c)) {	//in >> c 会忽略空白回车符
					if (isdigit(c))
						count++;
					else
						continue;
					for (int i = 0; i < 10; i++)
					{
						if (count == a[i])
						{
							ch[count] = '$';
							break;
						}
						ch[count] = c;
					}
					//cout << count << ":" << ch[count] << endl;
					out << ch[count] << " ";
					if ((count + 1) % 9 == 0)
					{
						out << endl;
					}
					if (count == 80)
					{
						//cout << "--------------------------------------" << endl;
						count = -1;
						out << endl;
						flag++;
						//fputs(ch, out);
					}
					if (flag == n)
						break;
				}
				in.close();
				if (count != -1) {
					const char* str = "存在错误格式！";
					//fputs(str, out);
					out << str << endl;
					cout << str << endl;
				}
				else
					cout << "已生成" + parameter2 + "个数独游戏" << endl;
				out.close();
			}
		}
		//结束
		//解数独游戏
		else if (parameter1 == "-s") {
			ifstream in(parameter2);
			if (!in.is_open()) {
				cout << parameter2 + "无法打开！" << endl;//parameter2 = game.txt
				return;
			}
			char ch[81];
			char c;
			int count = 0;
			//udokuSolver ss;
			FILE* out = fopen("solver.txt", "wt");
			while (in.get(c)) {	//in >> c 会忽略空白回车符
				if (isdigit(c) || c == '$') {
					if (c == '$')
						c = '0';
					ch[count++] = c;
				}
				if (count == 81) {
					count = 0;
					//fputs(ss.solve(ch), out);
					fputs(solution(ch), out);//修改求解数独函数
				}
			}
			in.close();
			if (count != 0) {
				const char* str = "存在错误格式！";
				fputs(str, out);
				cout << str << endl;
			}
			else
				cout << "已成功解出数独游戏" << endl;
			fclose(out);
		}
		else if (argc == 5)//生成有难度等级要求 && 限定挖空范围的数独游戏
	{
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		string parameter3 = argv[3];//新增参数  -m -r
		string parameter4 = argv[4];//新增参数  难度等级
		//新增：挖空→生成数独游戏
		if (parameter1 == "-n")
		{
			int n = isNum(parameter2);
			int flag = 0;
			if (n <= 0 || n > 1000000)
			{
				cout << "不满足0<n<=1000000！" << endl;
				return;
			}
			else {
				ifstream in("finale.txt");
				if (!in.is_open()) {
					cout << "finale.txt 无法打开！" << endl;
					return;
				}
				if (parameter3 == "-m")//如果写了等级
				{
					int m = isNum(parameter4);//再判断第四个参数，即1、2、3
					if (m < 1 || m > 3)
					{
						cout << "不满足1=<m<=3！" << endl;
						return;
					}

					Rand1(m * 10);//生成随机数成功
					char ch[81] = { '0' };
					char c;
					int count = -1;
					//SudokuSolver ss;
					ofstream out("game.txt", ios::trunc);
					while (in.get(c)) {	//in >> c 会忽略空白回车符
						if (isdigit(c))
							count++;
						else
							continue;
						for (int i = 0; i < m * 10; i++)
						{
							if (count == a[i])
							{
								ch[count] = '$';
								break;
							}
							ch[count] = c;
						}
						//cout << count << ":" << ch[count] << endl;
						out << ch[count] << " ";
						if ((count + 1) % 9 == 0)
						{
							out << endl;
						}
						if (count == 80)
						{
							//cout << "--------------------------------------" << endl;
							count = -1;
							out << endl;
							flag++;
						}
						if (flag == n)
							break;
					}

					in.close();
					if (count != -1) {
						const char* str = "存在错误格式！";
						//fputs(str, out);
						out << str << endl;
						cout << str << endl;
					}
					else
						cout << "已生成" << parameter2 << "个数独游戏" << endl;
					out.close();
				}
			}
		}
	}
	else {
		cout << "输入有误！" << endl;
	}
	return;
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
