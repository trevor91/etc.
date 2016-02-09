bank<-function(target){
  num<-1:9
  digit<-c(10,100,1000,10000,100000000,1000000000000,10000000000000000)
  if(target=="영") {return (0)}
  target<-unlist(strsplit(target,""))
  
  #한국인 습관
  a<-which(target=="억")
  b<-which(target=="천")
  b<-b[length(b)]
  if(!length(a)|!length(b)){a<-0}
  else if(b-a==2){target<-c(target,"만")}
  
  num_index<-c()
  digit_index1<-c() #10,100,1000,10000 index
  digit_index2<-c() #억,조,경 index
  
  change<-function (temp)
  {
    if(temp=="일"){temp <- num[1]}
    else if(temp=="이"){temp <- num[2]}
    else if(temp=="삼"){temp <- num[3]}
    else if(temp=="사"){temp <- num[4]}
    else if(temp=="오"){temp <- num[5]}
    else if(temp=="육"){temp <- num[6]}
    else if(temp=="칠"){temp <- num[7]}
    else if(temp=="팔"){temp <- num[8]}
    else if(temp=="구"){temp <- num[9]}
    #
    else if(temp=="십"){temp <- digit[1]}
    else if(temp=="백"){temp <- digit[2]}
    else if(temp=="천"){temp <- digit[3]}
    else if(temp=="만"){temp <- digit[4]}
    else if(temp=="억"){temp <- digit[5]}
    else if(temp=="조"){temp <- digit[6]}
    else if(temp=="경"){temp <- digit[7]}
    else{return(FALSE)}
    return (temp)
  }
  target<-as.double(sapply(target,change)) #문자->숫자
  
  #자릿수의 index
  for(i in 1:4){
    if(target[1]==digit[i]){target<-append(target,1,after=0)} #6번 조건
    digit_index1<-c(digit_index1,which(target==digit[i]))
  }
  for(i in 5:7){
    if(target[1]==digit[i]){return(FALSE)} #억,조,경으로 시작하면 return FALSE
    digit_index2<-c(digit_index2,which(target==digit[i]))
  }
  num_index<-setdiff(1:length(target),digit_index1)
  num_index<-setdiff(num_index,digit_index2)

  #이제부터 숫자조합
  result<-NULL
  result2<-NULL
  if(!length(num_index)){num_index<<-0; result<<-1} #1~9 숫자가 없으면
  if(!length(digit_index1)){digit_index1<<-0} #10,100,1000,10000 숫자가 없으면
  
  for(i in 1:length(target))
  {
    if(max(match(num_index,i,nomatch = 0))) #한자리 수
    {
      result <- c(result, target[i])
    }else if(max(match(digit_index1,i,nomatch = 0)))  #10,100,1000,10000 자리수
    {
      result <- c(result,result[length(result)]*target[i])
      result <- result[-(length(result)-1)]
    }else  #억,조,경
    {
      result2<-c(result2,sum(result)*target[i])
      result<-NULL
    }
  }
  if(sum(result2,result)==0){return (FALSE)}
  return(sum(result2,result))
}

bank("영") #0
bank("일") #1
bank("칠") #7
bank("이천오") #2005
bank("구천") #9000
bank("일십만") #100,000
bank("십만") #100,000
bank("일억오천") #150,000,000
bank("억오천만") #false
bank("사천구십칠조이천만삼") #?

bank("한글")#false
bank("testestsetest")#false
bank("사천오백구십일억삼천") #459130000000
