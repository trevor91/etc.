#pragma once
#include "Student.h"
using namespace std;

class Hash{
private:
	int tableSize; //���̺� ũ��
	int countStudent; //ȸ����
	int primeNumber; //n���� ���� �Ҽ�
	int countProbe; //probe Ƚ�� ī��Ʈ
	int key1; //ù��° Ű��
	int key2; //�ι�° Ű��
	Student* table; //�ڷḦ ������ ���̺�
	double loadfactor; //������
public:
	Hash();
	Hash(int, int, int);
	//********Main Function*************
	int HashingOne(int); //1�� �ؽ��Լ�
	int HashingTwo(int); //2�� �ؽ��Լ�
	void insertStudent(int, int, string); //ó�� hashTable�� �����ϱ� ���� �Է�
	void insertStudent(int,string); //���Ǹ� ���� �л� �Է�
	void insertSubject(int,int); //���� ���� �߰�
	void changeMail(int,string); //�̸��� ����
	void printStudnet(int); //�л� ���� ���
	//**********************************
	double loadFactor(); //������ �����Լ�
};