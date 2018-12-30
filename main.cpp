#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
#include<fstream>
#include "sudoku.h"
#include "s_sudoku.h"

using namespace std;

const int number = 1;//学号（1120161736）后两位mod9+1

const string fileName = "sudoku.txt";

int main(int argc, char** argv) {
	//申明
	bool isPurenumber(char* s);
	int checkArg(int argc, char* argv[]);

	
	//根据参数执行相应操作
	ArgCheck argC(argc, argv);
	argC.check();
	int flag = argC.getResult();
	if (flag == ArgCheck::INVALID)return 0;
	if (flag == ArgCheck::FORC) {
		//从参数获得终局个数
		stringstream ss;
		ss << argv[2];
		int n;
		ss >> n;
		cout << "n = " << n << endl;
		cout << " 开始生成数独终局文件 " << endl;
		//生成数独终局文件suduku.txt
		//createSudokuFile(n, fileName);
		SudokuFactory factory(n);
		char* fileString = factory.createSudokuFile();
		//cout << "sizeof(fileString)" << sizeof(fileString) << endl;
		//cout << fileString;
		ofstream file(fileName);
		if (!file.is_open()) cout << "打开文件失败" << endl;
		int k = 18 * 9 * n + n - 1;
		//cout << "k = " << k << endl;
		file << fileString;
		cout << " 完成 " << endl;
	}
	/*ifstream file_in("main.cpp");
	string line;
	while (!file_in.eof()) {
		getline(file_in, line);
		cout << line << "test " << endl;
	}*/
	if (flag == ArgCheck::FORS) {//求解数独
		cout << " 开始求解数独 " << endl;
		//getSudokuSolution(fileName);
		SudokuSolve ssolve;
		ssolve.solve(argv[2]);
		cout << " 完成 " << endl;
	}
}


