#include<iostream>
#include<cstring>
#include<string>
using namespace std;

const int number = 1;//ѧ�ź���λmod9+1

int main(int argc, char* argv[]) {
	//����
	bool isPurenumber(char* s);

	cout << "First code line" << endl;
	//����������
	cout << "argc = " << argc << endl;
	//cout << "agv[2] = " << argv[2] << endl;
	//��֤��������ĺϷ���
	if (argc < 2) {
		cout << "������������" << endl;
		return 0;
	}
	if (!isPurenumber(argv[2])) {
		cout << "�������Ϸ�" << endl;
		return 0;
	}
}

//�ж������Ƿ��ʴ�����
bool isPurenumber(char* s) {
	int n = strlen(s);
	for (int i = 0; i < n; i++)
		if (s[i] > '9' || s[i] < '0')
			return false;
	return true;
}