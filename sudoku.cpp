#include "sudoku.h"
#include <string>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

const int N = 9;

const char No = '1';//学号1120161736

int firstRow[N] = { No,2 ,3, 4 , 5, 6, 7, 8, 9 };//保存第一行

const int randow = 210;//随机程度

const string filename = "sudoku.txt";

ofstream test_file(filename);

//偏移值
int offset[N] = { 0,3,6,1,4,7,2,5,8 };

//用于调试
/*void printArray(int a[], int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "\n";
}*/

/*******************************************************/
//类ArgCheck的实现
int ArgCheck::check() {
	//申明
	bool isPurenumber(char* s);
	//验证传入参数的合法性
	if (argc != 3) {//数量
		cout << "参数数量过少或过多" << endl;
		return checkResult = INVALID;
	}
	if (strcmp("-c", argv[1]) != 0 && strcmp("-s", argv[1]) != 0)//-s和-c检查
	{
		cout << "请输入-c或-s" << endl;
		return checkResult = INVALID;
	}
	if (strcmp("-c", argv[1]) == 0) {//生成终局
		if (!isPurenumber(argv[2])) {//生成终局数必须为数字
			cout << "生成终局数必须为数字" << endl;
			return checkResult = INVALID;
		}
		return checkResult = FORC;
	}
	else {//求解数独
		return checkResult = FORS;
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

/*******************************************************/
/*******************************************************/
//类SudokuFactory的实现
//生成第一个模板
void SudokuFactory::createFirstModel() {
	void printSudoku(int a[N][N]);
	char number[N] = { '1','2', '3', '4', '5', '6', '7', '8', '9' };
	//随机确定最开始的排列
	srand((unsigned int)time(NULL));
	int ran = 0 + rand() % randow;
	//cout << "AtomCreate...." << endl;
	for (int i = 0; i < ran; i++)
		next_permutation(number + 1, number + N);
	//填入学号
	firstR[0] = '1';
	for (int i = 1; i < N; i++)
		firstR[i] = number[i];
	//cout << "第一个排列:\n";
	//printArray(firstR, N);
	//产生模板阵列数组
	//填入第一行
	for (int j = 0; j < N; j++)
		model[0][j] = firstR[j];
	//剩余行
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int k = (j +  offset[i]) % N;//计算偏移坐标
			//cout << " deta= " << (N - i) << endl;
			model[i][j] = firstR[k];
		}
	}
	//cout << "第一个model:\n";
	//printSudoku(model);
}


//更新模板
void SudokuFactory::refreshModel() {
	//cout << "refreshModel()\n";
	void printSudoku(int a[N][N]);
	next_permutation(firstR + 1, firstR + N);//取得下一个排列
	//cout << "新的排列:\n";
	//printArray(firstR, N);
	//产生模板阵列数组
	//填入第一行
	for (int j = 0; j < N; j++)
		model[0][j] = firstR[j];
	//剩余行
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int k = (j + (N - i)) % N;//计算偏移坐标
			//cout << " deta= " << (N - i) << endl;
			model[i][j] = firstR[k];
		}
	}
	//cout << "新的model:\n";
	//printSudoku(model);
}

//在原始阵列基础上进行变换并保存36个排列
void SudokuFactory::newFromModel() {
	//cout << "newFromModel()\n";
	int A[3] = { 4, 5, 6 };//456为一组
	int B[3] = { 7, 8, 9 };//456为一组
	//前三行不变
	char firstThreeRows[N * 6];// 保存123行
	int index = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < N - 1; j++) {
			firstThreeRows [index++]= (model[i][j]);
			firstThreeRows[index++] = ' ';
		}
		firstThreeRows[index++] = (model[i][N - 1]);
		firstThreeRows[index++] = '\n';//换行
	}
	//cout << sudokuString;
	for (int a = 0; a < 6; a++) {
		//确定A组456,的一个排列
		//cout << "!!!!!!!!!!A:\n";
		//printArray(A, 3);
		char midThreeRows[6 * N];//保存456行
		int index = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < N - 1; j++) {
				//每生成一个数字，直接保存。注意空格和换行。
				//cout << "（" << sudokuArray[A[index] - 1][j] << "）";
				midThreeRows[index++] = (model[A[i] - 1][j]);
				midThreeRows[index++] = ' ';
				//cout <<"\n<"<< sudokuString << ">" << endl;
				//cout << sudokuString;
			}
			//cout << "（" << sudokuArray[A[index] - 1][N - 1] << "）" << endl;
			midThreeRows[index++] = (model[A[i] - 1][N - 1]);//行尾没有空格
			//cout << "\n<" << sudokuString << ">" << endl;
			midThreeRows[index++] = '\n';//换行
		}
		//cout << "transA:";
		//cout << "\n<" << sudokuString << ">" << endl;
		//同一个A的排列可以有6种不同的排列
		for (int b = 0; b < 6; b++) {
			//确定B组789，的一个排列
			//cout << "B:\n";
			//printArray(B, 3);
			char lastThreeRows[6 * N];
			int index = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < N - 1; j++) {
					//每生成一个数字，直接保存。注意空格和换行。
					//cout << "（" << sudokuArray[B[index] - 1][j] << "）";
					lastThreeRows[index++] = (model[B[i] - 1][j]);
					lastThreeRows[index++] = ' ';
				}
				//cout << "（" << sudokuArray[B[index] - 1][N - 1] << "）" << endl;
				lastThreeRows[index++] = (model[B[i] - 1][N - 1]);//行尾没有空格
				lastThreeRows[index++] = '\n';//换行
				//cout << sudokuString;
			}
			//剩余需求量变化-1
			need--;
			//直接输出到文件
			store(firstThreeRows,midThreeRows,lastThreeRows);
			//cout << "need = " << need << endl;
			//cout << "transB:";
			//cout << oneSudokuString;
			if (need == 0) return;//为零则，结束生成
			//cout << "\n";//添加数独阵列间空行
			sudokuStore[index_store++] = '\n';
			//B的下一个排列
			next_permutation(B, B + 3);
		}
		//A的下一个排列
		next_permutation(A, A + 3);
	}
}

void SudokuFactory::store(char a[], char b[], char c[]) {
	int k1 = 6 * N;
	for (int i = 0; i < k1; i++)
		sudokuStore[index_store++] = a[i];
	for (int i = 0; i < k1; i++)
		sudokuStore[index_store++] = b[i];
	for (int i = 0; i < k1; i++)
		sudokuStore[index_store++] =c[i];
}

//生成终局文件
char* SudokuFactory::createSudokuFile() {
	while (need > 0) {
		newFromModel();
		refreshModel();
	}
	sudokuStore[index_store++] = '\0';//记得输入结束标识
	return sudokuStore;
}

/*void printSudoku(int a[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << a[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
}*/
