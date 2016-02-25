#6주차
#k-means

my_func<-function(data,k)
{
  # point<-matrix(rnorm(k*ncol(data)),ncol=ncol(data)) #랜덤 중심점.
  index<-sample(1:nrow(data),k) #Forgy 방식으로 중심점 설정
  point<-data[index,]
  
  colnames(point)<-colnames(data) #이름이 같아야 rbind가 된다.
  rownames(point)<-1:k
  combine<-rbind(point,data) #matrix상단에 중심점 저장
  while(1)
  {
    dis<-as.matrix(dist(combine)) #거리 구하고
    dis<-dis[,1:k] #뒷부분 필요 없으니 cut
    dis[which(dis==0)]<-NA #0 -> NA
    label<-as.factor(apply(dis,1,which.min)) #열별로 작은값 인덱스 저장
    combine<-cbind(combine,label)
    #
    center_coordinate<-aggregate(combine[1:(ncol(combine)-1)], by=list(combine$label), FUN=mean) #중심점 갱신
    line_index<-as.integer(as.character(center_coordinate[,1])) #어떤 중심점이 갱신된건지 확인
    point[line_index,]<-as.matrix(center_coordinate[,2:ncol(center_coordinate)]) #중심점이 갱신된것만 동기화해준다.
    same<-point==combine[1:nrow(point),1:ncol(point)]
    same<-which(same==FALSE) #일치하지 않는게 있다면 저장
    if(!length(same)) #전 중심점과 갱신한 중심점이 같다면
    {
#       combine<-combine[(k+1):nrow(combine),]
#       rownames(combine)<-1:nrow(combine)
      levels(combine[,ncol(combine)])<-c(1:k,"center")
      combine[1:k,ncol(combine)]<-"center"
      return(combine)
    }
    #중심점이 전과 다르다면
    combine<-combine[,-ncol(combine)] #label 제거
    combine[1:k,]<-point #중심점 combine에 갱신.
  }
}
# test<-my_func(iris[,-5],3)
test<-my_func(iris[,1:2],4) #그림 그려주려고 2차원 공간 데이터를 넣었습니다.
table(test[ncol(test)])


#그림그리기
library(plotly)
paint<-plot_ly(test, x = Sepal.Length, y = Sepal.Width, text = paste("label: ", label),
        mode = "markers", color = label)
#원 그리기 준비....
a<-which(test[,3]==1)
a1_min<-a[which.min(test[a,1])]
a2_min<-a[which.min(test[a,2])]
a1_max<-a[which.max(test[a,1])]
a2_max<-a[which.max(test[a,2])]
b<-which(test[,3]==2)
b1_min<-b[which.min(test[b,1])]
b2_min<-b[which.min(test[b,2])]
b1_max<-b[which.max(test[b,1])]
b2_max<-b[which.max(test[b,2])]
c<-which(test[,3]==3)
c1_min<-c[which.min(test[c,1])]
c2_min<-c[which.min(test[c,2])]
c1_max<-c[which.max(test[c,1])]
c2_max<-c[which.max(test[c,2])]
d<-which(test[,3]==4)
d1_min<-d[which.min(test[d,1])]
d2_min<-d[which.min(test[d,2])]
d1_max<-d[which.max(test[d,1])]
d2_max<-d[which.max(test[d,2])]

layout(paint, shapes = list(
         list(type = 'square',
              xref = 'x', x0 = test[a1_min,1], x1 = test[a1_max,1],
              yref = 'y', y0 = test[a2_min,2], y1 = test[a2_max,2],
              fillcolor = 'blue', line = list(color = 'black'),
              opacity = 0.2),
         list(type = 'square',
              xref = 'x', x0 = test[b1_min,1], x1 = test[b1_max,1],
              yref = 'y', y0 = test[b2_min,2], y1 = test[b2_max,2],
              fillcolor = 'green', line = list(color = 'black'),
              opacity = 0.2),
         list(type = 'square',
              xref = 'x', x0 = test[c1_min,1], x1 = test[c1_max,1],
              yref = 'y', y0 = test[c2_min,2], y1 = test[c2_max,2],
              fillcolor = 'red', line = list(color = 'black'),
              opacity = 0.2),
         list(type = 'square',
              xref = 'x', x0 = test[d1_min,1], x1 = test[d1_max,1],
              yref = 'y', y0 = test[d2_min,2], y1 = test[d2_max,2],
              fillcolor = 'yellow', line = list(color = 'black'),
              opacity = 0.2)))