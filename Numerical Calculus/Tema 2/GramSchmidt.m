function [Q,R,Err] = GramSchmidt(A)

[n,m]=size(A);
Q=zeros(n,m);
R=zeros(m);

Q(:,1)=A(:,1)/norm(A(:,1));

for k=2:m
    v=A(:,k);
    for j =1:k-1
        R(j,k)=A(:,k)'*Q(:,j);
        v= v-R(j,k)*Q(:,j);
    end
    R(k,k)=norm(v);
    Q(:,k)=v/R(k,k);
end

%Err=(max(max(abs(Q'*Q-eye(m)))));
Err=norm(Q'*Q-eye(m),'fro');