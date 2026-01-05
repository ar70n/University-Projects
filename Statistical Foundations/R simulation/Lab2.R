#Using Scripts
x<-rnorm(100)
hist(x)

#Exercise
x<-rnorm(1000, sd = 3)
hist(x^2)

s#Writing functions
plothistwithpdf<-function(n=100,mu=0,sigma=1){
  x<-rnorm(n,mean=mu,sd=sigma)
  hist(x,freq=FALSE)
  xval<-seq(min(x),max(x),length.out=100)
  pdf<-dnorm(xval,mean=mu,sd=sigma)
  lines(xval,pdf,col='blue')
  out<-list(xbar=0,s=0)
  out$xbar<-mean(x)
  out$s<-sd(x)
  out
}

ans<-plothistwithpdf(100,0,3)
ans

#Exercise 
histwithnorm<-function(c){
  n <- length(x)
  mu_mle <- mean(x)
  sigma_mle <- sd(x)
  hist(x, freq = FALSE)
  xval<-seq(min(x),max(x),length.out=100)
  pdf<-dnorm(xval,mean=mu_mle,sd=sigma_mle)
  lines(xval,pdf,col='blue')
  out<-list(mu_mle,sigma_mle)
  out
}

histwithnorm(x)

#The for loop
for (i in 1:10){
  x<-rnorm(100)
  xbar<-mean(x)
  print(xbar)
}
x<-rep(0,100)
for (i in 1:100){
  x[i]<-rnorm(1,i,1)
}

#Exercise 
x<-rep(0,100)
for (i in 1:100){
  x[i]<-sum(1:i)
}

#The if statement
u<-runif(1)
p<-0.3
if(u<p) {head<-1} else {head<-0}
print(head)

#Exercise
  u<-runif(1)
  if (u<1/6) {
    result<-1
  } else if(u<2/6){
    result<-2
  } else if (u<3/6){
    result<-3
  } else if (u<4/6){
    result<-4
  } else if (u<5/6){
    result<-5
  } else {
    result<-6
  }

print(result)

#Exercise
vec<-runif(100)
j=0
for (i in 1:100){
  if (vec[i]<0.5){
    j = j+1
  }
}
print(j)

#The while loop
u<-0
t<-0
while (u<=0.9){
  t<-t+1
  u<-runif(1)
}
print(t)


#Exercise
sum=0
i=0
while(sum<50){
  x<-runif(1)
  sum=sum + x
  i=i+1
}
print(i)

#Using functions
sinc <- function(x){
  if (abs(x) > 1) {
    ## x not near 0: calculate in the obvious way.
    s <- sin(x)/x
  }
  else {
    ## x too close to 0: use power series instead.
    s <- 1
    term <- 1
    for( j in seq(3,100,by=2) ) {
      term <- term*(-x*x)/(j*(j-1))
      s <- s+term
      if(abs(term) < 1.e-10) break
    }
  }
  ## Return the value of s
  s
}
sinc(0.01)

#Exercise
sample_mean_sd<-function(vec){
  mean = 0
  for (i in 1:length(vec)){
    mean = mean + vec[i]
    i = i +1
  }
  mean = mean / length(vec)
  
  sd = 0
  for (i in 1:length(vec)){
    sd = sd + (vec[i]-mean)^2
    i = i +1
  }
  sd = sqrt(sd/(length(vec)-1))
  
  return(list(mean = mean, sd = sd))
}
x<-rnorm(100)
sample_mean_sd(x)
mean(x)
sd(x)

#Simulation
#Exercise 1
x<-rgamma(10000,5)
hist(x)

#Exercise 2
x<-rnorm(10000)
qqnorm(x)
qqline(x)

#Exercise 3
x<-rnorm(10000)
y<-rt(10000,3)
qqplot(x,y)
qqplot(y,x)
#In the qqplot(y,x) we can see some kind of arctan
#La t-student con pocos grados de libertad tiene más probabilidad en las colas que la distribución Normal estándar.

#Exercise 4
x<-rnorm(10000)
y<-rt(10000,100)
qqplot(x,y)
qqplot(y,x)

#We see a straight line because t-students coverges to normal

#Exercise 
x<-rnorm(10000,3,5)
y<-rgamma(10000,shape=4,rate=2)
z<-x/y

hist(x)
hist(y)
hist(z)

mean(z)
var(z)

w<-z^2
hist(w)
mean(x < y) # P(x<y)

#Optimisation
#Exercise

log.lik.gamma <- function(theta, x) {
  
  alpha <- theta[1]
  beta <- theta[2]
  n <- length(x)
  
  res <- n*alpha*log(beta) - n*log(gamma(alpha)) + (alpha-1)*sum(log(x)) - beta*sum(x)
  return(res)
  
}

# create a grid for alpha and beta values
alpha.values <- seq(3,5,len=100)
beta.values <- seq(1,3,len=100)

# simulate some data to play with
dataset <- rgamma(100, 4, 2) 

# create a matrix whose (i,j)th element will store the value of the log-likelihood for the ith
# value of the alpha.values vector and the jth value of the beta.values vector.
loglik.mat <- matrix(NA, nrow=length(alpha.values), ncol=length(beta.values))
for (i in 1:length(alpha.values)){
  for (j in 1:length(beta.values)) {
    loglik.mat[i,j] <- log.lik.gamma(c(alpha.values[i], beta.values[j]), dataset)
  }
}
image(alpha.values, beta.values, loglik.mat)
contour(alpha.values, beta.values,loglik.mat, add=TRUE)
points(4,2,cex=2, pch=16) # plot the true value of the parameters. The loglik function should be close to that value


# find the MLE using optim
res <- optim(c(1,1), log.lik.gamma, x=dataset, control=list(fnscale=-1))
res
res$par # MLEs should be close to the true values (i.e. 4 and 2)

