function [L,k] = powerit(A,tol,MaxIt)
[m,n] = size(A);

if m~=n
    error('Input matrix must be square')
end
if max(max(A-A'))~=0
    error('Input matrix must be symmetric')
end
if nargin<2
    tol=1e-8;
end
if nargin<3
    MaxIt = 10*min(n,100)
end
%Inicializamos las variables

initKer = 0
while initKer<100*eps
    v=rand(m,1);
    initKer= max(A*v)/max(v);
end
k=0; E=1; L0=v'*A*v;
while E> tol && k<=MaxIt
    k=k+1; %Incremenmtamos contador de iteraciones
    v=A*v; %Aplicamos la matriz vector
    v=v/norm(v); %Normalizamos el vector
    L = v'*A*v; % Calculamos el cociente de Rayleigh
    E=abs(L-L0)/abs(L); %Calculamos el error relativo
    L0=L; %Actualizamos la anterior estimacion
end 
end
