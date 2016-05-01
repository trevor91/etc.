#pc 과부하를 줄이기 위해서
#step1에서는 title, article number만 가져오고
#step2에서 article number를 이용해서 기사 내용 수지집
library(stringr)

title<-NULL
artid<-NULL

#step1
for(i in 1:10)
{
  url<-paste0("http://news.khan.co.kr/kh_news/khan_art_list.html?code=910100&page=",i)
  page<-readLines(url,encoding="euc-kr")
  line<-page[str_detect(page,"http://news.khan.co.kr/kh_news/khan_art_view.html?")]
  line<-line[1:15]
  
  #title
  temp_title<-gsub("<.*?>","",line)
  temp_title<-gsub("\t","",temp_title)
  temp_title<-gsub("&quot;","\"",temp_title)
  title <-c(title,temp_title)
  #article id
  temp_artid<-gsub("\t","",line)
  temp_artid<-gsub("<li><span class=\'thumb\'>","",temp_artid)
  temp_artid<-gsub("<li><strong class='hd_title'>","",temp_artid)
  temp_artid<-gsub("</li>","",temp_artid)
  temp_artid<-substring(temp_artid,66,80)
  artid<-c(artid,temp_artid)
}
print("done step1")
#__________________________
#"[기타뉴스]" 제거
skip<-which(substring(title,1,6)=="[기타뉴스]")
title<-title[-skip]
artid<-artid[-skip]
#__________________________
print("start step2")
#step2
body<-NULL
for(i in 1:length(title))
{
  # if(skip[index]==i){++index;next} #[기타뉴스]면 실행안하고 다음 기사로
  article_url<-paste0("http://news.khan.co.kr/kh_news/khan_art_view.html?artid=",artid[i])
  article_url<-paste0(article_url,"&code=910100")
  page<-readLines(article_url,encoding = "euc-kr")
  
  line<-page[str_detect(page,"content_text")]
  temp_body<-gsub("<.*?>","",line)
  
  for(i in 1:length(temp_body))
  {
    if(i>1){temp_body[1]<-paste0(temp_body[1],temp_body[i])}
  }
  body<-c(body,temp_body[1])
}

result<-cbind(title,body)
write.csv(result,file="result.csv")
