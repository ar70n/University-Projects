A=double(uint8(100*rand(4)));
A=tril(A)

b=double(uint8(100*rand(4,1))) 

y=ltrs(A,b) %Resuelvel sistema

A*y-b %Comprobamos
%%
A=double(uint8(100*rand(4)));
A=triu(A)

b=double(uint8(100*rand(4,1))) 

y=utrs(A,b) %Resuelve el sistema

A*y-b %Comprobamos
%%

A=double(uint8(100*rand(4)));

[L,U]=LU(A);

L
U

L*U-A
%%
A=double(uint8(100*rand(4)));

z=A\b

x=resuelvesistema(A,b)
%%

A=double(uint8(100*rand(4)));
[P,L,U]=PLU(A);
P
L
U
P*A-L*U
%%
format long
A=[[1,1,3];[2,2+2^(-51),22];[0,1,2]]
[L,U]=LU(A);
L*U-A

[P,L,U]=PLU(A);
P*A-L*U
