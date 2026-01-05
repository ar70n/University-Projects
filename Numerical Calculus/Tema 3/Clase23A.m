% Ejemplos de interpolacion de Lagrange

x = [-3 -2.5 -2 0 4 5 6 7 8 5.5 11 11.5 12];
s = -3:0.1:12;
y = 10*rand(1,length(x));

L = Lagrange_Interpol(s,x);
P=y*L;

figure
plot(s,P); hold on
plot(x,y,'r*');


%%

clear all; clf

% Ejemplos nodos Chebyshev

% Numero de nodos
N = 10;

% Nodos equiespaciados
xe = linspace(-1,1,N);
ye = 1./(1+25*xe.^2);

% Nodos de Chebyshev
xc = cos((2.*(1:N)-1)*pi/(2*N));
yc = 1./(1+25*xc.^2);


% Evaluacion de los polinomios interpoladores en un vector s
s = linspace(-1,1,1000);
Le = Lagrange_Interpol(s,xe);
Lc = Lagrange_Interpol(s,xc);

% Construccion del polinomio interpolador de Lagrange
Pe = ye*Le;
Pc = yc*Lc;


% GRAFICAMOS
plot(s, Pe, 'r-', 'DisplayName', 'Equiespaciados')
hold on;
plot(s, Pc, 'b-', 'DisplayName', 'Chebysev')
plot(s, 1./(1+25*s.^2), 'k--', 'DisplayName', 'Funcion Original');
xlabel('x'); ylabel('f(x)');
legend show;

%%
clc; clear all
x = [-3 0 1 2.5 4 12];
y = 10*rand(length(x),1);
V = fliplr(vander(x));
a = solveQR(V,y);

s = -3:0.1:12;
N = length(a);
for j=1:length(s)
    p(j) = a(N);
    for n=N-1:-1:1
        p(j) = a(n) +s(j)*p(j);
    end
end

plot(s,p); hold on
plot(x,y,'r*');
