#include <string>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include "s_sudoku.h"

using namespace std;

ifstream file;

/******************************************/
//Rules.class
bool Rules::is_added_number(int num) {
	if (number[num] == true) return true;
	else return false;
}
//������num����
void  Rules::add_number(int num) {
	number[num] = true;
}

//������num�Ƴ�
void  Rules::delete_number(int num) {
	number[num] = false;
}
/******************************************/
/******************************************/
//Space.class
//�жϵ��ո��Ƿ����������н�;
bool Space::is_there_solutions() {
	if (remain_count == solution_cout) return false;
	return  true;
}
//������һ�����н�, û���򷵻ء�0��
char Space::next_solution() {
	if (!is_there_solutions()) return '0';
	return solutions[remain_count++];
}
/******************************************/
/******************************************/
//SudokuSolve.class

const string filename = "sudoku.txt";
SudokuSolve::SudokuSolve() {
	rows = new Rules[N];
	cols = new Rules[N];
	palaces = new Rules[N];
	spaces = NULL;
	sudoku_store = NULL;
}

char* SudokuSolve::solve() {
	file.open("test.txt");
	if (!file.is_open()) cout << "file error\n";
	int i = 0;
	while (next_puzzle()) {//ȡ��һ������
		//������Ᵽ���վ�
		i++;
		cout << "i = "<< i << endl;
		//puzzle_solve();
	}
	return NULL;
}

bool SudokuSolve::next_puzzle() {
	if (file.eof()) return false;
	string line;
	for (int i = 0; i < N + 1; i++) {
		getline(file, line);
		cout << line << endl;
	}
	return true;
}



