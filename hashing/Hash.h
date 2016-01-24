#pragma once
#include "Student.h"
using namespace std;

class Hash{
private:
	int tableSize; //테이블 크기
	int countStudent; //회원수
	int primeNumber; //n보다 작은 소수
	int countProbe; //probe 횟수 카운트
	int key1; //첫번째 키값
	int key2; //두번째 키값
	Student* table; //자료를 저장할 테이블
	double loadfactor; //적재율
public:
	Hash();
	Hash(int, int, int);
	//********Main Function*************
	int HashingOne(int); //1차 해쉬함수
	int HashingTwo(int); //2차 해쉬함수
	void insertStudent(int, int, string); //처음 hashTable을 구성하기 위한 입력
	void insertStudent(int,string); //질의를 통한 학생 입력
	void insertSubject(int,int); //수강 과목 추가
	void changeMail(int,string); //이메일 변경
	void printStudnet(int); //학생 정보 출력
	//**********************************
	double loadFactor(); //적재율 리턴함수
};