function [d,k,E]=QRsimple(A, tol, MaxIt)
[m,n]=size(A);
if n~=m; error('Input matrix must be square'); end
if max(max(A-A'))~=0;error('input matrix must be hermitian'); end

if nargin<2
    tol=1e-5;end
if nargin<3
    MaxIt = 100*min(m,100);
end
% Inicializacion de variables
k = 0;
N =  @(A) abs(diag(diag(A))-A); % Funcion que mide los elementos  fuera de la diagonal
E(1) = max(max(N(A)))/mean(abs(diag(A))); % Error inicial en elementos fuera de la diagonal

% Bucle while iterativo
while E(end) > tol && k<=MaxIt
    k=k+1; %Actualizacioncontador de oteraciones
    [Q,R] = GramSchmidtMod(A); % Factorizacion QR
    A = R*Q; % Actualizamos A para la siguiente iteracion
    E(k+1)=max(max(N(A)))/mean(abs(diag(A))); % Actualizamos error
end

% Extreamos la diagonal de A como los autovalores
d = diag(A);
% Los ordenamos por su magnitud
[~,I] = sort(abs(d), 'descend');
d = d(I); % Autovalores ordenados
end