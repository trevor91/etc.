/*	2015.11 �ڷᱸ�� 2�� ������Ʈ
	�л����� ���� ���α׷� ����
	��ǻ���������а� 12121537 ������*/
#include "Hash.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	int n; //�迭 ũ��
	int m; //�л� ��
	int q; //n���� ���� �Ҽ�
	string name; //�Է¹��� ���� �̸�
	cin >> name;
	ifstream dataFile(name); //���� �б�
	dataFile >> n >> m >> q;
	Hash* temp = new Hash(n, m, q);
	
	int s=0, t=0; //s=�й�, t=����
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