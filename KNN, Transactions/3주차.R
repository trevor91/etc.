#연관성분석
library(arules)

data<-read.csv("C:...csv")
head(data)
str(data)
data<-data[c(-1,-2)] #가구번호, 년도 삭ㅈ
str(data)

#data.frame -> transactions
data$가구주.성별<-factor(data$가구주.성별, levels = c(1,2), labels = c("남자","여자") )
data$가구주.동거여부<-factor(data$가구주.동거여부, levels = c(1,2,3,4), labels = c("1인 가구","같이 살고있음","따로 살고있음(학업,취업)", "따로 살고있음(군인"))
data$가구주.교육정도_학교<-factor(data$가구주.교육정도_학교, levels = c(1,2,3,4,5,6,7), labels = c("안받음","초등학교","중학교", "고등학교", "대학(3년제 이하)", "대학(4년제 이상)","대학원이상"))
data$가구주.혼인상태<-factor(data$가구주.혼인상태, levels = c(1,2,3,4), labels = c("미혼","배우자 있음", "사별", "이혼"))
data$가구주.종사상지위<-factor(data$가구주.종사상지위, levels = c(1,2,3,4,5,6,7), labels = c("상용근로자","임시.일용근로자","고용원이 있는 자영업자", " 고용원이 없는 자영업자", "무급가족봉사자", "기타 종사자", "무직자"))
data$현재.살고.있는.주택의.종류<-factor(data$현재.살고.있는.주택의.종류, levels = c(1,2,3,4), labels = c("단독주택","아파트","연립 및 다세대주택", "기타"))
data$현재.살고.있는.주택의.입주형태<-factor(data$현재.살고.있는.주택의.입주형태, levels = c(1,2,3,4,5), labels = c("자기집","전세","보증금 있는 월세", "보증금 없는 월세", "기타"))
data$가구원수<-factor(data$가구원수,)
str(data)

#만나이
data$가구주.만나이<-cut(data$가구주.만나이,br=10*(1.7:9.7))
#sum(table(data$가구주.만나이))

#전용면적
#summary(data$전용면적)
data$전용면적<-cut(data$전용면적,br=c(-Inf,50,67,85,Inf))
#sum(table(data$전용면적))

#자산총액
#summary(data$자산총액)
data$자산총액<-cut(data$자산총액,br=c(-Inf,5586,16440,37000,Inf))
#sum(table(data$자산총액))

#금융자산
summary(data$금융자산)
data$금융자산<-cut(data$금융자산,br=c(-Inf,1002,3550,9292,Inf))
#sum(table(data$금융자산))

#부채총액
summary(data$부채총액)
data$부채총액<-cut(data$부채총액,br=c(-Inf,1,600,5360,Inf))
#sum(table(data$부채총액))

data.trans<- as(data,"transactions")
inspect(data.trans[1:10])
class(data.trans)

str(data.trans@transactionInfo)
str(data.trans@itemInfo)

rule<-apriori(data.trans, parameter = list(support=0.1, confidence=1.0)) #default값은 0.1, 0.8
rule
summary(rule)
inspect(rule)

#
rule<-apriori(data.trans,parameter = list(support=10000/19745, confidence=0.8))#,#)
              #appearance = list(rhs="soda",default="lhs"))
rule
rule<-sort(rule,by="lift")
inspect(rule[1:5])


#
ecl<-eclat(data.trans,parameter = list(support=100/19745))
summary(ecl)
inspect(ecl[1:5])
ecl<-sort(ecl,by="support")
inspect(ecl[1:5])

#####KNN
data<-iris
set.seed(1)
index<-sample(1:150,0.8*150)
train<-data[index,] #120개
test<-data[-index,] #30개
test$Species
my_knn <-function(k)
{
  result<-c()
  for(i in 1:30)
  {
    #거리
    a<-(train[,1]-test[i,1])^2
    b<-(train[,2]-test[i,2])^2
    c<-(train[,3]-test[i,3])^2
    d<-(train[,4]-test[i,4])^2
    distance<-sqrt(a+b+c+d)
    #짧은거리 index 찾기
    distanceRank<-rank(distance,ties.method = "min") #작은순서대로 Rank
    my_index<-c()
    my_index<-which(distanceRank<=k) #작은 값들의 index를 저장.
    #result에 level값 저장.
    result<-c(result,as.numeric(which(max(table(train[my_index,5]))==table(train[my_index,5]))))
  }
  result<-factor(result,levels=c(1:3),labels=c("setosa","versicolor","virginica"))
}
table(my_knn(6))
table(test[,5])
