function L = Lagrange_Interpol(s,x)
    n = length(x); m = length(s);
    L = ones(n,m);
    for j=1:n
        for i = 1:j-1
            L(j,:) = L(j,:).*(s-x(i))/(x(j)-x(i));
        end
        for i=j+1:n
            L(j,:)=L(j,:).*(s-x(i))/(x(j)-x(i));
        end
    end
end