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
	bool is_added_number(int num);
	//������num����
	void add_number(int number);
	////������num�Ƴ�
	void delete_number(int num);
	void clear();
	void print();
	~Rules() { delete number; }
};
//�ո�
class SudokuSolve;
class Space {
	int row, col, palace_index;//�кţ��кţ����š�
	int solution_cout;//���н����
	int remain_count;
	int used_count;
	char solutions[9 * 9];//���н⼯��
public:
	Space(int m_row = 0, int m_col = 0) {
		row = m_row;
		col = m_col;
		solution_cout = 0;
		used_count = remain_count = 0;
		palace_index = m_row / 3 * 3 + m_col / 3;
	}
	//�жϵ��ո��Ƿ����������н�;
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
	void print();
	friend class SudokuSolve;
};

//SudokuSolve.classʹ�����ṩ�Ǹ�������Ŀ�ļ�����������solve()������������վ�
class SudokuSolve {
	static const int N = 9;
	//������������
	Rules* rows;
	Rules* cols;
	Rules* palaces;
	//�ո�����
	Space* spaces;
	int space_count;
	//��ǰ�������
	char array[N][N];
	//�վ�
	char* sudoku_store;
	//��ȡ��һ����������
	bool next_puzzle();
	//���һ������
	bool puzzle_solve(int k);
	//ˢ���У��У���
	void rules_clear();
	//�ж�����num�Ƿ�������
	bool try_to_add(int mum, int space_index);
	void print_array();
	//����ռ��״̬
	void refresh(int num, int space_index);
	//��ʼ���ո�����
	void init_spaces();
public:
	SudokuSolve();
	char* solve();
};

#endif // !S_SUDOKU_H

