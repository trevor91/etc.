#####KNN
data<-iris
#표준화
normalize <-function(x)
{
  return ((x-min(x))/(max(x)-min(x)))
}
data2<-as.data.frame(lapply(data[,-5],normalize))
data<-cbind(data2,data$Species)
colnames(data)<-c("Sepal.Length", "Sepal.Width", "Petal.Length", "Petal.Width", "Species")
#random
set.seed(1)
index<-sample(1:150,0.8*150)
train<-data[index,] #120개
test<-data[-index,] #30개
test$Species

#
my_knn <-function(train, test,train_label,k)
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
    temp<-as.numeric(which(max(table(train_label[my_index]))==table(train_label[my_index])))
    result<-c(result,temp[1])
  }
  train_label<-unique(train_label)
  result<-factor(result,levels=c(1:length(train_label)),labels=train_label)
  return (result)
}
my_knn(train[,1:4], test,train[,5],5) #train, test, train_label, k
#test[,5]
#for(i in 1:120){print(table(my_knn(train[,1:4], test,train[,5],i)))}
