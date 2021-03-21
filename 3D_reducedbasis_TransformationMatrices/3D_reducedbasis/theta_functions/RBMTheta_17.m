function out1 = RBMTheta_17(mu)
%RBMTHETA_17
%    OUT1 = RBMTHETA_17(L,D,L,L_0,R,R_0,RHO_C_T)

%    This function was generated by the Symbolic Math Toolbox version 8.3.
%    02-Nov-2020 12:33:02
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
out1 = (rho_C_t.*abs(l_0.*r_0.*(L.*r+r_0.*t2)).*1.0./abs(r).^2)./(abs(L+t2).*abs(l));
