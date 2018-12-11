#include<iostream>
#include<cstring>
#include<string>
using namespace std;

const int number = 1;//学号后两位mod9+1

int main(int argc, char* argv[]) {
	//申明
	bool isPurenumber(char* s);

	cout << "First code line" << endl;
	//输出传入参数
	cout << "argc = " << argc << endl;
	//cout << "agv[2] = " << argv[2] << endl;
	//验证传入参数的合法性
	if (argc < 2) {
		cout << "参数数量过少" << endl;
		return 0;
	}
	if (!isPurenumber(argv[2])) {
		cout << "参数不合法" << endl;
		return 0;
	}
}

//判断输入是否问纯数字
bool isPurenumber(char* s) {
	int n = strlen(s);
	for (int i = 0; i < n; i++)
		if (s[i] > '9' || s[i] < '0')
			return false;
	return true;
}