function y =ltrs(L,b)
% Resuelve un sistema de ecuaciones lineales Ly=b
% donde L es una matriz triangular inferior

n = length(b);
y = zeros(n,1);

for i=1:n
    if L(i,i)==0
        error('La matriz es singular');
    end
    y(i)=(b(i)- L(i,1:i-1)*y(1:i-1))/L(i,i);
end
end

