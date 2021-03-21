function out1 = RBTheta_248(mu)
%RBTHETA_248
%    OUT1 = RBTHETA_248(K_B,L,L_0,R,R_0)

%    This function was generated by the Symbolic Math Toolbox version 8.3.
%    02-Nov-2020 12:33:22
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

out1 = (k_b.*l.^2.*1.0./l_0.^2.*abs(l_0).*1.0./abs(r).^2.*abs(r_0).^2)./abs(l);
