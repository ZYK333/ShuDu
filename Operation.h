#include "Finale.h"
#include "Unique.h"
#include <time.h>
#include <sys/timeb.h>

int blank[81]; //�ڿ�λ��
int randnum2;  //-r ��Χ
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


//����ڿգ����������
void Rand1(int randnum1)
{
	int temp[81];
	srand((unsigned)time(0));
	for (int i = 0; i < 81; ++i) temp[i] = i + 1;//����ֵ��Χ�е��������������
	for (int j = 81 - 1; j >= 1; --j) swap(temp[j], temp[rand() % j]);//������������ű����ֵ������ֵ���н���
	for (int i = 0; i < randnum1; i++)
		blank[i] = temp[i];
}

//ָ����Χ���ڿ�
void Rand2(int RandMin, int RandMax)
{
	//���뼶�������
	struct timeb timeSeed;
	ftime(&timeSeed);
	srand(timeSeed.time * 1000 + timeSeed.millitm);  // milli time
	unsigned int range = RandMax - RandMin + 1;
	randnum2 = rand() % range + RandMin;
	Rand1(randnum2);
}

//�ڿ�
bool DigBlank(int n, bool u, bool r, int rand = 10) {
	//n��������Ϸ������u���Ƿ�Ψһ��r���Ƿ��з�Χ��rand���ڿ�����
	ifstream in("finale.txt");
	if (!in.is_open()) {
		cout << "finale.txt �޷��򿪣�" << endl;
		return false;
	}

	char ch[81] = { '0' };
	char c;
	int count = -1;
	int flag = 0;

	ofstream out("game.txt", ios::trunc);
	while (in.get(c)) {	
		if (isdigit(c))//���Կհ׻س���
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
			if (u && !unique(ch)) //���Ҫ����Ψһ�⵫������Ҫ�󣬺���
			{
				cout << "����ʧ�ܣ���ֻһ���⣡" << endl;
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
					cout << "���ɳɹ����ո���Ϊ" << rand << endl;
				else
					cout << "���ɳɹ���" << endl;
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
		const char* str = "���ڴ����ʽ��";
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

		//������������
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

		//����������Ϸ
		else if (parameter1 == "-n")
		{
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000)
			{
				cout << "������0<n<=1000000��" << endl;
				return;
			}
			Rand1(10);//����������ɹ���1���Ѷ�
			if (DigBlank(n, false, false))
				cout << "������" << n << "��������Ϸ" << endl;
			else
				cout << "����ʧ��" << endl;
		}

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
		else {
			cout << "��������" << endl;
		}
	}

	//����Ψһ���������Ϸ
	else if (argc == 4)
	{
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		string parameter3 = argv[3];
		int flag = 0;
		if (parameter1 != "-n" || parameter3 != "-u")
			cout << "���������ʽ����" << endl;
		int n = isNum(parameter2);
		if (n <= 0 || n > 1000000)
		{
			cout << "������0<n<=1000000��" << endl;
			return;
		}
		Rand1(10);//����������ɹ���1���Ѷ�
		if (DigBlank(n, true, false))
			cout << "������" << n << "��������Ϸ" << endl;
		else
			cout << "����ʧ��" << endl;
	}

	//�������Ѷȵȼ�Ҫ�� && �޶��ڿշ�Χ��������Ϸ
	else if (argc == 5)
	{
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		string parameter3 = argv[3];//��������  -m -r
		string parameter4 = argv[4];//��������  �Ѷȵȼ�

		if (parameter1 != "-n")
		{
			cout << "��������" << endl;
			return;
		}
		int n = isNum(parameter2);
		int flag = 0;
		if (n <= 0 || n > 1000000)
		{
			cout << "������0<n<=1000000��" << endl;
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
			Rand1(m * 10);//����������ɹ���m���Ѷ�
			if (DigBlank(n, false, false, m * 10))
				cout << "������" << n << "��������Ϸ���Ѷ�Ϊ" << m << "��" << endl;
			else
				cout << "����ʧ��" << endl;
		}
		else if (parameter3 == "-r")//������Ϸ���ڿյ�������Χ  ShuDu.exe -n 10 -r 20~55
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
				cout << "����ķ�Χ���Ϸ���" << endl;
				return;
			}
			Rand2(m1, m2);//����������ɹ�
			if (DigBlank(n, false, true, randnum2))
				cout << "������" << n << "��������Ϸ" << endl;
			else
				cout << "����ʧ��" << endl;
		}
		else
			cout << "��������" << endl;
	}
}
