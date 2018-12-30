#pragma once
#ifndef S_SUDOKU_H
#define S_SUDOKU_H

#include <fstream>
#include <string>
//�С��С���
class Rules {
	static const int N = 9;
	bool* number;//������д�����number[i] = true,��ʾ(i + 1), i + 1 = (1, 2, ...,9)������
public :
	Rules(){
		number = new bool[N];
		for (int i = 0; i < N; i++)
			number[i] = false;
	}
	//�ж�����num�Ƿ��Ѿ�����
	bool is_added_number(char num);
	//������num����
	void add_number(char number);
	////������num�Ƴ�
	void delete_number(char num);
	void reset();
	void print();
	~Rules() { delete number; }
};

/********************************************************/
/********************************************************/
//�ո�Space.class
class SudokuSolve;
class Space {
	int row, col, palace_index;//�кţ��кţ����š�
	int solution_count;//���н����
	int used_count;//�Ѿ��ù��Ŀ�������
	char solutions[9];//���н⼯��
	bool used[9];
	char current_num;//��ǰ�����ֵ
public:
	Space(int m_row = 0, int m_col = 0) {
		row = m_row;
		col = m_col;
		solution_count = 0;
		used_count = 0;
		current_num = '0';
		palace_index = m_row / 3 * 3 + m_col / 3;
		reset_used();
	}
	//�жϵ��ո��Ƿ�������û���ù��Ŀ��н�;
	bool is_there_solutions();
	//������һ�����н�, û���򷵻ء�0��
	char next_solution();
	//�к�
	int get_row() {
		return row;
	}
	//�к�
	int get_col() {
		return col;
	}
	//����
	int get_palace() {
		return palace_index;
	}
	//���н����
	int get_solution_count() {
		return solution_count;
	}
	void print();
	void reset();
	//ȫ�����ã��ù��Ŀ��н����±�ΪΪû�ù�
	void reset_used() {
		for (int i = 0; i < 9; i++)
			used[i] = false;
	}
	void set_used(int index) {
		used[index] = true;
	}
	friend class SudokuSolve;
};

/********************************************************/
/********************************************************/
//SudokuSolve.classʹ�����ṩ�Ǹ�������Ŀ�ļ�����������solve()������������վ�
class SudokuSolve {
	static const int N = 9;
	//������������
	static Rules* rows;
	static Rules* cols;
	static Rules* palaces;
	//�ո�����
	static Space* spaces;
	int space_count;
	//��ǰ�������
	static char array[N][N];
	//�վ�
	char* sudoku_store;
	//��ȡ��һ����������
	bool get_puzzle();
	//���һ������
	bool puzzle_solve(int k);
	//ˢ���У��У���
	void rules_reset();
	//�ж�����num�Ƿ�������
	bool try_to_add(char mum, int space_index);
	void print_array();
	//����ռ��״̬
	void refresh_rules(char num, int space_index, bool delete_num);
	//���ݵ�ĳ���н�ڵ�ʱҪ�Ƚ���ռ�ø���,�����
	//���ڻ��ݵ��Ľڵ��Ѿ�����ĳ�����֣�Ҫ���Ƴ��������
	void clear_space(int space_index);
	//���ݾ����Ŀո��������:�ù��Ŀ��н����±�ΪΪû�ù�
	//ͬʱ��ҲҪclear_space
	void reset_space(int space_index) {
		spaces[space_index].reset_used();
		clear_space(space_index);
	}
	//��ʼ���ո�����
	void init_spaces();
	//��ʼ����̬��Ա
	static void init_static();
	//�����ǰ�ո�����У��У�����ռ�����
	void print_space_status(int space_index);
public:
	SudokuSolve();
	char* solve(char* filename);
};

#endif // !S_SUDOKU_H

