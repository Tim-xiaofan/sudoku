#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
#include<fstream>
#include "sudoku.h"

using namespace std;

const int number = 1;//ѧ�ţ�1120161736������λmod9+1

const int INVALID = 2;

const int FORC = 3;

const int FORS = 4;

const string fileName = "sudoku.txt";

int main(int argc, char** argv) {
	//����
	bool isPurenumber(char* s);
	int checkArg(int argc, char* argv[]);

	cout << "First code line" << endl;
	//����������
	cout << "argc = " << argc << endl;
	//cout << "agv[2] = " << argv[2] << endl;
	
	//���ݲ���ִ����Ӧ����
	int flag = checkArg(argc, argv);
	if (flag == INVALID)return 0;
	if (flag == FORC) {
		//�Ӳ�������վָ���
		stringstream ss;
		ss << argv[2];
		int n;
		ss >> n;
		cout << "n = " << n << endl;
		cout << " ��ʼ���������վ��ļ� " << endl;
		//���������վ��ļ�suduku.txt
		createSudoku(n, fileName);
	}
	if (flag == FORS) {//�������
		cout << " ��ʼ������� " << endl;
		//getSudokuSolution(fileName);
	}
}

//�ж������Ƿ��ʴ�����
bool isPurenumber(char* s) {
	int n = strlen(s);
	for (int i = 0; i < n; i++)
		if (s[i] > '9' || s[i] < '0')
			return false;
	return true;
}

//�����Ϸ����ж�

int checkArg(int argc, char* argv[]) {
	//��֤��������ĺϷ���
	if (argc != 3) {//����
		cout << "�����������ٻ����" << endl;
		return INVALID;
	}
	if (strcmp("-c", argv[1]) != 0 && strcmp("-s", argv[1]) != 0)//-s��-c���
	{
		cout << "������-c��-s" << endl;
		return INVALID;
	}
	if (strcmp("-c", argv[1]) == 0) {//�����վ�
		if (!isPurenumber(argv[2])) {//�����վ�������Ϊ����
			cout << "�����վ�������Ϊ����" << endl;
			return INVALID;
		}
		return FORC;
	}
	else {//�������
		return FORS;
	}
}
