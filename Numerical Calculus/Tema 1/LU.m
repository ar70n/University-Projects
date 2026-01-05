function [L,U] = LU(A)
[n,m]=size(A);
if n~=m
    error('La matriz A no es cuadrada')
end

%Inicializacion 
L=eye(n); U=A;

for k=1:n-1
    if U(k,k)==0
        error('La matriz no es singular y no se puede factorizar')
    end
    for j=k+1:n
        L(j,k) = U(j,k) / U(k,k);
        U(j,k:n) = U(j,k:n)-L(j,k)*U(k,k:n);
    end
end
end