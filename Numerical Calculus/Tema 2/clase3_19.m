%Clase 19/03/2024

A=rand(4)
orth(A)
[Q,R]=qr(A)


A(4,:)=A(3,:)
orth(A)
%%
B=[1,0,1;1 2 3;0 1 0];
[Q,R,Err]=GramSchmidt(B)

[Q,R]=qr(B)

%%
N=1000;
A=rand(N);
tic 
[Q,R,Err] = GramSchmidt(A);

toc 
tic
[Q2,R2]=qr(A);
toc
%%

N=1000;
A=rand(N);
tic 
[Q,R,Err] = GramSchmidt(A);

toc 
tic
[Q2,R2,Err2]=GramSchmidtMod(A);
toc

format long

Err
Err2
%%

format short
A=floor(100*rand(5));
b=floor(100*rand(5,1));
x=SolveQR(A,b);
y=resuelvesistema(A,b)

%Aqui compara los errores de resolver un sistema mediante LU y mediante QR

%%

A=floor(100*rand(5,4));
b=floor(100*rand(5,1));

x=SolveQR(A,b)
