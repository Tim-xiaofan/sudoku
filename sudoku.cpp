#include "sudoku.h"
#include <string>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

const int N = 9;

const char No = '1';//ѧ��1120161736

int firstRow[N] = { No,2 ,3, 4 , 5, 6, 7, 8, 9 };//�����һ��

const int randow = 210;//����̶�

const string filename = "sudoku.txt";

ofstream test_file(filename);

//ƫ��ֵ
int offset[N] = { 0,3,6,1,4,7,2,5,8 };

//���ڵ���
/*void printArray(int a[], int n) {
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "\n";
}*/

/*******************************************************/
//��ArgCheck��ʵ��
int ArgCheck::check() {
	//����
	bool isPurenumber(char* s);
	//��֤��������ĺϷ���
	if (argc != 3) {//����
		cout << "�����������ٻ����" << endl;
		return checkResult = INVALID;
	}
	if (strcmp("-c", argv[1]) != 0 && strcmp("-s", argv[1]) != 0)//-s��-c���
	{
		cout << "������-c��-s" << endl;
		return checkResult = INVALID;
	}
	if (strcmp("-c", argv[1]) == 0) {//�����վ�
		if (!isPurenumber(argv[2])) {//�����վ�������Ϊ����
			cout << "�����վ�������Ϊ����" << endl;
			return checkResult = INVALID;
		}
		return checkResult = FORC;
	}
	else {//�������
		return checkResult = FORS;
	}
}

//�ж������Ƿ��ʴ�����
bool isPurenumber(char* s) {
	int n = strlen(s);
	for (int i = 0; i < n; i++)
		if (s[i] > '9' || s[i] < '0')
			return false;
	return true;
}

/*******************************************************/
/*******************************************************/
//��SudokuFactory��ʵ��
//���ɵ�һ��ģ��
void SudokuFactory::createFirstModel() {
	void printSudoku(int a[N][N]);
	char number[N] = { '1','2', '3', '4', '5', '6', '7', '8', '9' };
	//���ȷ���ʼ������
	srand((unsigned int)time(NULL));
	int ran = 0 + rand() % randow;
	//cout << "AtomCreate...." << endl;
	for (int i = 0; i < ran; i++)
		next_permutation(number + 1, number + N);
	//����ѧ��
	firstR[0] = '1';
	for (int i = 1; i < N; i++)
		firstR[i] = number[i];
	//cout << "��һ������:\n";
	//printArray(firstR, N);
	//����ģ����������
	//�����һ��
	for (int j = 0; j < N; j++)
		model[0][j] = firstR[j];
	//ʣ����
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int k = (j +  offset[i]) % N;//����ƫ������
			//cout << " deta= " << (N - i) << endl;
			model[i][j] = firstR[k];
		}
	}
	//cout << "��һ��model:\n";
	//printSudoku(model);
}


//����ģ��
void SudokuFactory::refreshModel() {
	//cout << "refreshModel()\n";
	void printSudoku(int a[N][N]);
	next_permutation(firstR + 1, firstR + N);//ȡ����һ������
	//cout << "�µ�����:\n";
	//printArray(firstR, N);
	//����ģ����������
	//�����һ��
	for (int j = 0; j < N; j++)
		model[0][j] = firstR[j];
	//ʣ����
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int k = (j + (N - i)) % N;//����ƫ������
			//cout << " deta= " << (N - i) << endl;
			model[i][j] = firstR[k];
		}
	}
	//cout << "�µ�model:\n";
	//printSudoku(model);
}

//��ԭʼ���л����Ͻ��б任������36������
void SudokuFactory::newFromModel() {
	//cout << "newFromModel()\n";
	int A[3] = { 4, 5, 6 };//456Ϊһ��
	int B[3] = { 7, 8, 9 };//456Ϊһ��
	//ǰ���в���
	char firstThreeRows[N * 6];// ����123��
	int index = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < N - 1; j++) {
			firstThreeRows [index++]= (model[i][j]);
			firstThreeRows[index++] = ' ';
		}
		firstThreeRows[index++] = (model[i][N - 1]);
		firstThreeRows[index++] = '\n';//����
	}
	//cout << sudokuString;
	for (int a = 0; a < 6; a++) {
		//ȷ��A��456,��һ������
		//cout << "!!!!!!!!!!A:\n";
		//printArray(A, 3);
		char midThreeRows[6 * N];//����456��
		int index = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < N - 1; j++) {
				//ÿ����һ�����֣�ֱ�ӱ��档ע��ո�ͻ��С�
				//cout << "��" << sudokuArray[A[index] - 1][j] << "��";
				midThreeRows[index++] = (model[A[i] - 1][j]);
				midThreeRows[index++] = ' ';
				//cout <<"\n<"<< sudokuString << ">" << endl;
				//cout << sudokuString;
			}
			//cout << "��" << sudokuArray[A[index] - 1][N - 1] << "��" << endl;
			midThreeRows[index++] = (model[A[i] - 1][N - 1]);//��βû�пո�
			//cout << "\n<" << sudokuString << ">" << endl;
			midThreeRows[index++] = '\n';//����
		}
		//cout << "transA:";
		//cout << "\n<" << sudokuString << ">" << endl;
		//ͬһ��A�����п�����6�ֲ�ͬ������
		for (int b = 0; b < 6; b++) {
			//ȷ��B��789����һ������
			//cout << "B:\n";
			//printArray(B, 3);
			char lastThreeRows[6 * N];
			int index = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < N - 1; j++) {
					//ÿ����һ�����֣�ֱ�ӱ��档ע��ո�ͻ��С�
					//cout << "��" << sudokuArray[B[index] - 1][j] << "��";
					lastThreeRows[index++] = (model[B[i] - 1][j]);
					lastThreeRows[index++] = ' ';
				}
				//cout << "��" << sudokuArray[B[index] - 1][N - 1] << "��" << endl;
				lastThreeRows[index++] = (model[B[i] - 1][N - 1]);//��βû�пո�
				lastThreeRows[index++] = '\n';//����
				//cout << sudokuString;
			}
			//ʣ���������仯-1
			need--;
			//ֱ��������ļ�
			store(firstThreeRows,midThreeRows,lastThreeRows);
			//cout << "need = " << need << endl;
			//cout << "transB:";
			//cout << oneSudokuString;
			if (need == 0) return;//Ϊ���򣬽�������
			//cout << "\n";//����������м����
			sudokuStore[index_store++] = '\n';
			//B����һ������
			next_permutation(B, B + 3);
		}
		//A����һ������
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

//�����վ��ļ�
char* SudokuFactory::createSudokuFile() {
	while (need > 0) {
		newFromModel();
		refreshModel();
	}
	sudokuStore[index_store++] = '\0';//�ǵ����������ʶ
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
