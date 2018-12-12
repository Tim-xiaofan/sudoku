#include "sudoku.h"
#include <string>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

const int N = 9;

const int No = 1;//ѧ��1120161736

int firstRow[N];//�����һ��

const int randow = 210;//����̶�

int sudokuArray[N][N];//������������

//���ڵ���
void printArray(int a[], int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "\n";
}

void createSudoku(int n, string filename) {
	//����
	void getFirstRow(int no);
	void createSudokuArray(string filename);
	void nextSudokuArray();
	void printSudokuArray(string filename);

	//ȷ����һ��
	//����ԭʼ����
	//���б任�õ�ʣ���35��
	//�����м�������Ƿ�����Ҫ�󣬲����㷴������Ĳ���
	while (n > 0) {
		//������һ��,��ѧ��������
		getFirstRow(No);
		//����ԭʼ����
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
	//���ȷ���ʼ������
	srand((unsigned int)time(NULL));
	int ran = 0 + rand() % randow;
	cout << "Trans...." << endl;
	for (int i = 0; i < ran; i++)
		next_permutation(number, number + N - 1);
	
	firstRow[0] = No;//����ѧ��
	for (int i = 1; i < N; i++)
		firstRow[i] = number[i - 1];
	//test
	//cout << "firstRow:\n";
	//printArray(firstRow, N);
}

//����ԭʼ����
void createSudokuArray(string filename) {
	//�����һ��
	for (int j = 0; j < N; j++)
		sudokuArray[0][j] = firstRow[j];
	//ʣ����
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++){
			int k = (j + (N - i)) % N;//����ƫ������
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
		cout << "���ļ�ʧ��" << endl;
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
