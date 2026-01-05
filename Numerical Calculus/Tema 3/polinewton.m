function P = polinewton(f,s,x)
    DF = Dividiff(f,s);
    df = diag(DF);
    n=length(s);
    N = ones(n,1);
    P = df(1)*N;
    for k=2:n
        N = N.*(x-s(k-1));
        P = P + df(k)*N;
        
    end

    plot(x,f(x),'k'); hold on; plot(x,P,'b');

end