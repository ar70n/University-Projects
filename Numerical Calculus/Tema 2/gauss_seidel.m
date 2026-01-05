function [x,N,err] = gauss_seidel(A,b,tol,maxN)
% Método de Gauss-Seidel para aproximar la solucion de
% Ax=b

n = length(A);
x = zeros(n,1);
xnew = zeros(n,1);
N=0;
err=[];
while N<maxN
    for i=1:n
        xnew(i)=(b(i)-A(i,1:i-1)*xnew(1:i-1)-A(i,i+1:n)*x(i+1:n))/A(i,i);
    end
    err(N+1) = norm(xnew-x,Inf);
    N=N+1;
    if err(end)<tol
        break;
    end
    x=xnew;



end

disp(['Iteraciones (GS): ' num2str(N)]);
if N==maxN
    disp('No se logro la convergencia en el numero maximo de iteraciones');
end

end
