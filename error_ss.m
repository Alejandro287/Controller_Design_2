function [] = error_ss(g)

    warning('off','symbolic:solve:TooManyVars')
    g=zpk(g);
    
    [num,den] = tfdata(g);
    syms s
    g = poly2sym(cell2mat(num),s)/poly2sym(cell2mat(den),s);
    
    errpos_min = input('ep <= ');
    errvel_min = input('ev <= ');
    
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
            k=solve(abs(1/(1+kp))*100 == errpos_min,k>0,k);
            disp ('k = ')
            disp(k)
        end
    end
    
    if errvel_min ~= -1
        syms s
        syms aux
        aux=s*gl;
        [num,den]=numden(aux);
        num=collect(num,s);
        den=collect(den,s);
        den=subs(den,s,0);
        if den == 0 
            disp ('kv = inf    and     ev = 0')
        else
            aux=num/den;
            kv=subs(aux,s,0)
            k=solve(abs(1/kv)*100 == errvel_min,k>0,k);
            disp ('k = ')
            disp(k)
        end
    end

end