function [Q,R] = Householder(A)


[m,n] = size(A);
Q=eye(m);
R=A;
for k=1:n
    x=R(k:m,k); %Construir el vector X
    e = zeros(size(x)); e(1)=1;
    % Calculamos el vector v para la 
    % transformacion de HouseHolder
    v = sign(x(1))*norm(x)*e+x;
    v=v/norm(v);
    % Aplicamos la transformacion de HouseHolder a R y Q
    R(k:m,k:n) = R(k:m,k:n)-2*v*(v'*R(k:m,k:n));
    Q(:,k:m)=Q(:,k:m) -2* (Q(:,k:m)*v)*v';
end
%Asegurar que R sea tranigular superior
R=triu(R);


end