function out1 = RBTheta_52(mu)
%RBTHETA_52
%    OUT1 = RBTHETA_52(L,D,H,K_T,L,L_0,R,R_0)

%    This function was generated by the Symbolic Math Toolbox version 8.3.
%    02-Nov-2020 12:32:43
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

t2 = L.*r;
t3 = d.*r_0;
t4 = -d;
t5 = -t3;
t6 = L+t4;
t7 = t2+t5;
out1 = -(h.*k_t.*r.^2.*t6.*1.0./t7.^2.*abs(t7).*(l-l_0))./(l.*abs(r).*abs(t6));
