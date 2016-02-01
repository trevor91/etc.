#pragma once
#include <string>
#include <iostream>
using namespace std;
class vertex;
class edge;
class edgeList;

class edgeList
{
	friend class graph;
public:
	edgeList()
	{
		next = NULL;
		pre = NULL;
		myEdge = NULL;
	}
private:
	edgeList* next; //list�� ���� edge
	edgeList* pre; //list�� ���� edge
	edge* myEdge; //list�� ����Ű�� edge
};
class vertexList
{
	friend class graph;
public:
	vertexList()
	{
		next = NULL;
		pre = NULL;
		myvertex = NULL;
	}
private:
	vertexList* next; //list�� ���� vertex
	vertexList* pre; //list�� ���� vertex
	vertex* myvertex; //list�� ����Ű�� vertex
};
class edge
{
	friend class graph;
public:
	edge()
	{
		doroNumber = 0;
		a = NULL;
		b = NULL;
		degreeOfA = NULL;
		degreeOfB = NULL;
		myEdgeList = NULL;
	}
private:
	int doroNumber; //���ι�ȣ(������)
	vertex* a; //������ �л��ּ�
	vertex* b; //�ٸ� ������ �л��ּ�
	edgeList* degreeOfA; //���� ����Ű�� a������ degree
	edgeList* degreeOfB; //���� ����Ű�� b������ degree
	edgeList* myEdgeList; //edge�� ����Ű�� list
};
class vertex
{
	friend class graph;
public:
	vertex()
	{
		studentNumber = 0;
		sizeOfDegree = 0;
		degree = NULL;
		myvertexList = NULL;
	}
private:
	int studentNumber; //�й�(������)
	int sizeOfDegree; //����� ������ ��
	string mail; //mail
	edgeList* degree; //�ڽſ��� ����� ������ list
	vertexList* myvertexList; //vertex�� ����Ű�� list
};
class graph
{
	friend class edge;
	friend class vertex;
	friend class edgeList;
	friend class vertexList;
public:
	graph()
	{
		vertexHeader = NULL;
		edgeHeader = NULL;
		sizeOfVertex = 0;
		sizeOfEdge = 0;
	}
	//Accessor Methods
	void endVertices(int); //edge�� ����� vertex�� ã���ִ� �Լ�
	void opposite(int,int); //edge�� ����� v���vertex���� �ٸ� vertex�� ã���ִ� �Լ�
	int opposite(edge*, vertex*);
	bool isAdjacentTo(int,int); //�� ���� ���̿� ������ �ٷ� ����Ǿ� �ִ��� �����ĸ� ���
	void printStudent(int studentNumber); // �л� ������ ���
	//Updata Methods
	void insertVertex(int,string); //������ ����
	bool insertEdge(int,int,int); //������ ����
	void eraseVertex(int); //������ ����
	void eraseVertexList(vertexList*); //vertexList����
	void eraseEdge(edge*); //������ ����, edge�� �ּҸ� �˰� ������
	void eraseEdge(int); //������ ����, edge�� �ּҸ� �𸦶�
	void eraseEdgeList(edgeList*); //EdgeList�� ����
	void eraseDegreeA(edge*); //DegreeA�� ������ ����
	void eraseDegreeB(edge*); //DegreeB�� ������ ����
	//Iterable Collection Methods
	void incidentEdges(int); //������ �������� ã�´�
	vertex* findVertex(int); //�Ѱ��ִ� �й��� ���� vertex�� ã�´�
	edge* findEdge(int); //�Ѱ��ִ� ���ι�ȣ�� ���� edge�� ã�´�
	void edges(vertex*); //��� edge�� ã�´�
	void printSizeOfVertex() { cout << sizeOfVertex << endl; }
	void printSizeOfEdge() { cout << sizeOfEdge << endl; }
private:
	vertexList* vertexHeader; //vertexList ����� header
	edgeList* edgeHeader; //edgeList ����� header
	int sizeOfVertex; //n
	int sizeOfEdge; //m
};