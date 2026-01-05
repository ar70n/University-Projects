function x = resuelvesistema(A,b)
[L,U]=LU(A);

y=ltrs(L,b);
x=utrs(U,y);

end