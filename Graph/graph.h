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
	edgeList* next; //list의 다음 edge
	edgeList* pre; //list의 이전 edge
	edge* myEdge; //list가 가리키는 edge
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
	vertexList* next; //list의 다음 vertex
	vertexList* pre; //list의 이전 vertex
	vertex* myvertex; //list가 가리키는 vertex
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
	int doroNumber; //도로번호(유일함)
	vertex* a; //한점의 학생주소
	vertex* b; //다른 한점의 학생주소
	edgeList* degreeOfA; //나를 가리키는 a점정의 degree
	edgeList* degreeOfB; //나를 가리키는 b점정의 degree
	edgeList* myEdgeList; //edge가 가리키는 list
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
	int studentNumber; //학번(유일함)
	int sizeOfDegree; //연결된 간선의 수
	string mail; //mail
	edgeList* degree; //자신에게 연결된 간선의 list
	vertexList* myvertexList; //vertex가 가리키는 list
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
	void endVertices(int); //edge에 연결된 vertex를 찾아주는 함수
	void opposite(int,int); //edge에 연결된 v라는vertex말고 다른 vertex를 찾아주는 함수
	int opposite(edge*, vertex*);
	bool isAdjacentTo(int,int); //두 정점 사이에 간선이 바로 연결되어 있느냐 없느냐를 출력
	void printStudent(int studentNumber); // 학생 정보를 출력
	//Updata Methods
	void insertVertex(int,string); //정점을 삽입
	bool insertEdge(int,int,int); //간선을 삽입
	void eraseVertex(int); //정점을 삭제
	void eraseVertexList(vertexList*); //vertexList삭제
	void eraseEdge(edge*); //간선을 삭제, edge의 주소를 알고 있을때
	void eraseEdge(int); //간선을 삭제, edge의 주소를 모를때
	void eraseEdgeList(edgeList*); //EdgeList를 삭제
	void eraseDegreeA(edge*); //DegreeA의 간선을 삭제
	void eraseDegreeB(edge*); //DegreeB의 간선을 삭제
	//Iterable Collection Methods
	void incidentEdges(int); //정점의 간선들을 찾는다
	vertex* findVertex(int); //넘겨주는 학번을 가진 vertex를 찾는다
	edge* findEdge(int); //넘겨주는 도로번호를 가진 edge를 찾는다
	void edges(vertex*); //모든 edge를 찾는다
	void printSizeOfVertex() { cout << sizeOfVertex << endl; }
	void printSizeOfEdge() { cout << sizeOfEdge << endl; }
private:
	vertexList* vertexHeader; //vertexList 노드의 header
	edgeList* edgeHeader; //edgeList 노드의 header
	int sizeOfVertex; //n
	int sizeOfEdge; //m
};