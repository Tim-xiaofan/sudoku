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
//将数字num填入
void  Rules::add_number(int num) {
	number[num - 1] = true;
	//for (int i = 0; i < N; i++)
		//cout << number;
}

//将数字num移除
void  Rules::delete_number(int num) {
	number[num - 1] = false;
}
void Rules::reset(){
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
//判断当空格是否还有其它可行解;
bool Space::is_there_solutions() {
	if (used_count == solution_count) return false;
	return  true;
}
//返回下一个可行解, 没有则返回‘0’
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
//输出space
void Space::print(){
	cout << "(" << row <<"," << col << "," << palace_index << "):";
	for (int i = 0; i < solution_count; i++)
		cout << solutions[i] << " ";
}
//重置space
void Space::reset(){
	solution_count = 0;
	used_count = 0;
	reset_used();
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

//解出所有数独
char* SudokuSolve::solve() {
	file.open("test.txt");
	if (!file.is_open()) cout << "file error\n";
	//cout << "test 1\n";
	while (next_puzzle()) {//取得一个谜题
		//解决谜题保存终局
		init_spaces();
		puzzle_solve(0);
		//cout << "test 2\n";
		rules_reset();
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

//更新数字占用情况
void SudokuSolve::cover(int num, int space_index){
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	rows[row].add_number(num);
	cols[col].add_number(num);
	palaces[palace_index].add_number(num);
	array[row][col] = num;
}

//恢复
void SudokuSolve::resume(int space_index){
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	int num = spaces[space_index].current_num;
	rows[row].delete_number(num);
	cols[col].delete_number(num);
	palaces[palace_index].delete_number(num);
	array[row][col] = 0;
}

//初始化spaces,包括可填数字，数量
void SudokuSolve::init_spaces(){
	//cout << "test\n";
	cout << "space_count = " << space_count<< "\n";
	for (int i = 0; i < space_count; i++)
		for (int j = 1; j <= N; j++)
			if (try_to_add(j, i))
				spaces[i].solutions[spaces[i].solution_count++] = j + '0';
	/*for (int i = 0; i < space_count; i++) {
		spaces[i].print();
		cout << "\n";
	}*/	
}

//求解数独
bool SudokuSolve::puzzle_solve(int space_index) {
	int flag = 0;
	int count = spaces[space_index].solution_count;//当前空格可填数字个数
	int solution = 0;
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	if (space_index == space_count - 1) {//最后一个空格
		//验证可行解
		for (int i = 0; i < count && !spaces[space_index].used[i]; i++) {
			solution = spaces[space_index].solutions[i];
			if (try_to_add(solution, space_index)) {
				spaces[space_index].used[i] = true;
				spaces[space_index].used_count++;
				flag = 1;
				array[row][col] = solution + '0';
				break;
			}
		}
		//得到一个完整结果
		if (flag == 1) {
			print_array();
			return true;
		}
		else {
			int k = space_index - 1;
			while (k > 0) {//回溯
				if (spaces[k--].is_there_solutions()) {//回溯到有其他解的节点
					puzzle_solve(k);
					break;
				}
				else resume(k--);//恢复,0不用
			}
			if (k == 0) {//回溯到了第一个空格
				if (!spaces[0].is_there_solutions())return false;//无解
				puzzle_solve(0);
			}
		}
	}
	else {//中间的某个空格
		//验证可行解
		for (int i = 0; i < count && !spaces[space_index].used[i]; i++) {
			solution = spaces[space_index].solutions[i];
			if (try_to_add(solution, space_index)) {
				spaces[space_index].used[i] = true;
				spaces[space_index].used_count++;
				flag = 1;
				array[row][col] = solution + '0';
				break;
			}
		}
		//当前层有解,则继续往前求解
		if (flag == 1) {
			int k = space_index;
			puzzle_solve(++k);
			return true;
		
		}
		else {//当前层没有解, 则回溯
			int k = space_index - 1;
			while (k > 0) {//回溯
				if (!spaces[k--].is_there_solutions()) {//回溯到有其他解的节点
					puzzle_solve(k);
					break;
				}
				else resume(k--);//恢复,0不用
			}
			if (k == 0) {//回溯到了第一个空格
				if (!spaces[0].is_there_solutions())return false;//无解
				puzzle_solve(0);
			}
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

//判断数字num是否能填入
bool SudokuSolve::try_to_add(int num, int space_index){
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	//行，列， 宫不重复
	if (rows[row].is_added_number(num))return false;
	if (cols[col].is_added_number(num))return false;
	if (palaces[palace_index].is_added_number(num))return false;
	return true;
}

//取数独题，初始化宫，列，行
bool SudokuSolve::next_puzzle() {
	if (file.eof()) { cout << "file.eof()"; return false; }
	//cout << "test 4\n";
	string line;
	char c;
	int len = 0;
	space_count = 0;
	for (int i = 0; i < N + 1; i++) {//10行,i为行号，index为列号
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

