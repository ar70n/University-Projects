clear;clc;

n = 3; m = 5;

A = floor(10*rand(m,n));
b = floor(10*rand(m,1)); 

[xMC, res]= SolveQR(A,b);
xMC
norm(xMC)
y=A\b
norm(y)
res
%%

clear;clc;

n = 3; m = 5;

A = floor(10*rand(m,n));
b = floor(10*rand(m,1)); 

[xMC, res]= SolveSVD(A,b);
xMC
norm(xMC)
y=A\b
norm(y)
res

%%
clear; clc;

A = floor(1.001*rand(1000));
sum(sum(A));
sum(sum(A==1))/sum(sum(A==0));
[U,S,V] = svd(A);
s = diag(S);
plot(s)
s(1000)
%%

A = floor(100*rand(1000,800));
[U,S, V] = svd(A);
s=diag(S);
plot(s)

%%

A = rand(200,100); 
tic
[Q,R] = GramSchmidtMod(A);
toc
tic
[Qh,Rh] = Householder(A);
toc

res1=norm(A-Q*R);
res2 = norm(A-Qh*Rh);
