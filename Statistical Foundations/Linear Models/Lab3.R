#Linear Models
library(MASS)
names(hills)<-c("distance","height.climbed","record")
attach(hills)
out<-lm(record~distance)
summary(out)
plot(distance,record)
abline(out)
out<-lm(record~distance+height.climbed)
summary(out)
out$fitted.values
residuals=record-out$fitted.values
summary(residuals)

#Central limit theorem
data<-rexp(1000,rate=1/5)
hist(data, freq=FALSE, breaks = 20)
x<-0:40
y<-dexp(x,rate=1/5)
lines(x,y)

#Exercise 1
mean(data)
sd(data)
median(data)
IQR(data)

#Exercise 2
#The theoretical mean of the exp distribution is in this case 5, the sd is 5 as well
# For the theoretical median we calculate the probability of P(X<=x)=1/2 where X~Exp(1/5)
qexp(0.5,rate=1/5) #This returns the value of x such that P(X<=x)=1/2 where X~Exp(1/5)
qexp(3/4,rate=1/5)-qexp(1/4, rate = 1/5) #IQR = Q3-Q1


data50<-matrix(rexp(1000*50,rate=1/5),nrow=1000,ncol=50)
plot(data)
hist(data50[,1])
meantime<-rowMeans(data50) #Mean of each bank (row)

#Exercise 3
hist(meantime,freq=FALSE)
x<-seq(2,8,0.1)
y<-dnorm(x,mean=mean(meantime),sd=sd(meantime))
lines(x,y)

#Exercise 4
