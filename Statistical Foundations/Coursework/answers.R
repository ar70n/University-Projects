#Exercise 1
#a)
data<-read.csv("ExperimentData.csv", header = TRUE)
attach(data)

hist(Output, freq=FALSE)

xval<-seq(min(Output),max(Output),length.out=100)
pdf<-dnorm(xval,mean=mean(Output), sd=sd(Output))
lines(xval,pdf,col='blue')

hist(Group)
boxplot(Output~Group)
plot(Group, Output)

hist(Input1)
boxplot(Output~Input1)
plot(Input1, Output)

hist(Input2)
boxplot(Output~Input2)
plot(Input2, Output)

hist(Type)
boxplot(Output~Type)
plot(Type, Output)

hist(Input3)
boxplot(Output~Input3)
plot(Input3, Output)

#(b)
modelo1<-lm(Output~Group + Input1 + Input2 + Type + Input3, data=data)
summary(modelo1)      
plot(modelo1)

modelo2<-lm(Output~ Input1 + Input2 + Type, data=data)
summary(modelo2)

par(mfrow = c(2, 2))
plot(modelo2)

par(mfrow = c(1, 1))

#Exercise 2
#(b)
dataset<-c(0.610, 0.309, 0.578, 0.921, 1.04, 0.820, 1.71, 0.834, 0.852, 1.11)

log.lik.weibull<-function(theta,x){
  if (theta <= 0){
    return(-Inf)
  }
  n<-length(x)
  sum_l = sum(log(x))
  result<-n*log(theta)+(theta-1)*sum_l-sum(x^theta)
  return(result)
}

minus.log.lik.weibull<-function(theta,x){
  -log.lik.weibull(theta,x)
}

t<-optimise(minus.log.lik.weibull, c(0,10), x = dataset)
print(t)

#(c)
#Generate theta values
theta.values<-seq(2.3,2.9, len=100)

# Compute the log-likelihood function for each theta
log_lik_values<-vector(length = length(theta.values))
for (i in 1:length(theta.values)){
  log_lik_values[i]<- log.lik.weibull(c(theta.values[i]), dataset)
}

# Find MLE in data generated
mle_theta <- theta.values[which.max(log_lik_values)]

# Plot log-likelihood
plot(theta.values, log_lik_values, 
     type = "l", 
     lwd = 2,
     col = "blue",
     xlab = expression(theta), 
     ylab = expression(l(theta)),
     main = "Log-likelihood function of Weibull")

# Show MLE in graphic
abline(h= -t[["objective"]], v = mle_theta, col = "red", lwd = 2, lty = 2)
points(mle_theta, max(log_lik_values), col = "red", pch = 16, cex = 1.5)

# Add legend
legend("topright", 
       legend = c(expression(l(theta)), paste("MLE =", round(mle_theta, 3))),
       col = c("blue", "red"),
       lwd = c(2, 2),
       lty = c(1, 2))


#Exercise 3
n<-100000
x<-rnorm(n)
y<-rnorm(n,mean = 1, sd = sqrt(2))
z<-rexp(n, rate = abs(x))
#(a)
mean(sqrt(abs(x/y)))
#(b)
mean(sin(x*y) > 0.5) #P(sin(XY)>0.5)
#(c)
mean(x<z)

