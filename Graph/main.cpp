#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "graph.h"
using namespace std;

int main()
{
	graph* test = new graph;
	char input; //����
	int studentNumber[2]; //�й�
	int doroNumber; //���ι�ȣ
	string mail; //�����ּ�

	string file;
	cin >> file;

	ifstream fileInput; //���� �Է� ����
	fileInput.open(file); //query������ �޴´�
	int student, doro;
	fileInput >> student >> doro;
	for (int i = 0; i < student; ++i) //���� �Է����� ���� �л� �� ��ŭ �߰�
	{
		fileInput >> studentNumber[0] >> mail;
		test->insertVertex(studentNumber[0], mail);
	}
	for (int i = 0; i < doro; ++i) //���� �Է����� ���� ���� �� ��ŭ �߰�
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
		case 'A': //�л��߰�
		case 'a':
		{
			cin >> studentNumber[0] >> mail;
			test->insertVertex(studentNumber[0], mail);
			test->printSizeOfVertex();
			break;
		}
		case 'P': //�л� ���� ���
		case 'p':
		{
			cin >> studentNumber[0];
			test->printStudent(studentNumber[0]);
			break;
		}
		case 'I': //�����߰�
		case 'i':
		{
			cin >> doroNumber >> studentNumber[0] >> studentNumber[1];
			bool success = test->insertEdge(studentNumber[0], studentNumber[1], doroNumber);
			if(success == true) test->printSizeOfEdge();
			break;
		}
		case 'X': //�л� ����
		case 'x':
		{
			cin >> studentNumber[0];
			test->eraseVertex(studentNumber[0]);
			break;
		}
		case 'Z': //���� ����
		case 'z':
		{
			cin >> doroNumber;
			test->eraseEdge(doroNumber);
			break;
		}
		case 'L': //����� ���� ���
		case 'l':
		{
			cin >> studentNumber[0];
			test->incidentEdges(studentNumber[0]);
			break;
		}
		case 'F': //�������� ���1
		case 'f':
		{
			cin >> doroNumber;
			test->endVertices(doroNumber);
			break;
		}
		case 'O': //�������� ���2
		case 'o':
		{
			cin >> studentNumber[0] >> doroNumber;
			test->opposite(studentNumber[0], doroNumber);
			break;
		}
		case 'K': //���� ���翩�� Ȯ��
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