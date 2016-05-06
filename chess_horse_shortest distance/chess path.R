#체스 경로

#전역변수
store_x<-c()
store_y<-c()
result<-c()
#
my_func<-function(x,y,par_x,par_y)
{
  pre_x<-par_x
  pre_y<-par_y
  gap_x<-x-pre_x
  gap_y<-y-pre_y
  if((gap_x==0)&(gap_y==0)){return (TRUE)}
  angle<-atan(gap_y/gap_x)
  store_x<<-c()
  store_y<<-c()
  if((gap_x<5)&(gap_y<5)&(gap_x>-5)&(gap_y>-5)) #목표물 근처에가면 전수조사
  {
    store_x<<-c(store_x,pre_x+2)
    store_y<<-c(store_y,pre_y+1)
    #
    store_x<<-c(store_x,pre_x+2)
    store_y<<-c(store_y,pre_y-1)
    #
    store_x<<-c(store_x,pre_x-2)
    store_y<<-c(store_y,pre_y+1)
    #
    store_x<<-c(store_x,pre_x-2)
    store_y<<-c(store_y,pre_y-1)
    #
    store_x<<-c(store_x,pre_x+1)
    store_y<<-c(store_y,pre_y+2)
    #
    store_x<<-c(store_x,pre_x+1)
    store_y<<-c(store_y,pre_y-2)
    #
    store_x<<-c(store_x,pre_x-1)
    store_y<<-c(store_y,pre_y+2)
    #
    store_x<<-c(store_x,pre_x-1)
    store_y<<-c(store_y,pre_y-2)
  }else if((gap_x>0)&(gap_y>0))
  {
    if((angle<=0)&(angle>-1.3)) #1사분면을 벗어나면 & 1사분면 근방이면
    {
      if(gap_x>gap_y) #4사분면이며
      {
        store_x<<-c(store_x,pre_x+2)
        store_y<<-c(store_y,pre_y+1)
      }else #2사분면이면
      {
        store_x<<-c(store_x,pre_x+1)
        store_y<<-c(store_y,pre_y+2)
      }
    }else if((angle<=0.5235988)&(angle>0)) #1~30도 //gap_x가 gap_y보다 크다
    {
      store_x<<-c(store_x,pre_x+2)
      store_y<<-c(store_y,pre_y+1)
      store_x<<-c(store_x,pre_x+2)
      store_y<<-c(store_y,pre_y-1)
    }else if((angle<=1.047198)&((angle>0.5235988))) #30~60도
    {
      store_x<<-c(store_x,pre_x+2)
      store_y<<-c(store_y,pre_y+1)
      store_x<<-c(store_x,pre_x+1)
      store_y<<-c(store_y,pre_y+2)
    }else if((angle<1.570796)&((angle>1.047198))) #60~89도  #(10000000,1)은 90도로 인식
    {
      store_x<<-c(store_x,pre_x-1)
      store_y<<-c(store_y,pre_y+2)
      store_x<<-c(store_x,pre_x+1)
      store_y<<-c(store_y,pre_y+2)
    }else{print("ERROR1")}
  }else{print("ERROR2")}
  
  store<-cbind(store_x,store_y)
  store<-unique(store)
  store_x<<-store[,1]
  store_y<<-store[,2]
  result[[length(result)+1]]<<-c(store)
  
  index_temp<-which(store_x==x)
  temp<-store_y[index_temp]
  temp<-which(temp==y)
  if(length(temp)){if(temp){return()}}
  
  if((gap_x>-2)|(gap_y>-2))
  {
    my_func(x,y,store_x,store_y)
  }
}
coordinate<-function(x,y) #목적지부터 출발지까지 지나온 좌표를 필터링
{
  ##목적지와 가까운곳부터 비교할 값을 정리.
  for(i in (length(result)-1):1)
  {
    if(i==length(result)-1) #목적지 도착 1번전.
    {
      next_xx<-x
      next_yy<-y
      pre_xx<-result[[i]][1:(length(result[[i]])/2)]
      pre_yy<-result[[i]][(length(result[[i]])/2+1):length(result[[i]])]
      before_xx<-result[[i-1]][1:(length(result[[i-1]])/2)]
      before_yy<-result[[i-1]][(length(result[[i-1]])/2+1):length(result[[i-1]])]
    }else if((i>1)&(length(result)>i))
    {
      next_xx<-result[[i+1]][1:(length(result[[i+1]])/2)]
      next_yy<-result[[i+1]][(length(result[[i+1]])/2+1):length(result[[i+1]])]
      pre_xx<-result[[i]][1:(length(result[[i]])/2)]
      pre_yy<-result[[i]][(length(result[[i]])/2+1):length(result[[i]])]
      before_xx<-result[[i-1]][1:(length(result[[i-1]])/2)]
      before_yy<-result[[i-1]][(length(result[[i-1]])/2+1):length(result[[i-1]])]
    }else if(i==1)
    {
      next_xx<-result[[i+1]][1:(length(result[[i+1]])/2)]
      next_yy<-result[[i+1]][(length(result[[i+1]])/2+1):length(result[[i+1]])]
      pre_xx<-result[[i]][1:(length(result[[i]])/2)]
      pre_yy<-result[[i]][(length(result[[i]])/2+1):length(result[[i]])]
      before_xx<-1 #시작점은 1,1이므로..
      before_yy<-1
    }
    index_xy<-c()
    ##정리한 값을 비교.
    for(j in 1:length(before_xx))
    {
      for(k in 1:length(next_xx))
      {
        #case1 next,pre
        index_xx_next<-which(abs(next_xx[k]-pre_xx)==2)
        index_yy_next<-which(abs(next_yy[k]-pre_yy)==1)
        index_xy_next<<-intersect(index_xx_next,index_yy_next)
        #case2
        index_xx_next<-which(abs(next_xx[k]-pre_xx)==1)
        index_yy_next<-which(abs(next_yy[k]-pre_yy)==2)
        index_xy_next<-c(index_xy_next,intersect(index_xx_next,index_yy_next))
        
        #case3 before,pre
        index_xx_before<-which(abs(before_xx[j]-pre_xx)==2)
        index_yy_before<-which(abs(before_yy[j]-pre_yy)==1)
        index_xy_before<<-intersect(index_xx_before,index_yy_before)
        #case4
        index_xx_before<-which(abs(before_xx[j]-pre_xx)==1)
        index_yy_before<-which(abs(before_yy[j]-pre_yy)==2)
        index_xy_before<-c(index_xy_before,intersect(index_xx_before,index_yy_before))
        #
        index_xy<<-intersect(index_xy_before,index_xy_next)
        print(index_xy)
      }
    }
    result[[i]]<<-c(pre_xx[index_xy],pre_yy[index_xy])
    print(result[[i]])
  }
  result<<-result[-length(result)]
  for(i in 1:length(result))
  {
    final_xx<-result[[i]][1:(length(result[[i]])/2)]
    final_yy<-result[[i]][(length(result[[i]])/2+1):length(result[[i]])]
    final_xy<-cbind(final_xx,final_yy)
    # final_xy<-unique(final_xy)
    print(final_xy)
  }
}
my_func(6,7,1,1)
coordinate(6,7)
# my_func(20,10,1,1)

for(i in 1:length(result))
{
  a<-result[[i]][1:(length(result[[i]])/2)]
  b<-result[[i]][(length(result[[i]])/2+1):length(result[[i]])]
  print(cbind(a,b))
}

