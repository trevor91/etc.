#include "Node.h"
#include <iostream>
using namespace std;

class Tree{
public:
	Tree();
	~Tree();
	Node* getRoot();
	int  getSize();
	void setX();
	void setY();
	bool empty();
	bool isRoot(Node*);
	bool isExternal(Node*);

	void setParent(int data, Node* startPoint, Node* endPoint);
	void insert(int data, int parent, int siblingnumber);
	
	void preorder(Node* startingPoint);
	void postorder(Node* startingPoint);
	BinaryNode* setBinaryTree();	//target Tree¸¦ Binary Tree·Î
	void map(int data, BinaryNode* Node);
	
private:
	Node* root=NULL;
	//BinaryNode* binaryRoot=NULL;
	int size=0;
	int x = 0;
	int y = 0;
};