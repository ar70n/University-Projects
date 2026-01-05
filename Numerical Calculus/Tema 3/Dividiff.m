function DF = Dividiff(f,s) 
    s = s(:);
    if isa(f, 'function_handle')
        F=f(s);
    else
        F=f;
    end

    n = length(s);
    DF = zeros(n);
    DF(:,1) = F(:);

   % DF(2:n,2) = (DF(2:n,1) - DF(1:n-1,1))./(s(2:n)-s(1:n-1));
    for i=2:n
        DF(i:n,i) = (DF(i:n,i-1) - DF(i-1:n-1,i-1))./(s(i:n)-s(1:n-i+1));
        
    end