


function C2 = lead(g,k,paso)

    warning('off','all')
    
    gl=g*k;
    [mg1,mf1,wf1,wg1] = margin(gl)
    mg1=20*log10(mg1)
    mf = input('mf >= ');
    %mg = input('mg >= ');
    phi=mf-mf1
    
    for theta=0:paso:100
        
        campana = phi + theta;
        b = (1+sin((campana*pi)/180))/(1-sin((campana*pi)/180));
        gain = -10*log10(b);
        gain = 10^(gain/20);
        [mag,phase,wout] = bode(gl);
        new_wg2 = interp1( squeeze(mag), wout, gain,'spline');
        fase2 = interp1( squeeze(mag), squeeze(phase), gain,'spline');
        mf2=180-abs(fase2);
        T2=(1)/((sqrt(b))*new_wg2);
        C2=tf([b*T2, 1],[T2, 1]);
        [mgf,mff,wff,wgf] = margin(C2*gl);
        if  campana > 70
            disp('Campana supera 70°') 
        elseif mff >= mf  
            break;   
        end
    end
    disp('theta=')
    disp(theta)
    disp('campana=')
    disp(campana)
    disp('b=')
    disp(b)
    gain = -10*log10(b)
    disp('fase2=')
    disp(fase2)
    disp('new_wg2=')
    disp(new_wg2)
    disp('mf2=')
    disp(mf2)
    disp('t2=')
    disp(T2)
    [mgf,mff,wff,wgf] = margin(C2*gl)
    mgf=20*log10(mgf)
    K_C2_G=C2*gl;
    bode(gl)
    hold on 
    bode(C2)
    hold on 
    bode(K_C2_G)
end

