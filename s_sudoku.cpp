#include <string>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include "s_sudoku.h"

using namespace std;

ifstream test_file;
ofstream output_file;

/******************************************/
//Rules.class
bool Rules::is_added_number(char c) {
	int num = c - '0';
	if (num < 1) return false;
	if (number[num - 1] == true) return true;
	else return false;
}
//������num����
void  Rules::add_number(char c) {
	int num = c - '0';
	if (num < 1) return;//0��������
	number[num - 1] = true;
	//for (int i = 0; i < N; i++)
		//cout << number;
}

//������num�Ƴ�
void  Rules::delete_number(char c) {
	int num = c - '0';
	if (num < 1) return;//0��������
	number[num - 1] = false;
}
//����ʹ�����
void Rules::reset(){
	for (int i = 0; i < N; i++)
		number[i] = false;
}
void Rules::print(){
	cout << "rule: ";
	for(int num = 0; num <= N; num++)
		if(is_added_number(num + 1 + '0'))cout << num + 1 << " ";
	cout << "\n";
}
/******************************************/
/******************************************/
//Space.class
//�жϵ��ո��Ƿ����������н�;
bool Space::is_there_solutions() {
	if (used_count == solution_count) return false;
	return  true;
}
//������һ�����н�, û���򷵻ء�0��
char Space::next_solution() {
	if (!is_there_solutions()) return '0';
	for(int i = 0; i < solution_count; i++)
		if (!used[i]) {
			used_count++;
			used[i] = true;
			return solutions[i];
		}
	return '0';
}
//���space
void Space::print(){
	cout << "(" << row <<"," << col << "," << palace_index << ")all:";
	for (int i = 0; i < solution_count; i++)
		cout << solutions[i] << " ";
	cout << endl;
	cout << "(" << row << "," << col << "," << palace_index << ")unsed:";
	for (int i = 0; i < solution_count; i++)
		if(!used[i])
		cout << solutions[i] << " ";
	cout << endl;
}
//����space
void Space::reset(){
	solution_count = 0;
	used_count = 0;
	reset_used();
}
/******************************************/
/******************************************/
//SudokuSolve.class
const string filename = "sudoku.txt";
//��̬�����ĳ�ʼ��
Rules* SudokuSolve::rows = new Rules[N];
Rules* SudokuSolve::cols = new Rules[N];
Rules* SudokuSolve::palaces = new Rules[N];
Space* SudokuSolve::spaces = new Space[N*N];
char SudokuSolve::array[N][N];

SudokuSolve::SudokuSolve() {
	sudoku_store = NULL;
	space_count = 0;
	init_static();
}

//�����������
char* SudokuSolve::solve(char* filename) {
	test_file.open(filename);
	output_file.open("sudoku.txt");
	if (!test_file.is_open()) cout << "file error\n";
	//cout << "test 1\n";
	while (get_puzzle()) {//ȡ��һ������
		//������Ᵽ���վ�
		init_spaces();
		//���
		//cout << "��⣺\n";
		//print_array();
		puzzle_solve(0);
		//cout << "test 2\n";
		rules_reset();
	}
	//cout << "test 1\n";
	return NULL;
}

void SudokuSolve::print_array(){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++)
			output_file << array[i][j] << " ";
		output_file << array[i][N-1]  <<"\n";//��ĩ�޿ո�
	}
	output_file << "\n";
}

//��������ռ�����
void SudokuSolve::refresh_rules(char num, int space_index, bool delete_num){
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	if (delete_num) {//�Ƴ�ĳ������
		//cout << "ɾ����" << space_index + 1 << "�ո��" << num << endl;
		rows[row].delete_number(num);
		cols[col].delete_number(num);
		palaces[palace_index].delete_number(num);
		array[row][col] = '0';
	}
	else {//���ĳ������
		//cout << "���" << space_index + 1 << "�ո�����" << num << endl;
		rows[row].add_number(num);
		cols[col].add_number(num);
		palaces[palace_index].add_number(num);
		array[row][col] = num;
	}
}

//���ݵ�ĳ���н�ڵ�ʱҪ�Ƚ���ռ�ø���,�����
//���ڻ��ݵ��Ľڵ��Ѿ�����ĳ�����֣�Ҫ���Ƴ��������
void SudokuSolve::clear_space(int space_index){
	char num = spaces[space_index].current_num;
	refresh_rules(num, space_index, true);
}

//��ʼ��spaces,�����������֣�����
void SudokuSolve::init_spaces(){
	//cout << "test\n";
	//cout << "space_count = " << space_count<< "\n";
	for (int i = 0; i < space_count; i++)
		for (int j = 1; j <= N; j++)
			if (try_to_add(j + '0', i))
				spaces[i].solutions[spaces[i].solution_count++] = j + '0';
	/*for (int i = 0; i < space_count; i++) {
		spaces[i].print();
		cout << "\n";
	}*/
}

void SudokuSolve::init_static(){
	memset(array, false, sizeof(array));
}

