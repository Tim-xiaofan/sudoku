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
class Space {
	int row, col, palace_index;//�кţ��кţ����š�
	int solution_cout;//���н����
	int remain_count;
	char* solutions;//���н⼯��
public:
	Space(int m_row = 0, int m_col = 0) {
		row = m_row;
		col = m_col;
		solution_cout = 0;
		solutions = 0;
		remain_count = 0;
		palace_index = m_row / 3 * 3 + m_col / 3;
	}
	//�жϵ��ո��Ƿ����������н�;
	bool is_there_solutions();
	//������һ�����н�, û���򷵻ء�0��
	char next_solution();
	void print();
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
	void puzzle_solve();
	//ˢ���У��У���
	void rules_clear();
public:
	SudokuSolve();
	char* solve();
};

#endif // !S_SUDOKU_H

