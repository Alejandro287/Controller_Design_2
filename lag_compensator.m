

function auxx = lag(g)
    
    errpos_min = input('ep <= ')
    errvel_min = input('ev <= ')
    
    syms s
    syms k 
    syms kp
    syms kv
    syms gl
    gl=k*g;
    if errpos_min ~= -1
        
        [num,den]=numden(gl);
        den=subs(den,s,0);

        if den == 0 
            disp ('kp = inf    and     ep = 0')
        else
            kp=subs(gl,s,0);
            k=solve(abs(1/(1+kp))*100 == errpos_min  ,k);
            disp (['k = ',k])
        end
    end
    
    if errpos_vel ~= -1
        syms s
        syms aux
        aux=s*gl;
        [num,den]=numden(aux);
        den=subs(den,s,0);
        if den == 0 
            disp ('kv = inf    and     ev = 0')
        else
            kv=subs(aux,s,0);
            k=solve(abs(1/kv)*100 == errvel_min,k);
            disp (['k = ',k])
        end
    end
    
    k = input('k = ')
    auxx=0;

end