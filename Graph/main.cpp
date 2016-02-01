#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "graph.h"
using namespace std;

int main()
{
	graph* test = new graph;
	char input; //질의
	int studentNumber[2]; //학번
	int doroNumber; //도로번호
	string mail; //메일주소

	string file;
	cin >> file;

	ifstream fileInput; //파일 입력 선언
	fileInput.open(file); //query파일을 받는다
	int student, doro;
	fileInput >> student >> doro;
	for (int i = 0; i < student; ++i) //파일 입력으로 받은 학생 수 만큼 추가
	{
		fileInput >> studentNumber[0] >> mail;
		test->insertVertex(studentNumber[0], mail);
	}
	for (int i = 0; i < doro; ++i) //파일 입력으로 받은 도로 수 만큼 추가
	{
		fileInput >> doroNumber >> studentNumber[0] >> studentNumber[1];
		test->insertEdge(studentNumber[0], studentNumber[1], doroNumber);
	}
	fileInput.close();
	while (1)
	{
		cin >> input;
		switch (input)
		{
		case 'A': //학생추가
		case 'a':
		{
			cin >> studentNumber[0] >> mail;
			test->insertVertex(studentNumber[0], mail);
			test->printSizeOfVertex();
			break;
		}
		case 'P': //학생 정보 출력
		case 'p':
		{
			cin >> studentNumber[0];
			test->printStudent(studentNumber[0]);
			break;
		}
		case 'I': //도로추가
		case 'i':
		{
			cin >> doroNumber >> studentNumber[0] >> studentNumber[1];
			bool success = test->insertEdge(studentNumber[0], studentNumber[1], doroNumber);
			if(success == true) test->printSizeOfEdge();
			break;
		}
		case 'X': //학생 삭제
		case 'x':
		{
			cin >> studentNumber[0];
			test->eraseVertex(studentNumber[0]);
			break;
		}
		case 'Z': //도로 삭제
		case 'z':
		{
			cin >> doroNumber;
			test->eraseEdge(doroNumber);
			break;
		}
		case 'L': //연결된 도로 출력
		case 'l':
		{
			cin >> studentNumber[0];
			test->incidentEdges(studentNumber[0]);
			break;
		}
		case 'F': //도로정보 출력1
		case 'f':
		{
			cin >> doroNumber;
			test->endVertices(doroNumber);
			break;
		}
		case 'O': //도로정보 출력2
		case 'o':
		{
			cin >> studentNumber[0] >> doroNumber;
			test->opposite(studentNumber[0], doroNumber);
			break;
		}
		case 'K': //도로 존재여부 확인
		case 'k':
		{
			cin >> studentNumber[0] >> studentNumber[1];
			test->isAdjacentTo(studentNumber[0], studentNumber[1]);
			break;
		}
		case 'Q':
		case 'q':
		{
			delete test;
			return 0;
		}
		}
	}
}