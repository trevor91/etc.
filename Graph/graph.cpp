#include "graph.h"
#pragma once
#include <iostream>
using namespace std;

void graph::endVertices(int doroNumber) //edge에 연결된 vertex를 찾아주는 함수
{
	edge* e = findEdge(doroNumber);
	if (e == NULL) { cout << "Not found" << endl; return; } //만약 반환값이 NULL이라면 return

	if (e->a->studentNumber > e->b->studentNumber) //작은 값 먼저 출력하기 위해서 비교
		cout << e->b->studentNumber << " " << e->a->studentNumber << endl;
	else
		cout << e->a->studentNumber << " " << e->b->studentNumber << endl;
}
void graph::opposite(int studentNumber,int doroNumber) //edge에 연결된 v라는vertex말고 다른 vertex를 찾아주는 함수
{
	vertex* v = findVertex(studentNumber);
	edge* e = findEdge(doroNumber);
	if ((e == NULL) || (v == NULL)) { cout << "Not available" << endl; return; } //반환값이 NULL이라면 return
	if (e->a == v){ cout << e->b->studentNumber << endl; } //반대쪽 값을 출력한다
	else if(e->b == v){ cout << e->a->studentNumber << endl; }
	else cout << "Not available" << endl;
}
int graph::opposite(edge* e,vertex* v) //edge에 연결된 v라는vertex말고 다른 vertex를 찾아주는 함수
{
	if (e->a == v){ return e->b->studentNumber; }
	else{ return e->a->studentNumber; }
}
bool graph::isAdjacentTo(int studentNumber1, int studentNumber2) //두 정점 사이에 간선이 바로 연결되어 있느냐 없느냐를 출력
{
	vertex* v = findVertex(studentNumber1); //두 정점의 값을 찾고
	vertex* w = findVertex(studentNumber2);
	if ((v == NULL) || (w == NULL) || (v->degree ==NULL) || (w->degree ==NULL)) //만약 주소값이 하나 이상이 없는 값이라면
	{
		cout << "Not found" << endl; //NULL 이므로 return
		return 0;
	}
	if (v->sizeOfDegree > w->sizeOfDegree) //w의 간선의 수가 더 적다면
	{
		edgeList* i = w->degree; //w의 간선으로 찾는다
		do
		{
			if (opposite(i->myEdge, w) == v->studentNumber) //반대쪽 정점의 학번과 v의 학번이 같다면
			{
				cout << i->myEdge->doroNumber << endl; //도로번호를 출력한다
				return 0;
			}
			i = i->next;
		} while (i!=NULL);
	}
	else //v의 간선이 더 적거나 같았다면
	{
		edgeList* i = v->degree; //v의 간선으로 찾는다
		do
		{
			if (opposite(i->myEdge, v) == w->studentNumber) //반대쪽 정점의 학번과 w의 학번이 같다면
			{
				cout << i->myEdge->doroNumber << endl; // 도로보호를 출력한다
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
	vertex* target = findVertex(studentNumber); //학생을 찾고
	if (target == NULL) //학생이 없다면 Notfound
	{
		cout << "Not found" << endl;
	}
	else if (target != NULL) //학생이 있다면
		cout << target->mail << " " << target->sizeOfDegree << endl;
}
void graph::insertVertex(int studentNumber, string mail) //정점을 삽입
{
	vertex* fresh = new vertex; //vertex를 새로 만들고
	vertexList* freshList = new vertexList; //vertexList도 새로 
	++sizeOfVertex; // size증가 시키고
	fresh->studentNumber = studentNumber; //학번 초기화
	fresh->mail = mail; //메일 초기화
	fresh->degree = NULL; //간선은 없고
	fresh->sizeOfDegree = 0; //그러므로size= 0
	//vertex와 vertexList를 서로 연결
	fresh->myvertexList = freshList;
	freshList->myvertex = fresh;
	//freshList 값 세팅
	if (vertexHeader == NULL) { vertexHeader = freshList; } //처음 입력받은 vertex라면
	else //기존에 vertex가 있었다면
	{
		freshList->next = vertexHeader; //리스트로 연결해준다
		freshList->pre = NULL;
		vertexHeader->pre = freshList;
		vertexHeader = freshList;
	}
}
bool graph::insertEdge(int studentV, int studentW, int doronumber) //간선을 삽입
{
	edge* fresh = new edge; //신선한 간선을 만들고
	edgeList* freshList = new edgeList; //신선한 간선 리스트들을 만든다
	vertex* v = findVertex(studentV); //학번에 해당하는 vertex를 찾고
	vertex* w = findVertex(studentW);
	if ((v == NULL) || (w == NULL)) //만약 없는 값이라면은
	{
		cout << sizeOfEdge << " Not found" << endl;
		return false;
	}
	fresh->a = v;//정점 연걸
	v->sizeOfDegree++;
	fresh->b = w;//정점 연결
	w->sizeOfDegree++;
	fresh->doroNumber = doronumber; //도로번호 입력
	//edge, edgeList 서로 연결
	fresh->myEdgeList = freshList;
	freshList->myEdge = fresh;

	if (edgeHeader == NULL)	{ edgeHeader = freshList; } //처음 입력받은거면
	else //기존에 header가 있었다면 리스트로 연결해준다
	{
		freshList->next = edgeHeader;
		freshList->pre = NULL;
		freshList->next->pre = freshList;
		edgeHeader = freshList;
	}

	//degreeList 세팅
	edgeList* vDegree = new edgeList; //vertex와 edge를 연결시켜주는 edgeList를 만든다
	edgeList* wDegree = new edgeList;
	vDegree->next = v->degree; //degree List에서 header부분에 삽입한다
	wDegree->next = w->degree;
	vDegree->pre = NULL; //header에 입력했으니 pre는 NULL
	wDegree->pre = NULL;
	if (v->degree == NULL) { v->degree = vDegree; } //기존 header값을 가진 객체는 삽입된 객체의 주소를 pre에 저장한다
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
	fresh->degreeOfA = vDegree; //edge와 degreeList연결
	fresh->degreeOfB = wDegree;
	fresh->degreeOfA->myEdge = fresh;
	fresh->degreeOfB->myEdge = fresh;
	++sizeOfEdge;//size 증가 시키고
	return true;
}
void graph::eraseVertex(int studentNumber) //정점을 삭제
{
	// 간선을 먼저 지우고 vertex를 지운다
	vertex* stale = findVertex(studentNumber); //해당 vertex를 찾는다
	if (stale == NULL) //vertex가 없다면
	{
		cout << sizeOfVertex << " "<< sizeOfEdge << " Not found" << endl;
		return;
	}
	for (edgeList* i = stale->degree; i != NULL; i=stale->degree) //간선들 먼저 삭제한다
	{
		if(i->myEdge != NULL) eraseEdge(i->myEdge); //eraseEdge로 돌아가면서 간선을 삭제한다
	}
	eraseVertexList(stale->myvertexList);//vertexList 지우기
	delete stale; //마지막 vertex를 지운다
	cout << --sizeOfVertex << " " << sizeOfEdge << endl;
	return;
}
void graph::eraseVertexList(vertexList* stale)
{
	//리스트 삭제
	if (stale->pre != NULL) //앞에 주소값이 널이 아니고
	{
		if (stale->next != NULL) //다음 주소값이 널이 아니면
		{
			stale->next->pre = stale->pre;
			stale->pre->next = stale->next;
		}
		else //다음 주소값이 널이라면
		{
			stale->pre->next = NULL;
		}
	}
	else //삭제 할 정점이 degree(header)였다면
	{
		if (stale->next != NULL) //다음 주소값이 널이 아니면
		{
			stale->next->pre = NULL;
			vertexHeader = stale->next;
		}
		else //다음 값도 없으면(하나 남은 노드가 삭제되면
		{
			sizeOfEdge = 0;
			vertexHeader = NULL;
		}
	}
	delete stale;
}
void graph::eraseEdge(edge* stale) //간선을 삭제 , egde의 주소를 알때
{
	//edge들을 삭제
	eraseEdgeList(stale->myEdgeList); //myEdgeList 삭제
	eraseDegreeA(stale); //degreeA를 삭제한다
	eraseDegreeB(stale); //degreeB를 삭제한다
	delete stale;
	--sizeOfEdge;
}
void graph::eraseEdge(int doroNumber) //간선을 삭제, edge의 주소를 모를때
{
	edge* stale = findEdge(doroNumber); //해당 간선을 찾는다
	if (stale == NULL) //찾는 값이 없다면
	{
		cout << sizeOfEdge << " Not found" << endl;
		return;
	}
	//edge들을 삭제
	eraseEdgeList(stale->myEdgeList); //myEdgeList 삭제
	eraseDegreeA(stale); //degreeA를 삭제한다
	eraseDegreeB(stale); //degreeB를 삭제한다
	--sizeOfEdge;
	delete stale;
	cout << sizeOfEdge << endl;
}
void graph::eraseEdgeList(edgeList* stale)
{
	if (stale->pre != NULL) //앞에 주소값이 널이 아니고
	{
		if (stale->next != NULL) //다음 주소값이 널이 아니면
		{
			stale->next->pre = stale->pre;
			stale->pre->next = stale->next;
		}
		else //다음 주소값이 널이라면
		{
			stale->pre->next = NULL;
		}
	}
	else //삭제 할 정점이 degree(header)였다면
	{
		if (stale->next != NULL) //다음 주소값이 널이 아니면
		{
			stale->next->pre = NULL;
			edgeHeader = stale->next;
		}
		else //다음 값도 없으면(하나 남은 노드가 삭제되면
		{
			sizeOfEdge = 0;
			edgeHeader = NULL;
		}
	}
	delete stale;
}
void graph::eraseDegreeA(edge* stale)
{
	if (stale->degreeOfA->pre != NULL) //앞에 주소값이 널이 아니고
	{
		if (stale->degreeOfA->next != NULL) //다음 주소값이 널이 아니면
		{
			stale->degreeOfA->next->pre = stale->degreeOfA->pre;
			stale->degreeOfA->pre->next = stale->degreeOfA->next;
		}
		else //다음 주소값이 널이라면
		{
			stale->degreeOfA->pre->next = NULL;
		}
	}
	else //삭제 할 정점이 degree(header)였다면
	{
		if (stale->degreeOfA->next != NULL) //다음 주소값이 널이 아니면
		{
			stale->degreeOfA->next->pre = NULL;
			stale->a->degree = stale->degreeOfA->next;
		}
		else //다음 값도 없으면(하나 남은 노드가 삭제되면
		{
			stale->a->degree = NULL;
		}
	}
	--stale->a->sizeOfDegree;
	delete stale->degreeOfA;
}
void graph::eraseDegreeB(edge* stale)
{
	if (stale->degreeOfB->pre != NULL) //앞에 주소값이 널이 아니고
	{
		if (stale->degreeOfB->next != NULL) //다음 주소값이 널이 아니면
		{
			stale->degreeOfB->next->pre = stale->degreeOfB->pre;
			stale->degreeOfB->pre->next = stale->degreeOfB->next;
		}
		else //다음 주소값이 널이라면
		{
			stale->degreeOfB->pre->next = NULL;
		}
	}
	else //삭제 할 정점이 degree(header)였다면
	{
		if (stale->degreeOfB->next != NULL) //다음 주소값이 널이 아니면
		{
			stale->degreeOfB->next->pre = NULL;
			stale->b->degree = stale->degreeOfB->next;
		}
		else //다음 값도 없으면(하나 남은 노드가 삭제되면
		{
			stale->b->degree = NULL;
		}
	}
	--stale->b->sizeOfDegree;
	delete stale->degreeOfB;
}
void graph::incidentEdges(int studentNumber) //정점의 간선들을 찾는다
{
	vertex* i = findVertex(studentNumber); //학번으로 vertex를 찾고
	if (i == NULL) //없다면
	{
		cout << "Not found" << endl;
		return;
	}
	cout << i->sizeOfDegree; //있다면 간선 수 출력하고
	edges(i); //간선도 출력
}
vertex* graph::findVertex(int studentNumber) //같은 학번을 가진 vertex를 찾는다
{
	vertexList* i = vertexHeader;
	do{
		if (i->myvertex->studentNumber == studentNumber) //학번이 같다면
		{
			return i->myvertex; //그 자리의 vertex를 출력한다
		}
		i = i->next; //찾지 못했다면 계속해서 탐색
	} while (i != NULL);
	//cout << "Not Found" << endl; //전부 찾아서 없다면
	return NULL;
}
edge* graph::findEdge(int doroNumber) //같은 학번을 가진 vertex를 찾는다
{
	edgeList* i = edgeHeader; //edgeList의 처음 값으로 초기화 해주고
	do
	{
		if (i->myEdge->doroNumber == doroNumber) //처음부터 doroNumber를 확인한다
		{
			return i->myEdge; //doroNumber가 같은 값이면 해당 주소를 리턴한다.
		}
		i = i->next;
	} while (i!=NULL);
	//cout << "Not found" << endl; //찾지 못하면
	return NULL;
}
void graph::edges(vertex* v) //vertex의 모든 edge를 찾는다
{
	edgeList* j=NULL;
	for (edgeList* i = v->degree; i != NULL; i = i->next) //도로를 추가한 순서대로 출력해야하므로 head에 입력을 했으니 맨 뒤부터 출력하면된다
		if (i->next == NULL)	{ j = i; }
	for (j; j != NULL; j = j->pre)
		cout << " " << j->myEdge->doroNumber;

	cout << endl;
}