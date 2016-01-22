#include <iostream>
using namespace std;

class Node{
	friend class Tree;
	friend class BinaryNode;
public:
	Node()
	{
		data = 0;
		parent = NULL;
		child = NULL;
		nextSibling = NULL;
		preSibling = NULL;
	}
	~Node(){ }
private:
	int data;
	Node* parent;
	Node* child;
	Node* nextSibling;
	Node* preSibling;
};

class BinaryNode{
	friend class Tree;
public:
	BinaryNode()
	{
		data = 0;
		parent = NULL;
		leftChild = NULL;
		rightChild = NULL;
	}
	BinaryNode(Node* target)
	{
		data = target->data;
		if (target->parent == NULL)
		{
			parent = NULL;
		}
		if (target->child == NULL) //�ܵ� root or external
		{
			leftChild = NULL;
		}
		else //root�� �ڽ��� ����
		{
			Node* tmpChild = target->child; // �ڽ� ����
			BinaryNode* tmpBinaryNode = leftChild = new BinaryNode(tmpChild); //�ڽ��� leftChild�� �־��ְ� left�ڽ��� BinaryNode�� �ӽ�����
			while (tmpChild != NULL) // �ڽ��� ���������� while
			{
				tmpChild = tmpChild->nextSibling;//������带 �ӽ�����
				if (tmpChild == NULL)//������尡 ���ٸ�
				{
					tmpBinaryNode->rightChild = NULL;
					break;
				}
				tmpBinaryNode->rightChild = new BinaryNode(tmpChild);//���� ������ �ִٸ� nextSibling�� ���� ������ �ڽĿ� ����
				tmpBinaryNode->parent = this;//�ڽ��� �θ� ����
				tmpBinaryNode = tmpBinaryNode->rightChild;//rightChild����
			}
		}
	}
	~BinaryNode(){ }
private:
	int data;
	BinaryNode* parent;
	BinaryNode* leftChild;
	BinaryNode* rightChild;
};