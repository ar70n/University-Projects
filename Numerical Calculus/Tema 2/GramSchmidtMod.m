function [Q,R,Err] = GramSchmidtMod(A)

[n,m]=size(A);
Q=zeros(n,m);
R=zeros(m);
V=A;

for j=1:m
    R(j,j)=norm(V(:,j));
    Q(:,j)=V(:,j)/R(j,j);
    for k =j+1:m
        R(j,k)=A(:,k)'*Q(:,j);
        V(:,k)= V(:,k)-R(j,k)*Q(:,j);
    end

end

%Err=(max(max(abs(Q'*Q-eye(m)))));
Err=norm(Q'*Q-eye(m),'fro');