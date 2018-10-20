

function C = lag_lead(g,k,paso)

    gl=g*k;
    [mg1,mf1,wf1,wg1] = margin(gl);
    mf = input('mf >= ');
    %mg = input('mg >= ');
    wg = input('wg = ');
    
    
    [mag,phase] = bode(gl,wg);
    mf1=180-abs(phase);
    phi=mf-mf1;
    
    for theta=0:paso:100
        
        campana = phi + theta;
        b = (1+sin((campana*pi)/180))/(1-sin((campana*pi)/180));
        T2=(1)/((sqrt(b))*wg);
        C2=tf([b*T2, 1],[T2, 1]);
        
        [mag,phase] = bode(C2*gl,wg);
        mag=-20*log10(mag);
        a=10^(mag/20);
        T1=(10/(a*wg));
        C1=tf([a*T1, 1],[T1, 1]);
        [mgf,mff,wff,wgf] = margin(C1*C2*gl);
        if campana > 70 
            disp('Campana supera 70°') 
        elseif mff >= mf
            break;   
        end
    end
    disp('theta=')
    disp(theta)
    disp('b=')
    disp(b)
    disp('t2=')
    disp(T2)
    disp('a=')
    disp(a)
    disp('t1=')
    disp(T1)
    K_C1_C2_G=C1*C2*gl;
    [mgf,mff,wff,wgf] = margin(K_C1_C2_G)
    bode(gl)
    hold on
    bode(C1)
    hold on
    bode(C2)
    hold on
    bode(K_C1_C2_G)
    C=[C1,C2];
end