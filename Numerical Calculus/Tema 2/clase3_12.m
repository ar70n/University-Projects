v=double(uint8(100*rand(1,10)));
k=10;
a=[];
for i=1:k
    a(i)=norm(v,i);
end
plot(a)
%%
% Ejemplo 1

n=3;
A=rand(n)+(n-1)*eye(n);
b=[-1;2;3];
tol=1e-5;
maxN=100;

[x,N,errj]=jacobi(A,b,tol,maxN);
disp('Solucion por jacobi');
disp(x);

[x,N,errgs]=gauss_seidel(A,b,tol,maxN);
disp('Solucion por gauss-seidel');
disp(x);


dif = errgs-errj(1:length(errgs));
plot(dif)
%%
tol=1e-5;
beta=(5+sqrt(21))/2;
A=[1, 1,2;beta,1,1;-5/2,1/beta,1];
b=A*[1;1;1];

[x,N,errj]=jacobi(A,b,tol,maxN);
disp('Solucion por jacobi');
disp(x);

[x,N,errgs]=gauss_seidel(A,b,tol,maxN);
disp('Solucion por gauss-seidel');
disp(x);

plot(errj);
%%
tol=1e-5
for k=50:200
    maxN=100*k;
    A=rand(k)+(k-1)*eye(k);
    b=rand(1,k);
    [x,N,errj]=jacobi(A,b,tol,maxN);
    [x,N,errgs]=gauss_seidel(A,b,tol,maxN);
end
