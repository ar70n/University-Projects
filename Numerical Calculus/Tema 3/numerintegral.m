function  [Im,It] = numerintegral(f,a,b,N)

    D = (b-a)/N;
    x = a:D:b
    Im = 0;
    It=0;

    for i = 1:N
        Im = Im + f((x(i)+x(i+1))/2)*D;
        It = It + (f(x(i))+f(x(i+1)))/2*D;
    end

    
end