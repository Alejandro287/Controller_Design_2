


function C = lag_lead_wmax(g,k)

    gl=g*k;
    [mg1,mf1,wf1,wg1] = margin(gl);
    mf = input('mf >= ');
    %mg = input('mg >= ');
   
    [mag,phase,wout] = bode(gl);
    p=-(180+(70-mf));
    wg1 = interp1( squeeze(phase), wout, p,'spline')
    [mag,phasee] = bode(gl,wg1);
    mf1=180-abs(phasee);
    phi=mf-mf1;

    campana = 70;
    b = (1+sin((campana*pi)/180))/(1-sin((campana*pi)/180));
    T2=(1)/((sqrt(b))*wg1);
    C2=tf([b*T2, 1],[T2, 1]);

    [mag,phase] = bode(C2*gl,wg1);
    magt=20*log10(mag);
    bode(C2*gl)
    hold on

    if magt > 0
        [mag,phase,wout] = bode(gl);
        p=-(180+(70-mf))+5.2;
        wg2 = interp1( squeeze(phase), wout, p);

        [mag,phase] = bode(C2*gl,((wg1+wg2)/2));
        magt=20*log10(mag);

        a=10^(-magt/20);
        T1=(20/(a*wg2));
        C1=tf([a*T1, 1],[T1, 1]);
    else
        a=-1;
        T1=-1;
        C1=tf(1);
    end
    
    if campana > 70 
        disp('Campana supera 70°') 
    end
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