#include "Hash.h"
#include <iostream>
using namespace std;
Hash::Hash(){}
Hash::Hash(int n, int m, int q)
{
	countProbe = 0;
	key1 = 0;
	key2 = 0;

	tableSize = n; //���̺��� ũ��
	countStudent = m; //����� ȸ���� ��
	primeNumber = q; //n���� ���� �Ҽ�
	table = new Student[tableSize]; //�Է¹���  n��ŭ ���̺��� �����
	loadfactor = (double)countStudent / (double)tableSize;
}
int Hash::HashingOne(int number){return number%tableSize;} //1�� �ؽ��Լ�
int Hash::HashingTwo(int number){return primeNumber - (number%primeNumber);} //2�� �ؽ��Լ�
void Hash::insertStudent(int s, int t, string e) //s=�й�, t=����, e=����  ���� �Է��� ���� table�� �����ϴ� �Լ�
{
	key1 = HashingOne(s);
	key2 = HashingTwo(s);
	if (table[key1].studentNumber == 0) //1�� �ؽ��Լ��� ���� ��������� data���� �־��ش�
	{
		table[key1].studentNumber = s;
		table[key1].score = t;
		table[key1].mail = e;
	}
	else //1�� �ؽ��Լ��� ���� �ִٸ�
	{
		for (int i = (key1 + key2)%tableSize; i != key1; i = (i+key2)%tableSize) //2���ؽ��Լ��� 1������ �����ָ鼭 ��ȸ�Ѵ�.
		{
			if (table[i].studentNumber == 0) //��ȸ �߿� ����ִ°��� ã���� data���� �־��ش�
			{
				table[i].studentNumber = s;
				table[i].score = t;
				table[i].mail = e;
				break;
			}
		}
	}
}
void Hash::insertStudent(int s, string e) //PPT�� ���� s=�й�, e=mail  //���Ǹ� ���ؼ� �Է��ϴ� �Լ�
{
	key1 = HashingOne(s); //ù��° �ؽ��� �Է�
	countProbe = 0; //�� �� ���κ����� ���������Ƿ� �ʱ�ȭ
	++countProbe; //probe Ƚ�� ������Ű��
	if (table[key1].mail == "") //Ű�� �ڸ��� ���� ������ �Է� 
	//������ �й��� �ֳ� ���ķ� data�� Ȯ���ߴµ� ���⼱ ���ϰ����� Ȯ��.
	//���� �����̶�� �й��� �ְ� ������ ���� �� ������, �� �������� �׷� ���� �����Ƿ� �������� ������� �����غ������߽��ϴ�.
	{
		++countStudent; //�л��� ����
		table[key1].studentNumber = s; //�й� �Է�
		table[key1].mail = e; //���� �Է�
	}
	else //1�� �ؽ����� �ڸ��� ������
	{
		key2 = HashingTwo(s); //�ι�° �ؽ��� �Է�
		//key1,2�� �̿��ؼ� table�� ��ȸ�ϸ鼭 ����� Ȯ���Ѵ�
		for (int i = (key1 + key2)%tableSize; i!=key1 ; i = (i + key2) % tableSize)
		{
			++countProbe; //�� ������ probe Ƚ�� ����
			if (table[i].mail == "") //����� ã����
			{
				++countStudent; //�л��� +1
				table[i].studentNumber = s; //�й� �Է�
				table[i].mail = e; //�̸��� �Է�
				//table[i].marker = 0; //�ٽ� ���� �Է� �޾����� marker�� 0����
				break;
			}
		}
	}
	cout.precision(2); //�Ҽ���3°���� �ݿø� -> �Ҽ��� 2�ڸ����� ǥ��
	cout << countProbe << " " << fixed << loadFactor() << endl;
}
void Hash::insertSubject(int s, int c) //PPT�� ���� s�� �й� c�� ���������� ����
{
	key1 = HashingOne(s); //ù��° �ؽ��� �Է�
	countProbe = 0;
	++countProbe;
	if (table[key1].studentNumber == s) //Ű���� �ε��� �й��� ������û �л� �й��� ������
	{
		if ((table[key1].score + c) > 24){ cout << countProbe << " Exceeded" << endl; return; } //������ �ʰ��̸�
		else //���� �ʰ��� �ƴϸ� ������ �÷��ش�
		{
			table[key1].score += c;
			cout << countProbe << " " << table[key1].score << endl;
		}
		return;
	}
	else if (table[key1].studentNumber == 0) //1���� �ؽ��� data�� ������ (�л��� ã�� ���ϸ�)
	{
		cout << countProbe << " Not found" << endl; //ã�� �л��� ������
		return;
	}
	else
	{
		key2 = HashingTwo(s); //�ι�° �ؽ��� �Է�
		//key1,2�� �̿��ؼ� table�� ��ȸ�ϸ鼭 ����� Ȯ���Ѵ�
		for (int i = (key1 + key2)%tableSize; key1 != i ; i = ((i + key2) % tableSize))
		{
			++countProbe;
			if (table[i].studentNumber == s) //�л��� ã����
			{
				if (table[i].score + c > 24){ cout << countProbe << " Exceeded" << endl; return; } //���� Ȯ�� �� �ʰ��ϸ�
				else //�ʰ����� ������
				{
					table[i].score += c;
					cout << countProbe << " " << table[i].score << endl;
				}
				return;
			}
			else if (table[i].studentNumber == 0) //ã�� ���� ���ٸ�
			{
				cout << countProbe << " Not found" << endl; //ã�� �л��� ������
				return;
			}
		}
	}
}
void Hash::changeMail(int s, string e) //PPT�� ���� s�� �й� e�� ����
{
	key1 = HashingOne(s);
	key2 = HashingTwo(s);
	int i = key1; //i�� Ű������ �ʱ�ȭ
	countProbe = 0;
	do //������ for���� �Ἥ ��ȸ�� �ߴµ�, �������� ������� ��ȸ�غ��°͵� ������ ���Ƽ� do while�� ��ȸ�մϴ�.
	{
		++countProbe;
		if (table[i].studentNumber == s)
		{
			table[i].mail = e;
			cout << countProbe << endl;
			return;
		}
		else if (table[i].studentNumber == 0)
		{
			cout << countProbe << " Not found" << endl; //ã�� �л��� ������
			return;
		}
		i = (i+key2)%tableSize;
	} while (i != key1);
}
void Hash::printStudnet(int s) //s�� �й�
{
	key1 = HashingOne(s);
	key2 = HashingTwo(s);
	int i = key1;
	countProbe = 0;
	do
	{
		++countProbe;
		if (table[i].studentNumber == s)
		{
			cout << countProbe << " " << table[i].studentNumber << " " << table[i].score << " " << table[i].mail << endl;
			countProbe = 0;
			return;
		}
		else if (table[i].studentNumber == 0)
		{
			cout << countProbe << " Not found" << endl; //ã�� �л��� ������
			return;
		}
		i = (i+key2)%tableSize;
 	} while (i != key1);
}
double Hash::loadFactor()
{
	loadfactor = (double)countStudent/(double)tableSize;
	return loadfactor;
}