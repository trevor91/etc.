#include "Tree.h"
#include <iostream>
using namespace std;

Tree::Tree()
{
	root = NULL;
	size = 0;
	x = 0;
	y = 0;
}
Tree::~Tree() {}
Node* Tree::getRoot(){ return root; }
int Tree::getSize() { return size; }
void Tree::setX() { x = 0; }
void Tree::setY() { y = 0; }
bool Tree::empty()
{
	if (size == 0)
		return true;	//����ִٸ� true
}
bool Tree::isRoot(Node* a)
{
	if (a == root)
		return true;	//root��� true
}
bool Tree::isExternal(Node* a)
{
	if (a->child == NULL)
		return true;	//external�̶�� true
	return false;
}
void Tree::setParent(int data, Node* startingPoint, Node* endPoint) //data�� ���� ���� ���� startingPoint�� ã�� endPoint�� �����Ѵ�
{
	if (startingPoint->data == data)
		endPoint->parent = startingPoint;		//data���� ������ parent���� startingPoint�� �����Ѵ�
	else if (!isExternal(startingPoint)) //internal Node�̸���
	{
		setParent(data, startingPoint->child, endPoint);	//����Լ��� startingPoint�� �ڽ��� Ž���Ѵ�
		if (startingPoint->nextSibling != NULL)
			setParent(data, startingPoint->nextSibling, endPoint);//����Լ��� ������带 Ž���Ѵ�
	}
	else
	{
		if (startingPoint->nextSibling != NULL)
			setParent(data, startingPoint->nextSibling, endPoint);
	}
}

void Tree::insert(int data, int parentData, int siblingNumber) //siblingNumber�� ���° �ڽ�����
{
	size++;
	Node* add = new Node;
	if (parentData == -1 && siblingNumber == -1)
	{
		add->data = data;
		root = add;
	}
	else
	{
		add->data = data;					//setData
		setParent(parentData,root, add);	//setParent

		//setSibling and child
		if (siblingNumber == 1)							//���� �Է³�尡 ù°�̰�
		{
			if (add->parent->child != NULL) //������ ��尡 �־��ٸ�
			{
				add->parent->child->preSibling = add;
				add->nextSibling = add->parent->child;
				add->parent->child = add;
			}
			else //���ο� �ڽ��̶��
				add->parent->child = add;
		}
		else
		{
			for (Node* i = add->parent->child; 1<siblingNumber; i=i->nextSibling)
			{
				if (siblingNumber==2 )
				{
					add->preSibling = i;						//add�տ� i�� �ּҰ���
					add->nextSibling = i->nextSibling;		//add�ڿ� i�� next����
					if (i->nextSibling != NULL) { i->nextSibling->preSibling = add; }	//add ���� ���pre ���� add��
					i->nextSibling = add;					//i �ڿ� add����.
				}
				--siblingNumber;
			}
		}
	}
}

void Tree::preorder(Node* startingPoint)		//startingPoint�������� ������Ѵ�. default=root
{
	if (!isExternal(startingPoint))		//���� internal�̶��
	{
		cout << startingPoint->data << " ";		//���� visit���ְ�
		preorder(startingPoint->child);			//�ڽĳ�带 visit���ְ�
		if (startingPoint->nextSibling != NULL)		//�ٷ� �� �Լ��� ������ �� ������ �ִ��� Ȯ���ؾ��Ѵ�
			preorder(startingPoint->nextSibling);	//������ ������ ������ visit
	}
	else//external�̶��
	{
		cout << startingPoint->data << " ";		//visit
		if (startingPoint->nextSibling != NULL)	//������ �ִٸ�
			preorder(startingPoint->nextSibling);//visit
	}
}
void Tree::postorder(Node* startingPoint)	//startingPoint�������� Ž���� �����Ѵ�. ���� ����Ʈ�� root
{
	if (!isExternal(startingPoint))//internal Node�����
	{
		postorder(startingPoint->child); //��� �Լ��� �ڽ���������
		cout << startingPoint->data << " ";//visit
		if (startingPoint->nextSibling != NULL)
			postorder(startingPoint->nextSibling);
	}
	else//external�̶��
	{
		cout << startingPoint->data << " ";//�ڽ��� �����Ƿ�visit
		if (startingPoint->nextSibling != NULL)
			postorder(startingPoint->nextSibling);
	}
}

BinaryNode* Tree::setBinaryTree()
{
	BinaryNode* find = new BinaryNode(root);
	return find;
}

void Tree::map(int data, BinaryNode* find)
{
	if (find->leftChild != NULL)
	{
		++y;
		map(data, find->leftChild);
		--y;
		if (find->rightChild != NULL)
		{
			++x;
			if (find->data == data)
			{
				cout << x << " " << y << endl;
				return;
			}
			++y;
			map(data, find->rightChild);
			--y;
		}
		else //find->rightChild==NULL
		{
			++x;
			if (find->data == data)
			{
				cout << x << " " << y << endl;
			}
		}
	}
	else //find->leftChild==NULL
	{
		++x;
		if (find->data == data)
		{
			cout << x << " " << y << endl;
			return;
		}
		if (find->rightChild != NULL)
		{
			++y;
			map(data, find->rightChild);
			--y;
		}
	}
}