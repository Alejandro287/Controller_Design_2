
function C1 = lag(g,k)
    gl=g*k;
    [mg1,mf1,wf1,wg1] = margin(gl)
    mg1=20*log10(mg1)
    mf = input('mf >= ');
    %mg = input('mg >= ');
    if mf ~= -1
        p = -180+(mf+6)
        [mag,phase,wout] = bode(gl);
        w_p   = interp1( squeeze(phase), wout, p,'spline')
        mag_p = 20*log10(interp1( squeeze(phase), squeeze(mag), p,'spline'))
        a=10^((-mag_p)/(20));
        T1=(10/(a*w_p));
        C1=tf([a*T1, 1],[T1, 1]);
        K_C1_G=C1*gl;
        disp('a=')
        disp(a)
        disp('T1=')
        disp(T1) 
        [mg,mf,wf,wg] = margin(K_C1_G)
        bode(gl)
        hold on 
        bode(C1)
        hold on 
        bode(K_C1_G)
    end
end



