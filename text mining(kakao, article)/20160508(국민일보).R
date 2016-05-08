#국민일보 
#정치 경제 국제 사회 연예
#title contents date category url
#http://news.kmib.co.kr/article/list_all.asp?sid1=pol&sid2=&sdate=20160508
library(stringr)
result<-NULL
result_title<-NULL
result_date<-NULL
result_url<-NULL
result_cate<-NULL
result_cont<-NULL
cate<-c("pol","eco","int","soc","ent")
# for(j in 1:length(cate))
for(j in 5:5) #____1:5까지 한번에 실행 x...  1:1,2:2,3:3,4:4,5:5 로 따로 실행하면 정상작동
{
  #__________________________TITLE, DATE, URL___________________________
  
  # may<-paste0("http://news.kmib.co.kr/article/list_all.asp?sid1=pol&sid2=&sdate=2016050",1:8)
  may<-paste0("http://news.kmib.co.kr/article/list_all.asp?sid1=",cate[j])
  may<-paste0(may,"&sid2=&sdate=2016050")
  may<-paste0(may,1:8)
  for(i in 1:length(may))
  {
    #___SOURCE___
    url = may[i]
    code<-readLines(url,encoding="EUC-kr")
    line<-which(str_detect(code,"<dl class=\"nws\">")==TRUE)
    
    #___INDEX___
    line_title<-line+1
    line_date<-line+2
    
    #___SOURCE___
    text_title<-code[line_title]
    result_title<<-c(result_title,gsub("<.*?>","",text_title)) #title done
    
    text_date<-code[line_date]
    result_date<<-c(result_date,gsub("<.*?>","",text_date)) #data done
    
    text_url<-code[line_title]
    result_url<<-c(result_url,substring(text_url,14,61)) #url done
  }
  result_url <<- paste0("http://news.kmib.co.kr/article/",result_url)

  #__________________________CATEGORY, CONTENTS___________________________
  for(i in 1:length(result_url))
  {
    code<-readLines(result_url[i])
    
    #INDEX
    line_cont<-which(str_detect(code,"<div class=\"tx\" id=\"articleBody\">")==TRUE)+4
    line_cate<-which(str_detect(code,"<a href=\"list.*?sid1=")==TRUE)
    
    #TEXT
    text_cont<-code[line_cont]
    text_cate<-code[line_cate]
    
    #
    text_cont<-gsub("<.*?>","",text_cont)
    text_cont<-gsub("\\t","",text_cont)
    result_cont <<-c(result_cont,text_cont)
    
    text_cate<-gsub("<.*?>","",text_cate)
    text_cate<-gsub("\\t","",text_cate)
    result_cate<<-c(result_cate,text_cate[length(text_cate)])
  }
  result<<-rbind(result,cbind(result_title, result_cont,result_date,result_cate,result_url))
}
colnames(result) <-c("title", "contents", "date", "category", "url")
write.csv(result,file="국민일보.csv",row.names=F)
