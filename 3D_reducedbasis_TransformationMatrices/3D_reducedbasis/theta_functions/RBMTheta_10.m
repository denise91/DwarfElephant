function out1 = RBMTheta_10(mu)
%RBMTHETA_10
%    OUT1 = RBMTHETA_10(L,D,R,R_0,RHO_C_T)

%    This function was generated by the Symbolic Math Toolbox version 8.3.
%    02-Nov-2020 12:32:51
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

t2 = -d;
out1 = (rho_C_t.*abs(L.*r+r_0.*t2))./(abs(L+t2).*abs(r));
