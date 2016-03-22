#10주차 과제
#뚜레쥬르 크롤링
#page 1:137

library(stringr)
library(readr)
library(foreach)
library(doSNOW)

registerDoSNOW(makeCluster(2, type = "SOCK")) #코어 2개를 만들어라
getDoParWorkers()

func<-function()
{
  #schema
  result<-as.data.frame(matrix(ncol=5))
  # for(i in 1:137)
  foreach(i=1:137) %do% #dopar로 코어 다 쓸려고하는데 왜 str_detect를 찾을수 없다고 나올까요?
  {
    url<-paste0("http://www.tlj.co.kr/store/search.asp?page=",i)
    HTML_code<-read_lines(url)
    HTML_code<-`Encoding<-`(HTML_code,"euc-kr")
    #위도, 경도
    #내가 뚜레주르 관련 사이트를 만든다면 위도 경도도 필요할때가 있겠지?
    locate<-HTML_code[str_detect(HTML_code,"data-lat=")]
    locate<-gsub("\t","",locate)
    locate<-gsub("<.*?data-lat=\"","",locate)
    locate<-gsub("\".*?=\\\"",", ",locate)
    locate<-gsub(", \\\">","",locate)
    if(i==133){locate<-gsub(", /.*?>","",locate)}
    #지점 이름
    branch<-HTML_code[str_detect(HTML_code,"\"listName_")]
    branch<-gsub("<.*?>","",branch)
    branch<-gsub("\t","",branch)
    
    #도로명 주소
    index<-str_detect(HTML_code,"\"listAddrD_")
    index<-which(index==TRUE)+1
    doro<-HTML_code[index]
    doro<-gsub("\t","",doro)
    
    #지번 주소 (필요한가?)
    index<-str_detect(HTML_code,"\"listAddrJ_")
    index<-which(index==TRUE)+1
    addr<-HTML_code[index]
    addr<-gsub("\t","",addr)
    
    #전화번호
    tel<-HTML_code[str_detect(HTML_code,"\"listTel_")]
    tel<-gsub("<.*?>","",tel)
    tel<-gsub("\t","",tel)
    
    
    my_matrix<-cbind(as.matrix(locate,ncol=1),as.matrix(branch,ncol=1),as.matrix(doro,ncol=1),
                     as.matrix(addr,ncol=1),as.matrix(tel,ncol=1))
    result<-rbind(result,my_matrix) #위도가 제일 앞이면 이상한가..?
  }
  colnames(result)<-c("Locate","Name","Address1","Address2","Phone number")
  View(result)
}
system.time(func())

#그냥 for문 돌렸을때
# 사용자  시스템 elapsed 
# 9.03   53.05   66.74 

# foreach돌렸을때..별로 차이 없네? 잘 안된건가?
# 사용자  시스템 elapsed 
# 8.34   50.25   59.04 
