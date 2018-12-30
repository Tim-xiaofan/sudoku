#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
#include<fstream>
#include "sudoku.h"
#include "s_sudoku.h"

using namespace std;

const int number = 1;//ѧ�ţ�1120161736������λmod9+1

const string fileName = "sudoku.txt";

int main(int argc, char** argv) {
	//����
	bool isPurenumber(char* s);
	int checkArg(int argc, char* argv[]);

	
	//���ݲ���ִ����Ӧ����
	ArgCheck argC(argc, argv);
	argC.check();
	int flag = argC.getResult();
	if (flag == ArgCheck::INVALID)return 0;
	if (flag == ArgCheck::FORC) {
		//�Ӳ�������վָ���
		stringstream ss;
		ss << argv[2];
		int n;
		ss >> n;
		cout << "n = " << n << endl;
		cout << " ��ʼ���������վ��ļ� " << endl;
		//���������վ��ļ�suduku.txt
		//createSudokuFile(n, fileName);
		SudokuFactory factory(n);
		char* fileString = factory.createSudokuFile();
		//cout << "sizeof(fileString)" << sizeof(fileString) << endl;
		//cout << fileString;
		ofstream file(fileName);
		if (!file.is_open()) cout << "���ļ�ʧ��" << endl;
		int k = 18 * 9 * n + n - 1;
		//cout << "k = " << k << endl;
		file << fileString;
		cout << " ��� " << endl;
	}
	/*ifstream file_in("main.cpp");
	string line;
	while (!file_in.eof()) {
		getline(file_in, line);
		cout << line << "test " << endl;
	}*/
	if (flag == ArgCheck::FORS) {//�������
		cout << " ��ʼ������� " << endl;
		//getSudokuSolution(fileName);
		SudokuSolve ssolve;
		ssolve.solve(argv[2]);
		cout << " ��� " << endl;
	}
}


