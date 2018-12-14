//������void createSudoku(int n, string fileName);����
#pragma once
#ifndef SUDOKU_H
#define SUDOKU_H

#include<cstring>
#include<string>
#include<cstdlib>

using namespace std;

class ArgCheck{
	int argc;
	char** argv;
	int checkResult;//�����û������ĺϷ���񣬱���û���Ҫ�����ֲ���
public:
	//һЩ��־����
	static const int INVALID = 0;//�������Ϸ�
	static const int FORC = 1;//���������վ�
	static const int FORS = 2;//�������
public:
	ArgCheck(int m_argc = 0, char** m_argv = NULL):checkResult(INVALID){
		argc = m_argc;
		argv = m_argv;
	}
	//�ṩcheckResualt
	int getResult() {
		return checkResult;
	}
	//�Բ����ĺϷ����Լ����������жϣ�����������checkResualt������
	int check();
};


class SudokuFactory {
	static const int N = 9;
	int need;//ʣ��������
	int index_store;
	char firstR[N];
	char model[N][N];//ģ��
	char* sudokuStore;//�����վ�
public:
	SudokuFactory(int m_need = 0 ) {
		need = m_need; 
		index_store = 0;
		sudokuStore = (char*)malloc(sizeof(char) * (18*N*need + need - 1));
		createFirstModel();//�Զ����ɵ�һ��ģ��
	}
	//  ���ʣ��������
	bool isEnough() {
		if (need > 0)return false;
		return true;
	}
	//���ɵ�һ��ģ��
	void createFirstModel();
	//����ģ��
	void refreshModel();
	//��ԭʼ���л����Ͻ��б任�����36������
	void newFromModel();
	//�����վ��ļ�
	char* createSudokuFile();
	string getsudokuStore() { return sudokuStore; }
	void store(char a[], char b[], char c[]);
	~SudokuFactory(){
		free(sudokuStore);
	}
};

#endif // !SUDOKU_H
