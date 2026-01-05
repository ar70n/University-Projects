function [x,N,err] = jacobi(A,b,tol,maxN)
% Método de Jacobi para aproximar la solucion de
% Ax=b

n = length(A);
D=diag(A);
R=A-diag(D);
x = zeros(n,1);
xnew = zeros(n,1);
N=0;
err=[];
while N<maxN
    xnew=(b-R*x)./D;
    err(N+1) = norm(xnew-x,Inf);
    x=xnew;
    N=N+1;
    if err(end)<tol
        break;
    end


end

disp(['Iteraciones (J): ' num2str(N)]);
if N==maxN
    disp('No se logro la convergencia en el numero maximo de iteraciones');
end

end
