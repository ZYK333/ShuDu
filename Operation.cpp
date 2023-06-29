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