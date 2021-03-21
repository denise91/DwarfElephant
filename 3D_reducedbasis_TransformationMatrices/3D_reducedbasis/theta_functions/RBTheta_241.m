function out1 = RBTheta_241(mu)
%RBTHETA_241
%    OUT1 = RBTHETA_241(L,H,K_T,L,L_0,R,R_0)

%    This function was generated by the Symbolic Math Toolbox version 8.3.
%    02-Nov-2020 12:33:20
rho_C_t = mu("rho_C_t");
rho_C_b = mu("rho_C_b");
k_b = mu("k_b");
k_t = mu("k_t");
h = mu("h");
d = mu("d");
l_0 = mu("l_0");
r_0 = mu("r_0");
l = mu("l");
r = mu("r");
L = mu("L");

t2 = -h;
out1 = (k_t.*1.0./r_0.^2.*abs(r_0.*(L.*l+l_0.*t2)).*(r.^2+r_0.^2))./(abs(L+t2).*abs(l).*abs(r).*2.0);
