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
//将数字num填入
void  Rules::add_number(char c) {
	int num = c - '0';
	if (num < 1) return;//0不做处理
	number[num - 1] = true;
	//for (int i = 0; i < N; i++)
		//cout << number;
}

//将数字num移除
void  Rules::delete_number(char c) {
	int num = c - '0';
	if (num < 1) return;//0不做处理
	number[num - 1] = false;
}
//重置使用情况
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
//静态变量的初始化
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

//解出所有数独
char* SudokuSolve::solve(char* filename) {
	test_file.open(filename);
	output_file.open("sudoku.txt");
	if (!test_file.is_open()) cout << "file error\n";
	//cout << "test 1\n";
	while (get_puzzle()) {//取得一个谜题
		//解决谜题保存终局
		init_spaces();
		//求解
		//cout << "求解：\n";
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
		output_file << array[i][N-1]  <<"\n";//行末无空格
	}
	output_file << "\n";
}

//更新数字占用情况
void SudokuSolve::refresh_rules(char num, int space_index, bool delete_num){
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	if (delete_num) {//移除某个数字
		//cout << "删除第" << space_index + 1 << "空格的" << num << endl;
		rows[row].delete_number(num);
		cols[col].delete_number(num);
		palaces[palace_index].delete_number(num);
		array[row][col] = '0';
	}
	else {//添加某个数字
		//cout << "向第" << space_index + 1 << "空格的添加" << num << endl;
		rows[row].add_number(num);
		cols[col].add_number(num);
		palaces[palace_index].add_number(num);
		array[row][col] = num;
	}
}

//回溯到某个有解节点时要先进行占用更新,再求解
//由于回溯到的节点已经填了某个数字，要先移除这个数字
void SudokuSolve::clear_space(int space_index){
	char num = spaces[space_index].current_num;
	refresh_rules(num, space_index, true);
}

//初始化spaces,包括可填数字，数量
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

//输出当前空格相关行，列，宫的占用情况
void SudokuSolve::print_space_status(int space_index){
	spaces[space_index].print();
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	cout << "行：\n";
	rows[row].print();
	cout << "列：\n";
	cols[col].print();
	cout << "宫：\n";
	palaces[palace_index].print();
}


//求解数独
bool SudokuSolve::puzzle_solve(int space_index) {
	int flag = 0;//是否有解
	//cout << "test\n";
	int count = spaces[space_index].solution_count;//当前空格可填数字个数（读入数独时确定）
	char solution = '0';
	int row = spaces[space_index].get_row();
	int col = spaces[space_index].get_col();
	int palace_index = spaces[space_index].get_palace();
	if (space_index == space_count - 1) {//最后一个空格
		//验证可行解
		//一个数字是否可填：是否用过；是否符合数独规则
		//cout << "开始填第" << space_index + 1 << "空格\n";
		//print_space_status(space_index);
		//print_array();
		for (int i = 0; i < count; i++) {
			if (!spaces[space_index].used[i]) {//是否用过
				solution = spaces[space_index].solutions[i];
				//cout << "get solution = " << solution << endl;
				if (try_to_add(solution, space_index)) {//检查是否符合规则
					spaces[space_index].used[i] = true;
					spaces[space_index].used_count++;
					spaces[space_index].current_num = solution;
					flag = 1;
					//更新
					refresh_rules(solution, space_index, false);
					//cout << "add solution = " << solution << endl;
					array[row][col] = solution;
					break;
				}
			}
		}
		//得到一个完整结果
		if (flag == 1) {
			//cout << "得到一个完整结果\n";
			print_array();
			return true;
		}
		else {
			if (space_index == 0) {//
				//cout << "无解\n";
				return false;
			}
			int k = space_index - 1;
			clear_space(k);
		}
	}
	else {//中间的某个空格
		//验证可行解
		//cout << "开始填第" << space_index + 1 << "空格\n";
		//print_space_status(space_index);
		//print_array();
		//cout << "end\n";
		for (int i = 0; i < count; i++) {
			if (!spaces[space_index].used[i]) {//没有用过
				solution = spaces[space_index].solutions[i];
				//cout << "get solution = " << solution << endl;
				if (try_to_add(solution, space_index)) {//检查是否符合规则
					spaces[space_index].used[i] = true;
					spaces[space_index].used_count++;
					spaces[space_index].current_num = solution;
					flag = 1;
					//cout << "add solution = " << solution << endl;
					//更新
					refresh_rules(solution, space_index, false);
					//cout << "add solution = " << solution << endl;
					array[row][col] = solution;
					break;
				}
			}
		}
		//当前空格有解,则继续往前求解
		if (flag == 1) {
			//cout << "当前空格有解,继续往前求解\n";
			int k = space_index + 1;
			puzzle_solve(k);
			return true;
		}
		else {
			if (space_index == 0) {//无解
				cout << "无解\n";
				return false;
			}
			int k = space_index - 1;
			//cout << "当前空格无解,返回上一个空格\n";
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

//判断数字num是否能填入
bool SudokuSolve::try_to_add(char num, int space_index){
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
bool SudokuSolve::get_puzzle() {
	if (test_file.eof()) {  return false; }
	//cout << "test 4\n";
	string line;
	char c;
	int len = 0;
	space_count = 0;
	for (int i = 0; i < N + 1; i++) {//读10行,i为行号，index为列号
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
	/*cout << "行：" << endl;
	for (int i = 0; i < N; i++) {
		rows[i].print();
		cout << "\n";
	}
	cout << "\n";
	cout << "列：" << endl;
	for (int i = 0; i < N; i++) {
		cols[i].print();
		cout << "\n";
	}
	cout << "宫：" << endl;
	for (int i = 0; i < N; i++) {
		palaces[i].print();
		cout << "\n";
	}
	cout << "\n";*/
	return true;
}

