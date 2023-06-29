#include "Finale.h"
#include "Unique.h"
#include <time.h>
#include <sys/timeb.h>

int blank[81]; //挖空位置
int randnum2;  //-r 范围
int m1, m2;

int isNum(const string& s) {
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
void Rand1(int randnum1)
{
	int temp[81];
	srand((unsigned)time(0));
	for (int i = 0; i < 81; ++i) temp[i] = i + 1;//将数值范围中的整数存放于数组
	for (int j = 81 - 1; j >= 1; --j) swap(temp[j], temp[rand() % j]);//随机产生索引脚标的数值与数组值进行交换
	for (int i = 0; i < randnum1; i++)
		blank[i] = temp[i];
}

//指定范围内挖空
void Rand2(int RandMin, int RandMax)
{
	//毫秒级随机种子
	struct timeb timeSeed;
	ftime(&timeSeed);
	srand(timeSeed.time * 1000 + timeSeed.millitm);  // milli time
	unsigned int range = RandMax - RandMin + 1;
	randnum2 = rand() % range + RandMin;
	Rand1(randnum2);
}

//挖空
bool DigBlank(int n, bool u, bool r, int rand = 10) {
	//n：数独游戏数量、u：是否唯一、r：是否有范围、rand：挖空数量
	ifstream in("finale.txt");
	if (!in.is_open()) {
		cout << "finale.txt 无法打开！" << endl;
		return false;
	}

	char ch[81] = { '0' };
	char c;
	int count = -1;
	int flag = 0;

	ofstream out("game.txt", ios::trunc);
	while (in.get(c)) {	
		if (isdigit(c))//忽略空白回车符
			count++;
		else
			continue;
		for (int i = 0; i < rand; i++)
		{
			if (count == blank[i])
			{
				ch[count] = '$';
				break;
			}
			ch[count] = c;
		}
		if (count == 80)
		{
			cout << "--------Process: " << flag << "/" << n << "--------" << endl;
			if (u && !unique(ch)) //如果要求有唯一解但不符合要求，忽略
			{
				cout << "生成失败：不只一个解！" << endl;
			}
			else
			{
				flag++;
				for (int i = 0; i < 81; i++)
				{
					if (ch[i] == '0')
						ch[i] = '$';
					out << ch[i] << " ";
					if ((i + 1) % 9 == 0)
						out << endl;
				}
				out << endl;
				if (r)
					cout << "生成成功：空格数为" << rand << endl;
				else
					cout << "生成成功！" << endl;
			}
			count = -1;
			if (n == flag)
				break;
			if (r)
			{
				Rand2(m1, m2);
				rand = randnum2;
			}
		}
	}
	in.close();
	if (count != -1) {
		const char* str = "存在错误格式！";
		out << str << endl;
		out.close();
		return false;
	}
	else {
		out.close();
		return true;
	}
}

void check(int argc, char** argv) {
	if (argc == 3) {
		string parameter1 = argv[1];
		string parameter2 = argv[2];

		//生成数独终盘
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

		//生成数独游戏
		else if (parameter1 == "-n")
		{
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000)
			{
				cout << "不满足0<n<=1000000！" << endl;
				return;
			}
			Rand1(10);//生成随机数成功，1级难度
			if (DigBlank(n, false, false))
				cout << "已生成" << n << "个数独游戏" << endl;
			else
				cout << "生成失败" << endl;
		}

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
		else {
			cout << "输入有误！" << endl;
		}
	}

	//生成唯一解的数独游戏
	else if (argc == 4)
	{
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		string parameter3 = argv[3];
		int flag = 0;
		if (parameter1 != "-n" || parameter3 != "-u")
			cout << "输入参数格式错误！" << endl;
		int n = isNum(parameter2);
		if (n <= 0 || n > 1000000)
		{
			cout << "不满足0<n<=1000000！" << endl;
			return;
		}
		Rand1(10);//生成随机数成功，1级难度
		if (DigBlank(n, true, false))
			cout << "已生成" << n << "个数独游戏" << endl;
		else
			cout << "生成失败" << endl;
	}

	//生成有难度等级要求 && 限定挖空范围的数独游戏
	else if (argc == 5)
	{
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		string parameter3 = argv[3];//新增参数  -m -r
		string parameter4 = argv[4];//新增参数  难度等级

		if (parameter1 != "-n")
		{
			cout << "输入有误！" << endl;
			return;
		}
		int n = isNum(parameter2);
		int flag = 0;
		if (n <= 0 || n > 1000000)
		{
			cout << "不满足0<n<=1000000！" << endl;
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
			Rand1(m * 10);//生成随机数成功，m级难度
			if (DigBlank(n, false, false, m * 10))
				cout << "已生成" << n << "个数独游戏，难度为" << m << "级" << endl;
			else
				cout << "生成失败" << endl;
		}
		else if (parameter3 == "-r")//生成游戏中挖空的数量范围  ShuDu.exe -n 10 -r 20~55
		{
			int log = 0;
			string s1, s2;
			for (int i = 0; i < parameter4.length(); i++)
			{
				if (parameter4[i] == '~')
					log = i;
			}
			for (int i = 0; i < log; i++)
				s1 += parameter4[i];
			for (int i = log + 1; i < parameter4.length(); i++)
				s2 += parameter4[i];
			m1 = isNum(s1);
			m2 = isNum(s2);
			if (m1 < 20 || m2>55)
			{
				cout << "输入的范围不合法！" << endl;
				return;
			}
			Rand2(m1, m2);//生成随机数成功
			if (DigBlank(n, false, true, randnum2))
				cout << "已生成" << n << "个数独游戏" << endl;
			else
				cout << "生成失败" << endl;
		}
		else
			cout << "输入有误！" << endl;
	}
}
