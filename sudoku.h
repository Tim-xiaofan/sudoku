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
	int checkResult;//表明用户参数的合法与否，辨别用户想要做那种操作
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
	int firstR[N];
	int model[N][N];//模板
	string sudokuStore;//保存终局
public:
	SudokuFactory(int m_need = 0 ) {
		need = m_need; 
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
};





void createSudokuFile(int n, string fileName);

#endif // !SUDOKU_H
