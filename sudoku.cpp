#include "sudoku.h"
#include <string>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

const int N = 9;

const int No = 1;//学号1120161736

int firstRow[N];//保存第一行

const int randow = 210;//随机程度

int sudokuArray[N][N];//保存数独阵列

//用于调试
void printArray(int a[], int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "\n";
}

void createSudoku(int n, string filename) {
	//申明
	void getFirstRow(int no);
	void createSudokuArray(string filename);
	void nextSudokuArray();
	void printSudokuArray(string filename);

	//确定第一行
	//生成原始阵列
	//进行变换得到剩余的35中
	//过程中检查数量是否满足要求，不满足反复上面的不走
	while (n > 0) {
		//产生第一行,在学号限制下
		getFirstRow(No);
		//生成原始阵列
		createSudokuArray(filename);
		printSudokuArray(filename);
		n--;
		//
		for (int i = 0; i < 35; i++)
			nextSudokuArray();
	}
}

void getFirstRow(int No) {
	int number[N - 1] = { 2, 3, 4 , 5, 6, 7, 8, 9 };
	//随机确定最开始的排列
	srand((unsigned int)time(NULL));
	int ran = 0 + rand() % randow;
	cout << "Trans...." << endl;
	for (int i = 0; i < ran; i++)
		next_permutation(number, number + N - 1);
	
	firstRow[0] = No;//填入学号
	for (int i = 1; i < N; i++)
		firstRow[i] = number[i - 1];
	//test
	//cout << "firstRow:\n";
	//printArray(firstRow, N);
}

//产生原始阵列
void createSudokuArray(string filename) {
	//填入第一行
	for (int j = 0; j < N; j++)
		sudokuArray[0][j] = firstRow[j];
	//剩余行
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++){
			int k = (j + (N - i)) % N;//计算偏移坐标
			//cout << " deta= " << (N - i) << endl;
			sudokuArray[i][j] = firstRow[k];
		}		
	}
}

void printSudokuArray(string filename) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++)
			cout << sudokuArray[i][j] << " ";
		cout << sudokuArray[i][N - 1] << endl;
	}
	cout << endl;
	ofstream file(filename);
	if (!file.is_open()) {
		cout << "打开文件失败" << endl;
		return;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++)
			file << sudokuArray[i][j] << " ";
		file << sudokuArray[i][N - 1] << endl;
	}
}

void nextSudokuArray() {

}
