#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
#include<fstream>
#include "sudoku.h"

using namespace std;

const int number = 1;//学号（1120161736）后两位mod9+1

const int INVALID = 2;

const int FORC = 3;

const int FORS = 4;

const string fileName = "sudoku.txt";

int main(int argc, char** argv) {
	//申明
	bool isPurenumber(char* s);
	int checkArg(int argc, char* argv[]);

	cout << "First code line" << endl;
	//输出传入参数
	cout << "argc = " << argc << endl;
	//cout << "agv[2] = " << argv[2] << endl;
	
	//根据参数执行相应操作
	int flag = checkArg(argc, argv);
	if (flag == INVALID)return 0;
	if (flag == FORC) {
		//从参数获得终局个数
		stringstream ss;
		ss << argv[2];
		int n;
		ss >> n;
		cout << "n = " << n << endl;
		cout << " 开始生成数独终局文件 " << endl;
		//生成数独终局文件suduku.txt
		createSudoku(n, fileName);
	}
	if (flag == FORS) {//求解数独
		cout << " 开始求解数独 " << endl;
		//getSudokuSolution(fileName);
	}
}

//判断输入是否问纯数字
bool isPurenumber(char* s) {
	int n = strlen(s);
	for (int i = 0; i < n; i++)
		if (s[i] > '9' || s[i] < '0')
			return false;
	return true;
}

//参数合法性判断

int checkArg(int argc, char* argv[]) {
	//验证传入参数的合法性
	if (argc != 3) {//数量
		cout << "参数数量过少或过多" << endl;
		return INVALID;
	}
	if (strcmp("-c", argv[1]) != 0 && strcmp("-s", argv[1]) != 0)//-s和-c检查
	{
		cout << "请输入-c或-s" << endl;
		return INVALID;
	}
	if (strcmp("-c", argv[1]) == 0) {//生成终局
		if (!isPurenumber(argv[2])) {//生成终局数必须为数字
			cout << "生成终局数必须为数字" << endl;
			return INVALID;
		}
		return FORC;
	}
	else {//求解数独
		return FORS;
	}
}
