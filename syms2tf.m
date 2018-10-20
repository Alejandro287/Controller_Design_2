

function G = syms2tf(g)
    [n,d]=numden(g);
    num=sym2poly(n);
    den=sym2poly(d);
    G=tf(num,den);
end