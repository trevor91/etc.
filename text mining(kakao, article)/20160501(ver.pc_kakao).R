#kakao
library(stringr)
text<-readLines(list.files()[1],encoding="UTF-8")
date_position<-which(str_detect(text,"-{15} [0-9]{4}년 [0-9]{1,2}월 [0-9]{1,2}일 .요일 -{15}")==TRUE)
#text[date_position]
date_text<-list()
for(i in 1:length(date_position))
{
  if(i!=length(date_position))
    date_text[i]<-list(text[(date_position[i]+1):(date_position[i+1]-1)])
  else
    date_text[i]<-list(text[(date_position[i]+1):length(text)])
  names(date_text)[i]<-gsub("-{15}","",text[date_position[i]])
}
