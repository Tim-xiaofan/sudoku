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
	if (number[num - 1] == true) return true;
	else return false;
}
//������num����
void  Rules::add_number(int num) {
	number[num - 1] = true;
	//for (int i = 0; i < N; i++)
		//cout << number;
}

//������num�Ƴ�
void  Rules::delete_number(int num) {
	number[num - 1] = false;
}
void Rules::clear(){
	for (int i = 0; i < N; i++)
		number[i] = false;
}
void Rules::print(){
	cout << "test: ";
	for(int num = 0; num <= N; num++)
		if(is_added_number(num + 1))cout << num + 1 << " ";
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
	cout << "(" << row <<"," << col << "," << palace_index << "):";
	for (int i = 0; i < remain_count; i++)
		cout << solutions[i] << " ";
}
/******************************************/
/******************************************/
//SudokuSolve.class

const string filename = "sudoku.txt";
SudokuSolve::SudokuSolve() {
	rows = new Rules[N];
	cols = new Rules[N];
	palaces = new Rules[N];
	spaces = new Space[N*N];
	sudoku_store = NULL;
	space_count = 0;
}

//�����������
char* SudokuSolve::solve() {
	file.open("test.txt");
	if (!file.is_open()) cout << "file error\n";
	//cout << "test 1\n";
	while (next_puzzle()) {//ȡ��һ������
		//������Ᵽ���վ�
		//init_spaces();
		//puzzle_solve(0);
		//cout << "test 2\n";
		rules_clear();
	}
	cout << "test 1\n";
	return NULL;
}

void SudokuSolve::print_array(){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << array[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
}

void SudokuSolve::refresh(int num, int space_index){
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	rows[row].add_number(num);
	cols[col].add_number(num);
	palaces[palace_index].add_number(num);
	array[row][col] = num;
}

//��ʼ��spaces,�����������֣�����
void SudokuSolve::init_spaces(){
	//cout << "test\n";
	cout << "space_count = " << space_count<< "\n";
	for (int i = 0; i < space_count; i++)
		for (int j = 1; j <= N; j++)
			if (try_to_add(j, i))
				spaces[i].solutions[spaces[i].remain_count++] = j + '0';
	for (int i = 0; i < space_count; i++) {
		spaces[i].print();
		cout << "\n";
	}		
}

//�������
bool SudokuSolve::puzzle_solve(int k) {
	int flag = 0;
	if (k == space_count - 1) {
		//�ҿ��н�
		for (int i = 1; i <= N; i++) //�ж�i�Ƿ�Ϊ���н�
			if (try_to_add(i, k)) {
				flag = 1;
				//���µ�ǰ״̬
				refresh(i, k);
				break;
			}
		if (flag == 0)return false;
		//������
		print_array();
		return true;
	}
	else {
		//�ҵ�ǰ����н�
		for (int i = 1; i <= N; i++) //�ж�i�Ƿ�Ϊ���н�
			if (try_to_add(i, k)) {
				//���µ�ǰռ��״̬
				refresh(i, k);
				if(puzzle_solve(k + 1)) flag = 1;
			}
	}
	return false;
}

void SudokuSolve::rules_clear(){
	for (int i = 0; i < N; i++) {
		rows[i].clear();
		cols[i].clear();
		palaces[i].clear();
	}
	space_count = 0;
}

//�ж�����num�Ƿ�������
bool SudokuSolve::try_to_add(int num, int space_index){
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	//�У��У� �����ظ�
	if (rows[row].is_added_number(num))return false;
	if (cols[col].is_added_number(num))return false;
	if (palaces[palace_index].is_added_number(num))return false;
	return true;
}

//ȡ�����⣬��ʼ�������У���
bool SudokuSolve::next_puzzle() {
	if (file.eof()) { cout << "file.eof()"; return false; }
	//cout << "test 4\n";
	string line;
	char c;
	int len = 0;
	space_count = 0;
	for (int i = 0; i < N + 1; i++) {//10��,iΪ�кţ�indexΪ�к�
		if (file.eof()) { break; }
		getline(file, line);
		//cout <<'\\'<< line <<'\\'<< endl;
		if (i == 9)break;
		len = line.length();
		for (int j = 0, index = 0; j < len; j++) {
			c = line[j];
			//cout << c;
			if (c >= '0' && c <= '9') {
				array[i][index] = c;
				if (c == '0') 
					spaces[space_count++] = Space(i, index);
				else {
					cols[index].add_number(c - '0');
					rows[i].add_number(c - '0');
					palaces[i / 3 * 3 + index / 3].add_number(c - '0');
					//cout << i / 3 + index / 3 << endl;
				}
				index++;
			}
		}
		//cout << "\n";
	}
	//cout << "test 4\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << array[i][j] << " ";
		cout << "\n";
	}
	//cout << "test 4\n";
	cout << "\n";
	/*for (int i = 0; i < space_count; i++) {
		spaces[i].print();
		cout << "\n";
	}
	cout << "\n";
	/*for (int i = 0; i < N; i++) {
		rows[i].print();
		cout << "\n";
	}
	cout << "\n";*/
	/*for (int i = 0; i < N; i++) {
		cols[i].print();
		cout << "\n";
	}
	/*for (int i = 0; i < N; i++) {
		palaces[i].print();
		cout << "\n";
	}
	cout << "\n";*/
	return true;
}

