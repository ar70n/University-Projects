%Ejemplo resolucion sistema determinaod por QR
%solucion exacta

A = floor(100*rand(3))
b = floor(100*rand(3,1))

x = SolveQR(A,b)
%%

% Ejemplos resolucion sistma no compatible por QR
% Minimos cuadrados

A = floor(100*rand(3,2))
b = floor(100*rand(3,1))
x=SolveQR(A,b);
%%
% Ejemplo de aplicacion de power iteration para estimar 

clear; clc;
A=rand(100); A=A'*A;
[L,k] = powerit(A);
eig(A);
%%
% Ejemplo de aplicacion de QR simple para estimar autoavlores
clear; clc; 
A=rand(100); A=A'*A;
[d,k,E]=QRsimple(A);
c=sort(abs(eig(A)),'descend')
max(c-d)
k
plot(E)

%%
clc;
A=rand(4); A=A'*A;

[Q1,R1] = GramSchmidt(A);
[Q2,R2] = GramSchmidt(A);
R1-R2


