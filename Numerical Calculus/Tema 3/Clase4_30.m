v = -3:2;

v(randperm(6))';


f = @(x) 1./(1+x.^2);
DF = Dividiff(f,v); DF(6,6);

DF = Dividiff(f,v(randperm(6)))
DF(6,6);

%%
f = @(x) 1./(1+x.^2);
s = -5:0.5:5;
x = -5:0.01:5;
s = -5:5;
P = polinewton(f,s,x);

%%

f = @(x) exp(-x.^2);
[Im,It] = numerintegral(f,-4,4,1000);
Im^2
It^2
