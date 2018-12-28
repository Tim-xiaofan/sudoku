#pragma once
#ifndef S_SUDOKU_H
#define S_SUDOKU_H

#include <fstream>
#include <string>
//列、行、宫
class Rules {
	static const int N = 9;
	bool* number;//数字填写情况，number[i] = true,表示(i + 1), i + 1 = (1, 2, ...,9)已填入
public :
	Rules(){
		number = new bool[N];
		for (int i = 0; i < N; i++)
			number[i] = false;
	}
	//判断数字num是否已经填入
	bool is_added_number(int num);
	//将数字num填入
	void add_number(int number);
	////将数字num移除
	void delete_number(int num);
	void clear();
	void print();
	~Rules() { delete number; }
};
//空格
class SudokuSolve;
class Space {
	int row, col, palace_index;//列号，行号，宫号。
	int solution_cout;//可行解个数
	int remain_count;
	int used_count;
	char solutions[9 * 9];//可行解集合
public:
	Space(int m_row = 0, int m_col = 0) {
		row = m_row;
		col = m_col;
		solution_cout = 0;
		used_count = remain_count = 0;
		palace_index = m_row / 3 * 3 + m_col / 3;
	}
	//判断当空格是否还有其它可行解;
	bool is_there_solutions();
	//返回下一个可行解, 没有则返回‘0’
	char next_solution();
	//行号
	int get_row() {
		return row;
	}
	//列号
	int get_col() {
		return col;
	}
	//宫号
	int get_palace() {
		return palace_index;
	}
	void print();
	friend class SudokuSolve;
};

//SudokuSolve.class使用者提供那个数独题目文件参数，调用solve()方法解出数独终局
class SudokuSolve {
	static const int N = 9;
	//数独限制条件
	Rules* rows;
	Rules* cols;
	Rules* palaces;
	//空格区域
	Space* spaces;
	int space_count;
	//当前阵列情况
	char array[N][N];
	//终局
	char* sudoku_store;
	//提取出一个数独谜题
	bool next_puzzle();
	//解决一个数独
	bool puzzle_solve(int k);
	//刷新行，列，宫
	void rules_clear();
	//判断数字num是否能填入
	bool try_to_add(int mum, int space_index);
	void print_array();
	//更新占用状态
	void refresh(int num, int space_index);
	//初始化空格区域
	void init_spaces();
public:
	SudokuSolve();
	char* solve();
};

#endif // !S_SUDOKU_H

