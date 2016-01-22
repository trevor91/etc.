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
		if (target->child == NULL) //단독 root or external
		{
			leftChild = NULL;
		}
		else //root의 자식을 설정
		{
			Node* tmpChild = target->child; // 자식 저장
			BinaryNode* tmpBinaryNode = leftChild = new BinaryNode(tmpChild); //자식을 leftChild에 넣어주고 left자식을 BinaryNode로 임시저장
			while (tmpChild != NULL) // 자식이 없을때까지 while
			{
				tmpChild = tmpChild->nextSibling;//형제노드를 임시저장
				if (tmpChild == NULL)//형제노드가 없다면
				{
					tmpBinaryNode->rightChild = NULL;
					break;
				}
				tmpBinaryNode->rightChild = new BinaryNode(tmpChild);//형제 도느가 있다면 nextSibling의 값을 오른쪽 자식에 저장
				tmpBinaryNode->parent = this;//자식의 부모를 설정
				tmpBinaryNode = tmpBinaryNode->rightChild;//rightChild설정
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