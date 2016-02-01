#include "graph.h"
#pragma once
#include <iostream>
using namespace std;

void graph::endVertices(int doroNumber) //edge�� ����� vertex�� ã���ִ� �Լ�
{
	edge* e = findEdge(doroNumber);
	if (e == NULL) { cout << "Not found" << endl; return; } //���� ��ȯ���� NULL�̶�� return

	if (e->a->studentNumber > e->b->studentNumber) //���� �� ���� ����ϱ� ���ؼ� ��
		cout << e->b->studentNumber << " " << e->a->studentNumber << endl;
	else
		cout << e->a->studentNumber << " " << e->b->studentNumber << endl;
}
void graph::opposite(int studentNumber,int doroNumber) //edge�� ����� v���vertex���� �ٸ� vertex�� ã���ִ� �Լ�
{
	vertex* v = findVertex(studentNumber);
	edge* e = findEdge(doroNumber);
	if ((e == NULL) || (v == NULL)) { cout << "Not available" << endl; return; } //��ȯ���� NULL�̶�� return
	if (e->a == v){ cout << e->b->studentNumber << endl; } //�ݴ��� ���� ����Ѵ�
	else if(e->b == v){ cout << e->a->studentNumber << endl; }
	else cout << "Not available" << endl;
}
int graph::opposite(edge* e,vertex* v) //edge�� ����� v���vertex���� �ٸ� vertex�� ã���ִ� �Լ�
{
	if (e->a == v){ return e->b->studentNumber; }
	else{ return e->a->studentNumber; }
}
bool graph::isAdjacentTo(int studentNumber1, int studentNumber2) //�� ���� ���̿� ������ �ٷ� ����Ǿ� �ִ��� �����ĸ� ���
{
	vertex* v = findVertex(studentNumber1); //�� ������ ���� ã��
	vertex* w = findVertex(studentNumber2);
	if ((v == NULL) || (w == NULL) || (v->degree ==NULL) || (w->degree ==NULL)) //���� �ּҰ��� �ϳ� �̻��� ���� ���̶��
	{
		cout << "Not found" << endl; //NULL �̹Ƿ� return
		return 0;
	}
	if (v->sizeOfDegree > w->sizeOfDegree) //w�� ������ ���� �� ���ٸ�
	{
		edgeList* i = w->degree; //w�� �������� ã�´�
		do
		{
			if (opposite(i->myEdge, w) == v->studentNumber) //�ݴ��� ������ �й��� v�� �й��� ���ٸ�
			{
				cout << i->myEdge->doroNumber << endl; //���ι�ȣ�� ����Ѵ�
				return 0;
			}
			i = i->next;
		} while (i!=NULL);
	}
	else //v�� ������ �� ���ų� ���Ҵٸ�
	{
		edgeList* i = v->degree; //v�� �������� ã�´�
		do
		{
			if (opposite(i->myEdge, v) == w->studentNumber) //�ݴ��� ������ �й��� w�� �й��� ���ٸ�
			{
				cout << i->myEdge->doroNumber << endl; // ���κ�ȣ�� ����Ѵ�
				return 0;
			}
			i = i->next;
		} while (i != NULL);
	}
	cout << "Not found" << endl;
	return 0;
}
void graph::printStudent(int studentNumber)
{
	vertex* target = findVertex(studentNumber); //�л��� ã��
	if (target == NULL) //�л��� ���ٸ� Notfound
	{
		cout << "Not found" << endl;
	}
	else if (target != NULL) //�л��� �ִٸ�
		cout << target->mail << " " << target->sizeOfDegree << endl;
}
void graph::insertVertex(int studentNumber, string mail) //������ ����
{
	vertex* fresh = new vertex; //vertex�� ���� �����
	vertexList* freshList = new vertexList; //vertexList�� ���� 
	++sizeOfVertex; // size���� ��Ű��
	fresh->studentNumber = studentNumber; //�й� �ʱ�ȭ
	fresh->mail = mail; //���� �ʱ�ȭ
	fresh->degree = NULL; //������ ����
	fresh->sizeOfDegree = 0; //�׷��Ƿ�size= 0
	//vertex�� vertexList�� ���� ����
	fresh->myvertexList = freshList;
	freshList->myvertex = fresh;
	//freshList �� ����
	if (vertexHeader == NULL) { vertexHeader = freshList; } //ó�� �Է¹��� vertex���
	else //������ vertex�� �־��ٸ�
	{
		freshList->next = vertexHeader; //����Ʈ�� �������ش�
		freshList->pre = NULL;
		vertexHeader->pre = freshList;
		vertexHeader = freshList;
	}
}
bool graph::insertEdge(int studentV, int studentW, int doronumber) //������ ����
{
	edge* fresh = new edge; //�ż��� ������ �����
	edgeList* freshList = new edgeList; //�ż��� ���� ����Ʈ���� �����
	vertex* v = findVertex(studentV); //�й��� �ش��ϴ� vertex�� ã��
	vertex* w = findVertex(studentW);
	if ((v == NULL) || (w == NULL)) //���� ���� ���̶����
	{
		cout << sizeOfEdge << " Not found" << endl;
		return false;
	}
	fresh->a = v;//���� ����
	v->sizeOfDegree++;
	fresh->b = w;//���� ����
	w->sizeOfDegree++;
	fresh->doroNumber = doronumber; //���ι�ȣ �Է�
	//edge, edgeList ���� ����
	fresh->myEdgeList = freshList;
	freshList->myEdge = fresh;

	if (edgeHeader == NULL)	{ edgeHeader = freshList; } //ó�� �Է¹����Ÿ�
	else //������ header�� �־��ٸ� ����Ʈ�� �������ش�
	{
		freshList->next = edgeHeader;
		freshList->pre = NULL;
		freshList->next->pre = freshList;
		edgeHeader = freshList;
	}

	//degreeList ����
	edgeList* vDegree = new edgeList; //vertex�� edge�� ��������ִ� edgeList�� �����
	edgeList* wDegree = new edgeList;
	vDegree->next = v->degree; //degree List���� header�κп� �����Ѵ�
	wDegree->next = w->degree;
	vDegree->pre = NULL; //header�� �Է������� pre�� NULL
	wDegree->pre = NULL;
	if (v->degree == NULL) { v->degree = vDegree; } //���� header���� ���� ��ü�� ���Ե� ��ü�� �ּҸ� pre�� �����Ѵ�
	else 
	{ 
		v->degree->pre = vDegree;
		v->degree = vDegree;
	}
	if (w->degree == NULL) { w->degree = wDegree; }
	else 
	{
		w->degree->pre = wDegree; 
		w->degree = wDegree;
	}
	fresh->degreeOfA = vDegree; //edge�� degreeList����
	fresh->degreeOfB = wDegree;
	fresh->degreeOfA->myEdge = fresh;
	fresh->degreeOfB->myEdge = fresh;
	++sizeOfEdge;//size ���� ��Ű��
	return true;
}
void graph::eraseVertex(int studentNumber) //������ ����
{
	// ������ ���� ����� vertex�� �����
	vertex* stale = findVertex(studentNumber); //�ش� vertex�� ã�´�
	if (stale == NULL) //vertex�� ���ٸ�
	{
		cout << sizeOfVertex << " "<< sizeOfEdge << " Not found" << endl;
		return;
	}
	for (edgeList* i = stale->degree; i != NULL; i=stale->degree) //������ ���� �����Ѵ�
	{
		if(i->myEdge != NULL) eraseEdge(i->myEdge); //eraseEdge�� ���ư��鼭 ������ �����Ѵ�
	}
	eraseVertexList(stale->myvertexList);//vertexList �����
	delete stale; //������ vertex�� �����
	cout << --sizeOfVertex << " " << sizeOfEdge << endl;
	return;
}
void graph::eraseVertexList(vertexList* stale)
{
	//����Ʈ ����
	if (stale->pre != NULL) //�տ� �ּҰ��� ���� �ƴϰ�
	{
		if (stale->next != NULL) //���� �ּҰ��� ���� �ƴϸ�
		{
			stale->next->pre = stale->pre;
			stale->pre->next = stale->next;
		}
		else //���� �ּҰ��� ���̶��
		{
			stale->pre->next = NULL;
		}
	}
	else //���� �� ������ degree(header)���ٸ�
	{
		if (stale->next != NULL) //���� �ּҰ��� ���� �ƴϸ�
		{
			stale->next->pre = NULL;
			vertexHeader = stale->next;
		}
		else //���� ���� ������(�ϳ� ���� ��尡 �����Ǹ�
		{
			sizeOfEdge = 0;
			vertexHeader = NULL;
		}
	}
	delete stale;
}
void graph::eraseEdge(edge* stale) //������ ���� , egde�� �ּҸ� �˶�
{
	//edge���� ����
	eraseEdgeList(stale->myEdgeList); //myEdgeList ����
	eraseDegreeA(stale); //degreeA�� �����Ѵ�
	eraseDegreeB(stale); //degreeB�� �����Ѵ�
	delete stale;
	--sizeOfEdge;
}
void graph::eraseEdge(int doroNumber) //������ ����, edge�� �ּҸ� �𸦶�
{
	edge* stale = findEdge(doroNumber); //�ش� ������ ã�´�
	if (stale == NULL) //ã�� ���� ���ٸ�
	{
		cout << sizeOfEdge << " Not found" << endl;
		return;
	}
	//edge���� ����
	eraseEdgeList(stale->myEdgeList); //myEdgeList ����
	eraseDegreeA(stale); //degreeA�� �����Ѵ�
	eraseDegreeB(stale); //degreeB�� �����Ѵ�
	--sizeOfEdge;
	delete stale;
	cout << sizeOfEdge << endl;
}
void graph::eraseEdgeList(edgeList* stale)
{
	if (stale->pre != NULL) //�տ� �ּҰ��� ���� �ƴϰ�
	{
		if (stale->next != NULL) //���� �ּҰ��� ���� �ƴϸ�
		{
			stale->next->pre = stale->pre;
			stale->pre->next = stale->next;
		}
		else //���� �ּҰ��� ���̶��
		{
			stale->pre->next = NULL;
		}
	}
	else //���� �� ������ degree(header)���ٸ�
	{
		if (stale->next != NULL) //���� �ּҰ��� ���� �ƴϸ�
		{
			stale->next->pre = NULL;
			edgeHeader = stale->next;
		}
		else //���� ���� ������(�ϳ� ���� ��尡 �����Ǹ�
		{
			sizeOfEdge = 0;
			edgeHeader = NULL;
		}
	}
	delete stale;
}
void graph::eraseDegreeA(edge* stale)
{
	if (stale->degreeOfA->pre != NULL) //�տ� �ּҰ��� ���� �ƴϰ�
	{
		if (stale->degreeOfA->next != NULL) //���� �ּҰ��� ���� �ƴϸ�
		{
			stale->degreeOfA->next->pre = stale->degreeOfA->pre;
			stale->degreeOfA->pre->next = stale->degreeOfA->next;
		}
		else //���� �ּҰ��� ���̶��
		{
			stale->degreeOfA->pre->next = NULL;
		}
	}
	else //���� �� ������ degree(header)���ٸ�
	{
		if (stale->degreeOfA->next != NULL) //���� �ּҰ��� ���� �ƴϸ�
		{
			stale->degreeOfA->next->pre = NULL;
			stale->a->degree = stale->degreeOfA->next;
		}
		else //���� ���� ������(�ϳ� ���� ��尡 �����Ǹ�
		{
			stale->a->degree = NULL;
		}
	}
	--stale->a->sizeOfDegree;
	delete stale->degreeOfA;
}
void graph::eraseDegreeB(edge* stale)
{
	if (stale->degreeOfB->pre != NULL) //�տ� �ּҰ��� ���� �ƴϰ�
	{
		if (stale->degreeOfB->next != NULL) //���� �ּҰ��� ���� �ƴϸ�
		{
			stale->degreeOfB->next->pre = stale->degreeOfB->pre;
			stale->degreeOfB->pre->next = stale->degreeOfB->next;
		}
		else //���� �ּҰ��� ���̶��
		{
			stale->degreeOfB->pre->next = NULL;
		}
	}
	else //���� �� ������ degree(header)���ٸ�
	{
		if (stale->degreeOfB->next != NULL) //���� �ּҰ��� ���� �ƴϸ�
		{
			stale->degreeOfB->next->pre = NULL;
			stale->b->degree = stale->degreeOfB->next;
		}
		else //���� ���� ������(�ϳ� ���� ��尡 �����Ǹ�
		{
			stale->b->degree = NULL;
		}
	}
	--stale->b->sizeOfDegree;
	delete stale->degreeOfB;
}
void graph::incidentEdges(int studentNumber) //������ �������� ã�´�
{
	vertex* i = findVertex(studentNumber); //�й����� vertex�� ã��
	if (i == NULL) //���ٸ�
	{
		cout << "Not found" << endl;
		return;
	}
	cout << i->sizeOfDegree; //�ִٸ� ���� �� ����ϰ�
	edges(i); //������ ���
}
vertex* graph::findVertex(int studentNumber) //���� �й��� ���� vertex�� ã�´�
{
	vertexList* i = vertexHeader;
	do{
		if (i->myvertex->studentNumber == studentNumber) //�й��� ���ٸ�
		{
			return i->myvertex; //�� �ڸ��� vertex�� ����Ѵ�
		}
		i = i->next; //ã�� ���ߴٸ� ����ؼ� Ž��
	} while (i != NULL);
	//cout << "Not Found" << endl; //���� ã�Ƽ� ���ٸ�
	return NULL;
}
edge* graph::findEdge(int doroNumber) //���� �й��� ���� vertex�� ã�´�
{
	edgeList* i = edgeHeader; //edgeList�� ó�� ������ �ʱ�ȭ ���ְ�
	do
	{
		if (i->myEdge->doroNumber == doroNumber) //ó������ doroNumber�� Ȯ���Ѵ�
		{
			return i->myEdge; //doroNumber�� ���� ���̸� �ش� �ּҸ� �����Ѵ�.
		}
		i = i->next;
	} while (i!=NULL);
	//cout << "Not found" << endl; //ã�� ���ϸ�
	return NULL;
}
void graph::edges(vertex* v) //vertex�� ��� edge�� ã�´�
{
	edgeList* j=NULL;
	for (edgeList* i = v->degree; i != NULL; i = i->next) //���θ� �߰��� ������� ����ؾ��ϹǷ� head�� �Է��� ������ �� �ں��� ����ϸ�ȴ�
		if (i->next == NULL)	{ j = i; }
	for (j; j != NULL; j = j->pre)
		cout << " " << j->myEdge->doroNumber;

	cout << endl;
}