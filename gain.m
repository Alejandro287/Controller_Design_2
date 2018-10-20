

function [] = gain(g)

    gl=g;
    [mg1,mf1,wf1,wg1] = margin(gl);
    mf = input('mf >= ');
    mg = input('mg >= ');
    wg = input('wg >= ');
    
    if mf ~= -1
        p = -(180-mf);
        [mag,phase,wout] = bode(gl);
        w_p   = interp1( squeeze(phase), wout, p);
        mag_p = 20*log10(interp1( squeeze(phase), squeeze(mag), p));
        k=10^(-mag_p/20);
        disp('k = ')
        disp(k)
    end
    
    if mg ~= -1
        dmg=mg-20*log10(mg1);
        k=10^(-dmg/20);
        if k < 1
            disp('k <= ')
            disp(k)
        else
            disp('k >= ')
            disp(k)
        end
    end
    
    if wg ~= -1
        [mag,phase]=bode(gl,wg);
        mag=20*log10(mag);
        k=10^(-mag/20);
        disp('k = ')
        disp(k)
    end
end