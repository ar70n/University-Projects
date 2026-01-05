function [P,L,U] = PLU(A)
[n,m]=size(A);
if n~=m
    error('La matriz A no es cuadrada')
end

%Inicializacion 
P=eye(n);
L=eye(n);
U=A;

for k=1:n-1
    [M,I] = max(abs(U(k:n,k)));

    %Pivotaje

    if I~=1
        r= I+k-1; %Esto nos da la poscion real del maximo en U
        %Permutamos las filas en U y L
        %aux = U(k,:);U(k,:)=U(r,:); U(r,:)=aux Forma poco eficiente 

        U([k,r],k:n)=U([r,k],k:n);
        L([k,r],1:k-1)=L([r,k],1:k-1);
        P([k,r],:)=P([r,k],:);
    end

        

    if U(k,k)==0
        error('La matriz no es singular y no se puede factorizar')
    end
    for j=k+1:n
        L(j,k) = U(j,k) / U(k,k);
        U(j,k:n) = U(j,k:n)-L(j,k)*U(k,k:n);
    end
end
end