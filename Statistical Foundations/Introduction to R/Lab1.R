#Execute sequentially
#Exercise 1
x<-dnorm(seq(-5,15,length(10000)), mean=5, sd=2)
plot(x, type="l")

#Exercise 2
y<-rnorm(50,mean=5, sd=2)
hist(y)

#If we increase the number of random observations we get closer to the normal distribution
z<-rnorm(500,mean=5, sd=2)
hist(z, freq = FALSE)

#Exercise 3
lines(seq(-5,15),x)

#Exercise 4
x<-rnorm(500, mean=0, sd=1)
qqnorm(x)
abline(0,1)

#Now we change the mean
x<-rnorm(500, mean=2, sd=1)
qqnorm(x)
abline(0,1)
#translation of the straight line

#Now we change the sd
x<-rnorm(500, mean=0, sd=3)
qqnorm(x)
abline(0,1)
#Change of slope

#Now we change both
x<-rnorm(500, mean=4, sd=3)
qqnorm(x)
abline(0,1)

#Reading in data
library(MASS)
hills
names(hills)<-c("distance", "height.climbed", "record")
hills
pairs(hills)
attach(hills)
distance
plot(distance, record)
identify(distance, record, row.names(hills))
cars.data <- read.csv("Cars.csv", header=TRUE)
attach(cars.data)
table(Type)
boxplot(Price~Type,range=0)
MPG.city>=30
Price[MPG.city>=30]
summary(Price[MPG.city>=30])
Type=="Compact"

#Exercise 1
cars.data <- read.csv("Cars.csv", header=TRUE)
attach(cars.data)
x<-MPG.city[Min.Price>30]
mean(x)
sd(x)

#Exercise 2
plot(Price, MPG.city)
x <- seq(0, 60, length = 100)
lines(x, 50/(x-5)+15)
#We notice that for very expensive cars we have low MPG and for very cheap cars very high MPG

#Exercise 3
Model[max(Max.Price-Min.Price)]

#Exercise 4
hist(MPG.highway)

#Exercise 5
boxplot(MPG.highway~Type)

#Matrices
a.vector <- c(3, 5, 6, 2.5, 100, 27.7)
a.matrix
a.matrix[1,2]
a.matrix[1,]
a.matrix[,2]
a.matrix[1,2:3]
x<-matrix(c(2,4,6,8),nrow=2)
x+10
x*x
x%*%x
data(iris)
x <- iris
y <- x[, 1:4]
z<-as.matrix(y)
A<-t(z)%*%z #transpose matrix
dim(A)
E<-eigen(A,symmetric=TRUE)

#Lists
ans <- list(x=0,y=0,z="")
ans$x <- c(1,2,3,4,5)
ans$y <- c(4,3,2,1)
ans$z <- c("cat","dog")
ans
ans$x
ans[[2]]

#Exercise 1
A<-matrix(c(2,1,0,1,3,1,0,1,2),nrow=3)
B<-c(1,-3,1)
help(solve)
sol<-solve(A,B)
#A%*%sol==B

#Exercise 2
E<-eigen(A)
E
