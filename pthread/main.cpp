#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

struct add_vec
{
	vector<int>::iterator begin;
	vector<int>::iterator end;
};
//전역 변수
vector<int> a; //숫자 배열을 읽어올 공간
add_vec add1; // 1번 쓰레드에서 처리해야할 범위
add_vec add2; // 2번 쓰레드에서 처리해야할 범위
add_vec add3; // 3번 쓰레드에서 처리해야할 범위
pthread_spinlock_t sort_lock;
int signal = 0; //bounded waiting을 만족하기 위한 신호
void print_vector(vector<int> target)
{
	for(vector<int>::iterator iter=target.begin();iter!=target.end();++iter)
		cout << *iter << " ";
	cout << endl;
}
void* p_sort(void* add)
{
	pthread_spin_lock(&sort_lock);
	add_vec* point = (add_vec*)add;
	sort(point->begin,point->end);
	++signal;
	pthread_spin_unlock(&sort_lock);
}
void* p_merge(void*)
{
	pthread_spin_lock(&sort_lock);
	if(signal==3)
	{
		vector<int> b(2*(a.capacity()/3)); //1,2thread merge space
		vector<int> result(a.capacity()); //1,2,3 thread merge space
		merge(add1.begin,add1.end,add2.begin,add2.end,b.begin()); //1,2 thread merge
		merge(b.begin(),b.end(),add3.begin,add3.end,result.begin()); //1,2,3 thread merge
		print_vector(result); //output
		
		//ppt에 나온것처럼 파일로 출력
		ofstream output;
		output.open("output.txt");
		for(vector<int>::iterator iter=result.begin();iter!=result.end();++iter)
			output << *iter << " ";
		output << endl;
		output.close();
		pthread_spin_unlock(&sort_lock);
	}
	else if(signal<3) //thread가 다 수행되지 않았다면 재귀
	{
		pthread_spin_unlock(&sort_lock);
		sleep(1);
		p_merge(NULL);
	}
	else if(signal>3) {cout << "Error" << endl;}
}
int main()
{
	//data입력
	ifstream inputData("input.txt");
	int temp;
	while(inputData>>temp){a.push_back(temp);} //파일 입력
	inputData.close();
	print_vector(a); //입력된 data확인

	//data 3등분하는 지점 체크
	int i = 0;
	add1.begin = a.begin();
	add3.end = a.end();
	for(vector<int>::iterator iter=a.begin();i<(2*(a.capacity()/3)+1);++iter)
	{
		if(i==(a.capacity()/3)) {add1.end = add2.begin = iter;}
		else if(i==(2*(a.capacity()/3))) {add2.end = add3.begin = iter;}
		++i;
	}

	pthread_spin_init(&sort_lock,0); //spinlock
	//thread 3개 생성
	pthread_t t[4]; //0~2 = sort, 3 = merge
	pthread_create(&t[0],NULL,p_sort,(void*)&add1);
	pthread_create(&t[1],NULL,p_sort,(void*)&add2);
	pthread_create(&t[2],NULL,p_sort,(void*)&add3);
	pthread_create(&t[3],NULL,p_merge,NULL);
	
	pthread_join(t[0],NULL);
	pthread_join(t[1],NULL);
	pthread_join(t[2],NULL);
	pthread_join(t[3],NULL);
	
	pthread_exit(NULL);
	pthread_exit(NULL);
	pthread_exit(NULL);
	pthread_exit(NULL);
	pthread_spin_destroy(&sort_lock); //spinlock
	return 0;
}
