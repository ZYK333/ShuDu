#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class InputHandler {
public:
	void check(int argc, char** argv);
	void Rand1(int m);
	void Rand2(int m1,int m2);

private:
	int isNum(const string& s);
	
};
