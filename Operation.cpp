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
				cout << "������0<n<=1000000��" << endl;
				return;
			}
			else {
				FianlMaker fm;
				fm.make(n);
				cout << "������" + parameter2 + "����������" << endl;
			}
		}
		//�������ڿա�����������Ϸ
		else if (parameter1 == "-n")
		{
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000)
			{
				cout << "������0<n<=1000000��" << endl;
				return;
			}
			else {
				ifstream in("finale.txt");
				if (!in.is_open()) {
					cout << "finale.txt �޷��򿪣�" << endl;
					return;
				}
				Rand1(10);//����������ɹ���1���Ѷ�
				char ch[81] = { '0' };
				char c;
				int count = -1;
				int flag = 0;
				//SudokuSolver ss;
				ofstream out("game.txt", ios::trunc);
				while (in.get(c)) {	//in >> c ����Կհ׻س���
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
					const char* str = "���ڴ����ʽ��";
					//fputs(str, out);
					out << str << endl;
					cout << str << endl;
				}
				else
					cout << "������" + parameter2 + "��������Ϸ" << endl;
				out.close();
			}
		}
		//����
		//��������Ϸ
		else if (parameter1 == "-s") {
			ifstream in(parameter2);
			if (!in.is_open()) {
				cout << parameter2 + "�޷��򿪣�" << endl;//parameter2 = game.txt
				return;
			}
			char ch[81];
			char c;
			int count = 0;
			//udokuSolver ss;
			FILE* out = fopen("solver.txt", "wt");
			while (in.get(c)) {	//in >> c ����Կհ׻س���
				if (isdigit(c) || c == '$') {
					if (c == '$')
						c = '0';
					ch[count++] = c;
				}
				if (count == 81) {
					count = 0;
					//fputs(ss.solve(ch), out);
					fputs(solution(ch), out);//�޸������������
				}
			}
			in.close();
			if (count != 0) {
				const char* str = "���ڴ����ʽ��";
				fputs(str, out);
				cout << str << endl;
			}
			else
				cout << "�ѳɹ����������Ϸ" << endl;
			fclose(out);
		}
		else if (argc == 5)//�������Ѷȵȼ�Ҫ�� && �޶��ڿշ�Χ��������Ϸ
	{
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		string parameter3 = argv[3];//��������  -m -r
		string parameter4 = argv[4];//��������  �Ѷȵȼ�
		//�������ڿա�����������Ϸ
		if (parameter1 == "-n")
		{
			int n = isNum(parameter2);
			int flag = 0;
			if (n <= 0 || n > 1000000)
			{
				cout << "������0<n<=1000000��" << endl;
				return;
			}
			else {
				ifstream in("finale.txt");
				if (!in.is_open()) {
					cout << "finale.txt �޷��򿪣�" << endl;
					return;
				}
				if (parameter3 == "-m")//���д�˵ȼ�
				{
					int m = isNum(parameter4);//���жϵ��ĸ���������1��2��3
					if (m < 1 || m > 3)
					{
						cout << "������1=<m<=3��" << endl;
						return;
					}

					Rand1(m * 10);//����������ɹ�
					char ch[81] = { '0' };
					char c;
					int count = -1;
					//SudokuSolver ss;
					ofstream out("game.txt", ios::trunc);
					while (in.get(c)) {	//in >> c ����Կհ׻س���
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
						const char* str = "���ڴ����ʽ��";
						//fputs(str, out);
						out << str << endl;
						cout << str << endl;
					}
					else
						cout << "������" << parameter2 << "��������Ϸ" << endl;
					out.close();
				}
			}
		}
	}
	else {
		cout << "��������" << endl;
	}
	return;
}
	

	else {
		cout << "��������" << endl;
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

//����ڿգ����������
void InputHandler::Rand1(int randnum1)
{
	int temp[81];
	srand((unsigned)time(0));
	for (int i = 0; i < 81; ++i) temp[i] = i + 1;//����ֵ��Χ�е��������������
	for (int j = 81 - 1; j >= 1; --j) swap(temp[j], temp[rand() % j]);//������������ű����ֵ������ֵ���н���
	for (int i = 0; i < randnum1; i++)
		a[i] = temp[i];

}
//ָ����Χ���ڿ�
void InputHandler::Rand2(int m1, int m2)
{
	int temp[81];
	srand((unsigned)time(0));
	for (int i = 0; i < m2 - m1 + 1; ++i)
	{
		temp[i] = m1 + i;//����ֵ��Χ�е��������������
		//cout << temp[i] << " ";
	}

	for (int j = m2 - m1; j >= 1; --j) swap(temp[j], temp[rand() % j]);//������������ű����ֵ������ֵ���н���
	randnum2 = temp[0];//��m1��m2֮������һ���������Ϊ�ڿյ�����
	cout << randnum2 << endl;
	Rand1(randnum2);
}
