x = [-3, 0, 4, 5, 6,7,8,5,5,11, 12];
s = -3:0.1:12;
y = 100*rand(1, length(x));

L = Lagrange_Interpol(s,x);
P= y*L;
figure
plot(s,P); hold on
plot(x,y,'r*')

%%
% Ejemplo nodos chevychev
