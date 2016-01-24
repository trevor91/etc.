#include "Hash.h"
#include <iostream>
using namespace std;
Hash::Hash(){}
Hash::Hash(int n, int m, int q)
{
	countProbe = 0;
	key1 = 0;
	key2 = 0;

	tableSize = n; //테이블의 크기
	countStudent = m; //저장된 회원의 수
	primeNumber = q; //n보다 작은 소수
	table = new Student[tableSize]; //입력받은  n만큼 테이블을 만든다
	loadfactor = (double)countStudent / (double)tableSize;
}
int Hash::HashingOne(int number){return number%tableSize;} //1차 해쉬함수
int Hash::HashingTwo(int number){return primeNumber - (number%primeNumber);} //2차 해쉬함수
void Hash::insertStudent(int s, int t, string e) //s=학번, t=학점, e=메일  파일 입력을 통해 table을 구성하는 함수
{
	key1 = HashingOne(s);
	key2 = HashingTwo(s);
	if (table[key1].studentNumber == 0) //1차 해쉬함수에 값이 비어있으면 data들을 넣어준다
	{
		table[key1].studentNumber = s;
		table[key1].score = t;
		table[key1].mail = e;
	}
	else //1차 해쉬함수에 값이 있다면
	{
		for (int i = (key1 + key2)%tableSize; i != key1; i = (i+key2)%tableSize) //2차해쉬함수를 1차값과 더해주면서 순회한다.
		{
			if (table[i].studentNumber == 0) //순회 중에 비어있는곳을 찾으면 data들을 넣어준다
			{
				table[i].studentNumber = s;
				table[i].score = t;
				table[i].mail = e;
				break;
			}
		}
	}
}
void Hash::insertStudent(int s, string e) //PPT와 같게 s=학번, e=mail  //질의를 통해서 입력하는 함수
{
	key1 = HashingOne(s); //첫번째 해쉬값 입력
	countProbe = 0; //그 전 프로빙값이 남아있으므로 초기화
	++countProbe; //probe 횟수 증가시키고
	if (table[key1].mail == "") //키값 자리에 값이 없으면 입력 
	//위에선 학번이 있냐 없냐로 data를 확인했는데 여기선 메일값으로 확인.
	//실제 구성이라면 학번은 있고 메일이 없을 수 있지만, 이 과제에선 그런 경우는 없으므로 여러가지 방법으로 구성해보려고했습니다.
	{
		++countStudent; //학생수 증가
		table[key1].studentNumber = s; //학번 입력
		table[key1].mail = e; //메일 입력
	}
	else //1차 해쉬값에 자리가 있으면
	{
		key2 = HashingTwo(s); //두번째 해쉬값 입력
		//key1,2를 이용해서 table을 순회하면서 빈곳을 확인한다
		for (int i = (key1 + key2)%tableSize; i!=key1 ; i = (i + key2) % tableSize)
		{
			++countProbe; //뛸 때마다 probe 횟수 증가
			if (table[i].mail == "") //빈곳을 찾으면
			{
				++countStudent; //학생수 +1
				table[i].studentNumber = s; //학번 입력
				table[i].mail = e; //이메일 입력
				//table[i].marker = 0; //다시 값을 입력 받았으면 marker는 0으로
				break;
			}
		}
	}
	cout.precision(2); //소수점3째에서 반올림 -> 소수점 2자리까지 표현
	cout << countProbe << " " << fixed << loadFactor() << endl;
}
void Hash::insertSubject(int s, int c) //PPT와 같게 s는 학번 c는 수강과목의 학점
{
	key1 = HashingOne(s); //첫번째 해쉬값 입력
	countProbe = 0;
	++countProbe;
	if (table[key1].studentNumber == s) //키값의 인덱스 학번과 수강신청 학생 학번이 같으면
	{
		if ((table[key1].score + c) > 24){ cout << countProbe << " Exceeded" << endl; return; } //학점이 초과이면
		else //학점 초과가 아니면 학점을 올려준다
		{
			table[key1].score += c;
			cout << countProbe << " " << table[key1].score << endl;
		}
		return;
	}
	else if (table[key1].studentNumber == 0) //1차해 해쉬에 data가 없으면 (학생을 찾지 못하면)
	{
		cout << countProbe << " Not found" << endl; //찾는 학생이 없으면
		return;
	}
	else
	{
		key2 = HashingTwo(s); //두번째 해쉬값 입력
		//key1,2를 이용해서 table을 순회하면서 빈곳을 확인한다
		for (int i = (key1 + key2)%tableSize; key1 != i ; i = ((i + key2) % tableSize))
		{
			++countProbe;
			if (table[i].studentNumber == s) //학생을 찾으면
			{
				if (table[i].score + c > 24){ cout << countProbe << " Exceeded" << endl; return; } //학점 확인 후 초과하면
				else //초과하지 않으면
				{
					table[i].score += c;
					cout << countProbe << " " << table[i].score << endl;
				}
				return;
			}
			else if (table[i].studentNumber == 0) //찾는 값이 없다면
			{
				cout << countProbe << " Not found" << endl; //찾는 학생이 없으면
				return;
			}
		}
	}
}
void Hash::changeMail(int s, string e) //PPT와 같이 s는 학번 e는 메일
{
	key1 = HashingOne(s);
	key2 = HashingTwo(s);
	int i = key1; //i값 키값으로 초기화
	countProbe = 0;
	do //위에서 for문을 써서 순회를 했는데, 여러가지 방법으로 순회해보는것도 좋을것 같아서 do while로 순회합니다.
	{
		++countProbe;
		if (table[i].studentNumber == s)
		{
			table[i].mail = e;
			cout << countProbe << endl;
			return;
		}
		else if (table[i].studentNumber == 0)
		{
			cout << countProbe << " Not found" << endl; //찾는 학생이 없으면
			return;
		}
		i = (i+key2)%tableSize;
	} while (i != key1);
}
void Hash::printStudnet(int s) //s는 학번
{
	key1 = HashingOne(s);
	key2 = HashingTwo(s);
	int i = key1;
	countProbe = 0;
	do
	{
		++countProbe;
		if (table[i].studentNumber == s)
		{
			cout << countProbe << " " << table[i].studentNumber << " " << table[i].score << " " << table[i].mail << endl;
			countProbe = 0;
			return;
		}
		else if (table[i].studentNumber == 0)
		{
			cout << countProbe << " Not found" << endl; //찾는 학생이 없으면
			return;
		}
		i = (i+key2)%tableSize;
 	} while (i != key1);
}
double Hash::loadFactor()
{
	loadfactor = (double)countStudent/(double)tableSize;
	return loadfactor;
}