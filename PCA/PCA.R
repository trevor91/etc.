data<-read.csv("NBA.csv",stringsAsFactors=T)

ppm<-data[,"games"] * data[,"point"] / data[,"minutes"] #분당 득점률
data<-cbind(data,ppm)

# erase<-which(colnames(data)=="Name")
erase<-which(colnames(data)=="games") #삭제할 index 찾고
erase<-c(erase,which(colnames(data)=="minutes"))
erase<-c(erase,which(colnames(data)=="point"))
data<-data[,-erase] #Name, games, point, minutes 변수 삭제

# step1
# 주성분분석에서는 변수별로 단위가 다른 raw data를 사용하지 않고
# 평균과 표준편차를 가지고 표준화(standadization)한 데이터를 사용합니다.
# 그래야 scale이 다른 문제로 인한 데이터 왜곡을 피할 수 있기 때문입니다.
#아마 수업시간엔 log를 씌었던걸로 기억합니다. 이것도 해보고,,,저것도 해보고,,,
data_trans<-transform(data,
                height_s = scale(height),
                age_s = scale(age),
                assist_s = scale(assist),
                rebound_s = scale(rebound),
                fieldgoal_s = scale(fieldgoal),
                freethrow_s = scale(freethrow))
#근데 실행 전과 후에 다른게 없네요.

#step2
# 변수를 보고 이 값이 크면 좋은지, 작으면 좋은지를 판단합니다.
# 크면 좋은 변수와 작으면 좋은 변수는 서로 반대 방향으로 움직이는데
# 이를 같은 방향으로 수정해서 상관도가 높게 나와, 같은 주성분에 반영되도록합니다.
# height, age, assist, rebound, fieldgoal, freethrow 대부분 높으면 좋은 변수인데...
# 나이가 조금 걸리네요.나이 많으면 경험이 많아서 노련한데, 몸이 안따라주는것도 있고,,
# 나이가 적으면 좋다고 가정하고! 뭐 결과가 중요하겠습니까? 과정에서 배우는거죠.
# 사실 다 크면 좋은값이면 step2에서 할게 없습니다.
# data_trans <- transform(data_trans, age_s2 = max(age_s) - age_s)
data_trans_2 <- data_trans[,c("Name", "height_s", "age_s2", "assist_s", "rebound_s", "fieldgoal_s", "freethrow_s","ppm")]

#step3
# 변수들간의 상관계수를 분석해보겠습니다.
# 주성분분석이 변수들 간의 상관관계가 높다는 것을 가정하고 있기 때문에
# 한번 확인해보도록 하겠습니다.
library(psych)
pairs.panels(data_trans_2[,-1])
#reboud와 assist가 60%정도로 상관관계가 높네요.

#step4
# 이제 주성분 분석해야죠. prcomp()를 사용합니다.
data_prcomp <- prcomp(data_trans_2[,c(2:7)]) #ppm은 빼고
summary(data_prcomp) #80% 이상의 성과를 내려면 PC4까지 써야하네요...(기대 이하..)
# 1요인이 표준편차가 1.4로 가장 크네요.

print(data_prcomp)
# 1요인은 assist와 rebound와 관련이 크고,,득점과 관련된것과 조금씩 관련이 있는데..?
# 2요인은 키와 관련이 크고
# 3요인은 자유투와 관련이 있고...
# 4요인은 나이와 득점과 관련이 크고
# 5요인은 필드골,도움과 관련이 있고...6요인은..어시스트,키

# 그렇다면 1요인은 득점에 관여를 많이 하는거니까 "활동성"이라고 이름을 붙일 수 있을것 같고
# 4요인은 나이와 득점에 관련된거니 "노련함"이라 할 수 있을것 같습니다.

#step5 그려보자
biplot(data_prcomp, cex = c(0.6, 0.7))
pc1 <- predict(data_prcomp)[,1] #활동성
pc4 <- predict(data_prcomp)[,4] #노련함
text(pc1, pc4, labels = data_trans_2$Name, 
     cex = 0.7, pos = 3, col = "blue")

#step6
# 차원을 줄인걸로 회귀분석을 해보자.
data.lm <- lm(ppm ~ PC1+PC2+PC3+PC4, family ="binomial", data = as.data.frame(data_prcomp$x))
summary(data.lm)
data.lm.const<-lm(ppm~1,data = as.data.frame(data_prcomp$x))
summary(data.lm.const)
# data.forward<-step(data.lm,scope=list(lower=data.lm.const,upper=data.lm),direction="forward")
# summary(data.forward)
# data.backward<-step(data.lm,scope=list(lower=data.lm.const,upper=data.lm),direction="backward")
# summary(data.forward)
# data.both<-step(data.lm,scope=list(lower=data.lm.const,upper=data.lm),direction="both")
# summary(data.forward)
pred <- predict(data.lm, type="response")
plot(ppm, pred)
abline(a=0, b=1)