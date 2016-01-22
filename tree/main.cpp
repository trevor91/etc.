#include "Tree.h"
#include <iostream>
using namespace std;
int main()
{
	Tree* a = new Tree;
	char input=NULL;
	int data=0, parent=0, sibling=0;
	int N=0;
	
	while (1)
	{
		cin >> input;
		switch (input)
		{
		case 'I':
		case 'i':
			cin >> data >> parent >> sibling;
			a->insert(data, parent, sibling);
			break;
		case 'P':
		case 'p':
			a->preorder(a->getRoot());
			cout << endl;
			break;
		case 'T':
		case 't':
			a->postorder(a->getRoot());
			cout << endl;
			break;
		case 'C':
		case 'c':
			cin >> N;
			a->setX(); a->setY();
			a->map(N, a->setBinaryTree());
			break;
		case 'Q':
		case 'q':
			return 0;
		}
	}
	return 0;
}