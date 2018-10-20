

function G = tf2syms(g)
    [num,den] = tfdata(g);
    syms s
    G = poly2sym(cell2mat(num),s)/poly2sym(cell2mat(den),s);
end