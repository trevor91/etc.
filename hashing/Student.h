#pragma once
#include <string>
using namespace std;

class Student{
	friend class Hash;
public:
	Student()
	{
		studentNumber = 0;
		mail = "";
		score = 0;
		marker = 0;
	}

private:
	int studentNumber; //�й�
	string mail; //����
	int score; //����
	int marker; //�߰��� ������ �ڸ��� ǥ��( 0=�������� �����ڸ�, 1=������ �ڸ�)
};