#generator
#1~4999사이의 Self-Number들의 합을 구하여라.
area<-1:4999
gen<-c()
for(i in 1:4999) #area에 해당하는 genarator를 찾는다
{
  if(i<10) #한자리 수
  {
    temp<-i*2
  }else if(i<100) #두자리 수
  {
    temp <- i%/%10 + i%%10 + i
  }else if(i<1000) #세자리 수
  {
    temp<-i%/%100 + i%/%10%%10 + i%%10 + i
  }else #네자리 수
  {
    temp<-i%/%1000 + i%/%100%%10 + i%/%10%%10 + i%%10 + i
  }
  gen<-c(gen,temp)
}
gen<-unique(gen[gen<5000]) #5000미만 숫자만 뽑고 중복 제거
#duplicated(gen) #중복 제거 확인
selfNumber <- setdiff(area,gen) #차집합
#합집합 union
#교집합 intersect
result<-sum(selfNumber)


#%%%%%another
library(stringr)

func<-function(setNum)
{
  area<-1:setNum
  gen<-c()
  for(i in 1:setNum)
  {
    temp<-str_split(i,'')
    temp<-as.integer(temp[[1]])
    gen<-c(gen,sum(temp)+i)
  }
  selfNumber<-setdiff(area,gen)
  return (sum(selfNumber))
}
system.time(func(4999))

##%%%%%another
library(stringr)
aaa<-function(set)
{
  range<-1:set
  a<-str_split(range,'')
  a<-sapply(a,function(a){
    sum(as.integer(a))
  })
  a<-a+range
  a<-unique(a)
  a<-a[a<set+1]
  result<-setdiff(range,a)
  sum(result)
}
#as.integer(unlist(a))
system.time(aaa(4999))

