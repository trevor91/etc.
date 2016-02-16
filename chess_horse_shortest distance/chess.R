#체스
#말이 해당 좌표에 최단경로로 도착하는 횟수 구하기
#말은 1,1에서 시작하고 좌표는 x,y

#횟수 중심의 코드
count<-0
my_func<-function(x,y,pre_x,pre_y)
{
  #차이 계산
  gap_x<-x-pre_x
  gap_y<-y-pre_y
  if((gap_x<=4)&(gap_y<=4))
  {
    #범위 안에 들어오면 길이계산.
    len<-gap_x^2+gap_y^2
    if(len==5){result<-count+1}
    else if((len==18)|(len==10)|(len==20)|(len==16)|(len==1)|(len==4)|(len==2)){result<-count+2}
    else if((len==13)|(len==9)|(len==8)|(len==25)|(len==17)){result<-count+3}
    else if((len==32)){result<-count+4}
    else {result<-"ERROR"}
    count<<-0
    return (result)
  }
  #move
  if(gap_x>gap_y)
  {
    if(gap_y<0)
    {
      next_x<-pre_x+2
      next_y<-pre_y-1
    }else
    {
      next_x<-pre_x+2
      next_y<-pre_y+1
    }
  }else
  {
    if(gap_x<0)
    {
      next_x<-pre_x-1
      next_y<-pre_y+2
    }else
    {
      next_x<-pre_x+1
      next_y<-pre_y+2
    }
  }
  count<<-count+1
  my_func(x,y,next_x,next_y)#재귀
}

my_func(24,17,1,1) #13 정답
my_func(23,12,1,1) #11 정답
my_func(12,23,1,1) #11 정답
my_func(10,11,1,1) #7 정답
my_func(11,10,1,1) #7 정답
my_func(20,1,1,1) #11 정답
my_func(1,20,1,1) #11 정답
my_func(33,15,1,1) #16 정답
my_func(75,53,1,1) #42 정답
my_func(84,14,1,1) #42 정답
my_func(55,37,1,1) #30 정답
