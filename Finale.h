#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class FianlMaker {
public:
	void make(int n);

private:
	int num, count;
	int table[9][9];
	void record();
	void rowExchange(const int& r1, const int& r2);
	void colExchange(const int& c1, const int& c2);
	void combina(const int& c1, const int& c2, const int& c3, const int& r1, const int& r2, const int& r3);
};
