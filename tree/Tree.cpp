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
		return true;	//비어있다면 true
}
bool Tree::isRoot(Node* a)
{
	if (a == root)
		return true;	//root라면 true
}
bool Tree::isExternal(Node* a)
{
	if (a->child == NULL)
		return true;	//external이라면 true
	return false;
}
void Tree::setParent(int data, Node* startingPoint, Node* endPoint) //data와 같은 값을 가진 startingPoint를 찾고 endPoint에 저장한다
{
	if (startingPoint->data == data)
		endPoint->parent = startingPoint;		//data값이 같으면 parent값에 startingPoint를 저장한다
	else if (!isExternal(startingPoint)) //internal Node이면은
	{
		setParent(data, startingPoint->child, endPoint);	//재귀함수로 startingPoint의 자식을 탐색한다
		if (startingPoint->nextSibling != NULL)
			setParent(data, startingPoint->nextSibling, endPoint);//재귀함수로 형제노드를 탐색한다
	}
	else
	{
		if (startingPoint->nextSibling != NULL)
			setParent(data, startingPoint->nextSibling, endPoint);
	}
}

void Tree::insert(int data, int parentData, int siblingNumber) //siblingNumber는 몇번째 자식인지
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
		if (siblingNumber == 1)							//현재 입력노드가 첫째이고
		{
			if (add->parent->child != NULL) //기존에 노드가 있었다면
			{
				add->parent->child->preSibling = add;
				add->nextSibling = add->parent->child;
				add->parent->child = add;
			}
			else //새로운 자식이라면
				add->parent->child = add;
		}
		else
		{
			for (Node* i = add->parent->child; 1<siblingNumber; i=i->nextSibling)
			{
				if (siblingNumber==2 )
				{
					add->preSibling = i;						//add앞에 i의 주소값을
					add->nextSibling = i->nextSibling;		//add뒤에 i의 next값을
					if (i->nextSibling != NULL) { i->nextSibling->preSibling = add; }	//add 다음 노드pre 값을 add로
					i->nextSibling = add;					//i 뒤에 add값을.
				}
				--siblingNumber;
			}
		}
	}
}

void Tree::preorder(Node* startingPoint)		//startingPoint에서부터 출력을한다. default=root
{
	if (!isExternal(startingPoint))		//만약 internal이라면
	{
		cout << startingPoint->data << " ";		//먼저 visit해주고
		preorder(startingPoint->child);			//자식노드를 visit해주고
		if (startingPoint->nextSibling != NULL)		//바로 위 함수가 끝나면 또 형제가 있는지 확인해야한다
			preorder(startingPoint->nextSibling);	//형제가 있으면 형제도 visit
	}
	else//external이라면
	{
		cout << startingPoint->data << " ";		//visit
		if (startingPoint->nextSibling != NULL)	//형제가 있다면
			preorder(startingPoint->nextSibling);//visit
	}
}
void Tree::postorder(Node* startingPoint)	//startingPoint에서부터 탐색을 시작한다. 역시 디폴트는 root
{
	if (!isExternal(startingPoint))//internal Node라면은
	{
		postorder(startingPoint->child); //재귀 함수로 자식을보내고
		cout << startingPoint->data << " ";//visit
		if (startingPoint->nextSibling != NULL)
			postorder(startingPoint->nextSibling);
	}
	else//external이라면
	{
		cout << startingPoint->data << " ";//자식이 없으므로visit
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