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
	//for (int i = 0; i < N; i++)
		//cout << number;
}

//������num�Ƴ�
void  Rules::delete_number(int num) {
	number[num] = false;
}
void Rules::print(){
	cout << "test: ";
	for(int num = 1; num <= N; num++)
		if(is_added_number(num))cout << num << " ";
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
void Space::print(){
	cout << "(" << row <<"," << col << "," << palace_index << ")";
}
/******************************************/
/******************************************/
//SudokuSolve.class

const string filename = "sudoku.txt";
SudokuSolve::SudokuSolve() {
	rows = new Rules[N];
	cols = new Rules[N];
	palaces = new Rules[N];
	spaces = new Space[N * N];
	sudoku_store = NULL;
	space_count = 0;
}

char* SudokuSolve::solve() {
	file.open("test.txt");
	if (!file.is_open()) cout << "file error\n";
	while (next_puzzle()) {//ȡ��һ������
		//������Ᵽ���վ�
		puzzle_solve();
	}
	return NULL;
}
void SudokuSolve::puzzle_solve() {

}

//ȡ�����⣬��ʼ�������У���
bool SudokuSolve::next_puzzle() {
	if (file.eof()) return false;
	string line;
	char c;
	int len = 0;
	space_count = 0;
	for (int i = 0; i < N + 1; i++) {//10��,iΪ�кţ�indexΪ�к�
		getline(file, line);
		if (i == 9)break;
		len = line.length();
		for (int j = 0, index = 0; j < len; j++) {
			c = line[j];
			//cout << c;
			if (c >= '0' && c <= '9') {
				array[i][index] = c;
				if (c == '0') {
					spaces[space_count++] = Space(i, index);
				}
				else {
					cols[index].add_number(c - '0');
					rows[i].add_number(c - '0');
					palaces[i / 3 + index / 3].add_number(c - '0');
				}
				index++;
			}
		}
		//cout << "\n";
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << array[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
	/*for (int i = 0; i < space_count; i++) {
		spaces[i].print();
		cout << "\n";
	}
	cout << "\n";
	for (int i = 0; i < N; i++) {
		rows[i].print();
		cout << "\n";
	}
	cout << "\n";
	for (int i = 0; i < N; i++) {
		cols[i].print();
		cout << "\n";
	}*/
	for (int i = 0; i < N; i++) {
		palaces[i].print();
		cout << "\n";
	}
	return true;
}


