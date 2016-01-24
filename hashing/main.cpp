/*	2015.11 자료구조 2차 프로젝트
	학생정보 관리 프로그램 설계
	컴퓨터정보공학과 12121537 이제형*/
#include "Hash.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	int n; //배열 크기
	int m; //학생 수
	int q; //n보다 작은 소수
	string name; //입력받을 파일 이름
	cin >> name;
	ifstream dataFile(name); //파일 읽기
	dataFile >> n >> m >> q;
	Hash* temp = new Hash(n, m, q);
	
	int s=0, t=0; //s=학번, t=학점
	string e=""; //e=mail
	for (int i = 0; i < m; ++i)
	{
		dataFile >> s >> t >> e;
		temp->insertStudent(s, t, e);
	}
	//*********************************//
	while (1)
	{
		char input;
		cin >> input;
		switch (input)
		{
		case 'A':
		case 'a':
			cin >> s >> e;
			temp->insertStudent(s, e);
			break;
		case 'U':
		case 'u':
			cin >> s >> t;
			temp->insertSubject(s, t);
			break;
		case 'M':
		case 'm':
			cin >> s >> e;
			temp->changeMail(s, e);
			break;
		case 'P':
		case 'p':
			cin >> s;
			temp->printStudnet(s);
			break;
		case 'Q':
		case 'q':
			return 0;
		}
	}
	return 0;
}