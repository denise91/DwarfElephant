function out1 = RBTheta_162(mu)
%RBTHETA_162
%    OUT1 = RBTHETA_162(L,D,H,K_T,L,L_0,R,R_0)

%    This function was generated by the Symbolic Math Toolbox version 8.3.
%    02-Nov-2020 12:33:05
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

t2 = d.*r_0;
t4 = h.*l_0.*r;
t3 = l.*t2;
t5 = t3+t4;
t6 = 1.0./t5.^2;
out1 = -(k_t.*abs(-t5.*(t2-L.*r)).*1.0./abs(r).^2.*(h.*r.^2.*t6.*(l-l_0).*(d.*l+h.*l_0)+d.*l.^2.*t6.*(t2+h.*r).*(r-r_0)))./(abs(d+h).*abs(l).*abs(L-d));