//�����ǰ�ո�����У��У�����ռ�����
void SudokuSolve::print_space_status(int space_index){
	spaces[space_index].print();
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	cout << "�У�\n";
	rows[row].print();
	cout << "�У�\n";
	cols[col].print();
	cout << "����\n";
	palaces[palace_index].print();
}


//�������
bool SudokuSolve::puzzle_solve(int space_index) {
	int flag = 0;//�Ƿ��н�
	//cout << "test\n";
	int count = spaces[space_index].solution_count;//��ǰ�ո�������ָ�������������ʱȷ����
	char solution = '0';
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	if (space_index == space_count - 1) {//���һ���ո�
		//��֤���н�
		//һ�������Ƿ����Ƿ��ù����Ƿ������������
		//cout << "��ʼ���" << space_index + 1 << "�ո�\n";
		//print_space_status(space_index);
		//print_array();
		for (int i = 0; i < count; i++) {
			if (!spaces[space_index].used[i]) {//�Ƿ��ù�
				solution = spaces[space_index].solutions[i];
				//cout << "get solution = " << solution << endl;
				if (try_to_add(solution, space_index)) {//����Ƿ���Ϲ���
					spaces[space_index].used[i] = true;
					spaces[space_index].used_count++;
					spaces[space_index].current_num = solution;
					flag = 1;
					//����
					refresh_rules(solution, space_index, false);
					//cout << "add solution = " << solution << endl;
					array[row][col] = solution;
					break;
				}
			}
		}
		//�õ�һ���������
		if (flag == 1) {
			//cout << "�õ�һ���������\n";
			print_array();
			return true;
		}
		else {
			if (space_index == 0) {//
				//cout << "�޽�\n";
				return false;
			}
			int k = space_index - 1;
			clear_space(k);
		}
	}
	else {//�м��ĳ���ո�
		//��֤���н�
		//cout << "��ʼ���" << space_index + 1 << "�ո�\n";
		//print_space_status(space_index);
		//print_array();
		//cout << "end\n";
		for (int i = 0; i < count; i++) {
			if (!spaces[space_index].used[i]) {//û���ù�
				solution = spaces[space_index].solutions[i];
				//cout << "get solution = " << solution << endl;
				if (try_to_add(solution, space_index)) {//����Ƿ���Ϲ���
					spaces[space_index].used[i] = true;
					spaces[space_index].used_count++;
					spaces[space_index].current_num = solution;
					flag = 1;
					//cout << "add solution = " << solution << endl;
					//����
					refresh_rules(solution, space_index, false);
					//cout << "add solution = " << solution << endl;
					array[row][col] = solution;
					break;
				}
			}
		}
		//��ǰ�ո��н�,�������ǰ���
		if (flag == 1) {
			//cout << "��ǰ�ո��н�,������ǰ���\n";
			int k = space_index + 1;
			puzzle_solve(k);
			return true;
		}
		else {
			if (space_index == 0) {//�޽�
				cout << "�޽�\n";
				return false;
			}
			int k = space_index - 1;
			//cout << "��ǰ�ո��޽�,������һ���ո�\n";
			spaces[space_index].current_num = '0';
			reset_space(space_index);
			//cout << "reset_space\n";
			clear_space(k);
			//cout << "clear_space\n";
			puzzle_solve(k);
		}
	}
	return false;
}

void SudokuSolve::rules_reset(){
	for (int i = 0; i < N; i++) {
		rows[i].reset();
		cols[i].reset();
		palaces[i].reset();
	}
	for (int i = 0; i < space_count; i++)
		spaces[i].reset();
	space_count = 0;
}

//�ж�����num�Ƿ�������
bool SudokuSolve::try_to_add(char num, int space_index){
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
bool SudokuSolve::get_puzzle() {
	if (test_file.eof()) {  return false; }
	//cout << "test 4\n";
	string line;
	char c;
	int len = 0;
	space_count = 0;
	for (int i = 0; i < N + 1; i++) {//��10��,iΪ�кţ�indexΪ�к�
		if (test_file.eof()) { break; }
		getline(test_file, line);
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
					cols[index].add_number(c);
					rows[i].add_number(c);
					palaces[i / 3 * 3 + index / 3].add_number(c);
					//cout << i / 3 + index / 3 << endl;
				}
				index++;
			}
		}
		//cout << "\n";
	}
	//cout << "test 4\n";
	/*for (int i = 0; i < N; i++) {
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
	cout << "\n";*/
	/*cout << "�У�" << endl;
	for (int i = 0; i < N; i++) {
		rows[i].print();
		cout << "\n";
	}
	cout << "\n";
	cout << "�У�" << endl;
	for (int i = 0; i < N; i++) {
		cols[i].print();
		cout << "\n";
	}
	cout << "����" << endl;
	for (int i = 0; i < N; i++) {
		palaces[i].print();
		cout << "\n";
	}
	cout << "\n";*/
	return true;
}

