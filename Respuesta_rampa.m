s=tf('s');
G=50/(s*(s/5+1));
K=5;
C2=(1+0.048916*s)/(1+0.005505*s);
K_C2_G=K*C2*G;
Go=feedback(K_C2_G,1);

t=0:0.0001:1;
r=t;
[y,t]=lsim(Go,r,t);
plot(t,-y+(r'))
title('\fontsize{16}Resta de entrada tipo rampa unitaria y respuesta del sistema en lazo cerrado a esta entrada')
xlabel('\fontsize{12}Tiempo [segundos]')
ylabel('\fontsize{12}Amplitud')

figure 
pzmap(Go)