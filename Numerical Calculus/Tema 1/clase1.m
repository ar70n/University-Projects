% Ejerjcicio 2
% a)
err=1;
i=0;
resultado=0;
x=27;
errores=[];
while err>10^-5
   
    resultado = resultado + (-1)^i*x^(2*i+1)/factorial(2*i+1);
    err = abs(sin(x)-resultado);
    i=i+1;
    errores(i)=abs(resultado-sin(x));

end

% Plot de la evolvuion del error frente a las iteraciones

plot(1:i,errores,'b-o');
title('Evolvuion del error frente a las iteraciones');
xlabel('Num iteraciones')
ylabel('Error')
grid on

%%
% b)
%Mejora del algoritmo
clc
x=27;
x=mod(x+pi,2*pi)-pi; %Reduce x al intervale [-pi,pi]
if abs(x) > pi/2
    if x<0
        x=-(pi+x);
    else 
        x=pi-x;
    end
end

y=0;
i=0;
errores=[];
while abs(y-sin(x))> 10^-5
    y=y+(-1)^i*x^(2*i+1)/factorial(2*i+1);
    i=i+1;
    errores(i)=abs(y-sin(x));

end

plot(1:i,errores,'b-o');
title('Evolvuion del error frente a las iteraciones');
xlabel('Num iteraciones')
ylabel('Error')
grid on

%%
% Ejercicio 3

x=10^-16;

if abs(x)<10^-15

    f = 1 + x^2/factorial(3);
else
    f = (exp(x)-exp(-x))/2*x;
end
disp(f);

%%
clear all
clc

f1= @(x) 2*x-4;
figure;
fplot(f1,[0,3]);
[c1,n1,E1_1,E2_1] = bisection(f1,0,3,10^-5,10^-5,100);
hold on
plot(c1,f1(c1),'ro');
grid on;
%%
close all; clear all; clc
f2=@(x) x^3*sin(x);
figure;
fplot(f2,[3,10])
grid on
[c2,n2,E1_2,E2_2] = bisection(f2,3,10,10^-5,10^-5,100);
hold on;
plot(c2,f2(c2),'ro');