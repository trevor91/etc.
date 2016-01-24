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
	int studentNumber; //학번
	string mail; //메일
	int score; //학점
	int marker; //중간에 삭제된 자리를 표시( 0=삭제된적 없는자리, 1=삭제된 자리)
};