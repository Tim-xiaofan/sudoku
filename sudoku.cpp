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

int firstRow[N] = { No,2 ,3, 4 , 5, 6, 7, 8, 9 };//�����һ��

const int randow = 210;//����̶�

int sudokuArray[N][N];//������������

const string filename = "sudoku.txt";

string sudokuFileString;//�������ɵ���������

int need = 0;//ʣ��������


//���ڵ���
void printArray(int a[], int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "\n";
}

void createSudokuFile(int n, string filename) {
	//����
	void getFirstPermutation(int no);
	void createModelSudoku(string filename);
	void newFromModel();
	void outputSudoku(string filename);

	sudokuFileString = "";//��ʼ���Ϊ��
	need = n;// ��ʼ��������������
	getFirstPermutation(No);//�õ���һ�е�һ������

	//ȷ����һ��
	//����ԭʼ����
	//���б任�õ�36�����ظ��ĺϷ���������
	//�����м�������Ƿ�����Ҫ�󣬲����㷴������Ĳ���
	while (need > 0) {
		//����ԭʼ����
		createModelSudoku(filename);
		//cout << "Model Array:\n";
		//outputSudoku(filename);
		//���б任�õ�36�����ظ��ĺϷ���������
		newFromModel();
		next_permutation(firstRow + 1, firstRow + N);
	}
	//cout << sudokuFileString;
	outputSudoku(filename);
}

void getFirstPermutation(int No) {
	//���ȷ���ʼ������
	srand((unsigned int)time(NULL));
	int ran = 0 + rand() % randow;
	cout << "Trans...." << endl;
	for (int i = 0; i < ran; i++)
		next_permutation(firstRow + 1, firstRow + N);
	//cout << "firstPermutation:\n";
	//printArray(firstRow, N);
}

//����ԭʼ����
void createModelSudoku(string filename) {
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

void outputSudoku(string filename) {
	ofstream file(filename);
	if (!file.is_open()) {
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	file << sudokuFileString;
}

//��ԭʼ���л����Ͻ��б任�����36������
void newFromModel() {
	int A[3] = { 4, 5, 6 };//456Ϊһ��
	int B[3] = { 7, 8, 9 };//456Ϊһ��
	//ǰ���в���
	string firstThreeRows = "";// ����123��
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < N - 1; j++) {
			firstThreeRows += to_string(sudokuArray[i][j]);
			firstThreeRows += " ";
		}
		firstThreeRows += to_string(sudokuArray[i][N-1]);
		firstThreeRows += "\n";//����
	}
	//cout << sudokuString;
	for (int a = 0; a < 6; a++) {
		//ȷ��A��456,��һ������
		//cout << "!!!!!!!!!!A:\n";
		//printArray(A, 3);
		string midThreeRows = "";//����456��
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < N - 1; j++) {
				//ÿ����һ�����֣�ֱ�ӱ��档ע��ո�ͻ��С�
				//cout << "��" << sudokuArray[A[index] - 1][j] << "��";
				midThreeRows += to_string(sudokuArray[A[i] - 1][j]);
				midThreeRows += " ";
				//cout <<"\n<"<< sudokuString << ">" << endl;
				//cout << sudokuString;
			}
			//cout << "��" << sudokuArray[A[index] - 1][N - 1] << "��" << endl;
			midThreeRows += to_string(sudokuArray[A[i] - 1][N - 1]);//��βû�пո�
			//cout << "\n<" << sudokuString << ">" << endl;
			midThreeRows += "\n";//����
		}
		//cout << "transA:";
		//cout << "\n<" << sudokuString << ">" << endl;
		//ͬһ��A�����п�����6�ֲ�ͬ������
		for (int b = 0; b < 6; b++) {
			//ȷ��B��789����һ������
			//cout << "B:\n";
			//printArray(B, 3);
			string lastThreeRows = "";
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < N - 1; j++) {
					//ÿ����һ�����֣�ֱ�ӱ��档���Կո�ͻ��С�
					//cout << "��" << sudokuArray[B[index] - 1][j] << "��";
					lastThreeRows += to_string(sudokuArray[B[i] - 1][j]);
					lastThreeRows += " ";
				}
				//cout << "��" << sudokuArray[B[index] - 1][N - 1] << "��" << endl;
				lastThreeRows += to_string(sudokuArray[B[i] - 1][N - 1]);//��βû�пո�
				lastThreeRows += "\n";//����
				//cout << sudokuString;
			}
			//ʣ���������仯-1
			need--;
			//cout << "need = " << need << endl;
			//cout << "transB:";
			string oneSudokuString = firstThreeRows + midThreeRows + lastThreeRows;
			sudokuFileString += oneSudokuString;
			//cout << oneSudokuString;
			if (need == 0) return;//Ϊ���򣬽�������
			//cout << "\n";//����������м����
			sudokuFileString += "\n";
			//B����һ������
			next_permutation(B, B + 3);
		}
		//A����һ������
		next_permutation(A, A + 3);
	}
}
