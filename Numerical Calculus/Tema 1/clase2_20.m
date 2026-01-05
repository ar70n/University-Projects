f= @(x)x^2-2;


[x,N,res] = pfix(f,0.5,1e-4,100,2,2);
%%
g = @(x)sqrt(x+2);


[x,N,res] = pfix(g,0.5,1e-4,100,2,2);

%%
h=@(x)2*x^3+4/3*x-1

[x, N, res1, res2] = Secante(h, 1, 2, 1e-4, 1e-4, 100);

%%

h=@(x)2*x^3+4/3*x-1;
dfdx=@(x)6*x^2+4/3;
[x, N, res1, res2] = Newton(h, dfdx, 2, 1e-4, 1e-4, 100)
%%
f=@(x)x^7-5* x^4+3*x-2

[x, N, res1, res2] = Secante(f, 1, 2, 1e-4, 1e-4, 100)
%%


f=@(x)x^7-5* x^4+3*x-2;
dfdx=@(x)7*x^6-20*x^3+3;

[x, N, res1, res2] = Newton(f, dfdx, 2, 1e-4, 1e-4, 100)
%%
A=double(uint8(100*rand(4)))
b=double(uint8(100*rand(4,1)))

L=tril(A)

ltrs(L,b)
%%
clc
clear all
close all