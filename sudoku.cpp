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

int firstRow[N] = { No,2 ,3, 4 , 5, 6, 7, 8, 9 };//保存第一行

const int randow = 210;//随机程度

int sudokuArray[N][N];//保存数独阵列

const string filename = "sudoku.txt";

string sudokuFileString;//保存生成的所有阵列

int need = 0;//剩余需求量


//用于调试
void printArray(int a[], int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "\n";
}

void createSudokuFile(int n, string filename) {
	//申明
	void getFirstPermutation(int no);
	void createModelSudoku(string filename);
	void newFromModel();
	void outputSudoku(string filename);

	sudokuFileString = "";//初始结果为空
	need = n;// 初始化数独需求数量
	getFirstPermutation(No);//得到第一行第一个排列

	//确定第一行
	//生成原始阵列
	//进行变换得到36个不重复的合法数独阵列
	//过程中检查数量是否满足要求，不满足反复上面的不走
	while (need > 0) {
		//生成原始阵列
		createModelSudoku(filename);
		//cout << "Model Array:\n";
		//outputSudoku(filename);
		//进行变换得到36个不重复的合法数独阵列
		newFromModel();
		next_permutation(firstRow + 1, firstRow + N);
	}
	//cout << sudokuFileString;
	outputSudoku(filename);
}

void getFirstPermutation(int No) {
	//随机确定最开始的排列
	srand((unsigned int)time(NULL));
	int ran = 0 + rand() % randow;
	cout << "Trans...." << endl;
	for (int i = 0; i < ran; i++)
		next_permutation(firstRow + 1, firstRow + N);
	//cout << "firstPermutation:\n";
	//printArray(firstRow, N);
}

//产生原始阵列
void createModelSudoku(string filename) {
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

void outputSudoku(string filename) {
	ofstream file(filename);
	if (!file.is_open()) {
		cout << "打开文件失败" << endl;
		return;
	}
	file << sudokuFileString;
}

//在原始阵列基础上进行变换并输出36个排列
void newFromModel() {
	int A[3] = { 4, 5, 6 };//456为一组
	int B[3] = { 7, 8, 9 };//456为一组
	//前三行不变
	string firstThreeRows = "";// 保存123行
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < N - 1; j++) {
			firstThreeRows += to_string(sudokuArray[i][j]);
			firstThreeRows += " ";
		}
		firstThreeRows += to_string(sudokuArray[i][N-1]);
		firstThreeRows += "\n";//换行
	}
	//cout << sudokuString;
	for (int a = 0; a < 6; a++) {
		//确定A组456,的一个排列
		//cout << "!!!!!!!!!!A:\n";
		//printArray(A, 3);
		string midThreeRows = "";//保存456行
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < N - 1; j++) {
				//每生成一个数字，直接保存。注意空格和换行。
				//cout << "（" << sudokuArray[A[index] - 1][j] << "）";
				midThreeRows += to_string(sudokuArray[A[i] - 1][j]);
				midThreeRows += " ";
				//cout <<"\n<"<< sudokuString << ">" << endl;
				//cout << sudokuString;
			}
			//cout << "（" << sudokuArray[A[index] - 1][N - 1] << "）" << endl;
			midThreeRows += to_string(sudokuArray[A[i] - 1][N - 1]);//行尾没有空格
			//cout << "\n<" << sudokuString << ">" << endl;
			midThreeRows += "\n";//换行
		}
		//cout << "transA:";
		//cout << "\n<" << sudokuString << ">" << endl;
		//同一个A的排列可以有6种不同的排列
		for (int b = 0; b < 6; b++) {
			//确定B组789，的一个排列
			//cout << "B:\n";
			//printArray(B, 3);
			string lastThreeRows = "";
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < N - 1; j++) {
					//每生成一个数字，直接保存。足以空格和换行。
					//cout << "（" << sudokuArray[B[index] - 1][j] << "）";
					lastThreeRows += to_string(sudokuArray[B[i] - 1][j]);
					lastThreeRows += " ";
				}
				//cout << "（" << sudokuArray[B[index] - 1][N - 1] << "）" << endl;
				lastThreeRows += to_string(sudokuArray[B[i] - 1][N - 1]);//行尾没有空格
				lastThreeRows += "\n";//换行
				//cout << sudokuString;
			}
			//剩余需求量变化-1
			need--;
			//cout << "need = " << need << endl;
			//cout << "transB:";
			string oneSudokuString = firstThreeRows + midThreeRows + lastThreeRows;
			sudokuFileString += oneSudokuString;
			//cout << oneSudokuString;
			if (need == 0) return;//为零则，结束生成
			//cout << "\n";//添加数独阵列间空行
			sudokuFileString += "\n";
			//B的下一个排列
			next_permutation(B, B + 3);
		}
		//A的下一个排列
		next_permutation(A, A + 3);
	}
}
