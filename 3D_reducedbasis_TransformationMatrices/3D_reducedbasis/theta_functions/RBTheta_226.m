function out1 = RBTheta_226(mu)
%RBTHETA_226
%    OUT1 = RBTHETA_226(L,H,K_T,L,L_0,R,R_0)

%    This function was generated by the Symbolic Math Toolbox version 8.3.
%    02-Nov-2020 12:33:17
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

t2 = L.*l;
t3 = h.*l_0;
t4 = -t3;
t5 = t2+t4;
out1 = -(k_t.*1.0./r_0.^2.*t2.^2.*1.0./t5.^2.*1.0./abs(r).^2.*abs(r_0).^2.*abs(t5).*(r-r_0).^2)./(abs(l).*abs(L-h));
