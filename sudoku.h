//定义了void createSudoku(int n, string fileName);方法
#pragma once
#ifndef SUDOKU_H
#define SUDOKU_H

#include<cstring>
#include<string>
#include<cstdlib>

using namespace std;

class ArgCheck{
	int argc;
	char** argv;
	int checkResult;//表明用户参数的合法与否，辨别用户想要做哪种操作
public:
	//一些标志变量
	static const int INVALID = 0;//参数不合法
	static const int FORC = 1;//生成数独终局
	static const int FORS = 2;//求解数独
public:
	ArgCheck(int m_argc = 0, char** m_argv = NULL):checkResult(INVALID){
		argc = m_argc;
		argv = m_argv;
	}
	//提供checkResualt
	int getResult() {
		return checkResult;
	}
	//对参数的合法性以及参数进行判断，结果存入变量checkResualt并返回
	int check();
};


class SudokuFactory {
	static const int N = 9;
	int need;//剩余需求量
	int index_store;
	char* firstR;
	char model[N][N];//模板
	char* sudokuStore;//保存终局
public:
	SudokuFactory(int m_need = 0 ) {
		need = m_need; 
		index_store = 0;//j记录当前字符数量
		sudokuStore = (char*)malloc(sizeof(char) * (18*N*need + need));
		firstR = (char*)malloc(sizeof(int)*N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				model[i][j] = '0';
		createFirstModel();//自动生成第一个模板
	}
	//  检查剩余需求量
	bool isEnough() {
		if (need > 0)return false;
		return true;
	}
	//生成第一个模板
	void createFirstModel();
	//更新模板
	void refreshModel();
	//在原始阵列基础上进行变换并输出36个排列
	void newFromModel();
	//生成终局文件
	char* createSudokuFile();
	string getsudokuStore() { return sudokuStore; }
	void store(char a[], char b[], char c[]);
	~SudokuFactory(){
		free(sudokuStore);
	}
};

#endif // !SUDOKU_H
