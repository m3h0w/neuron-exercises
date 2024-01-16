from neuron import h # type: ignore
from neuron.units import ms, mV # type: ignore
import matplotlib.pyplot as plt

# TITLE Calcium T channel for Subthalamic Nucleus

# UNITS {
#     (mV) = (millivolt)
#     (mA) = (milliamp)
# }

# NEURON {
#     SUFFIX CaT
#     USEION ca READ eca WRITE ica
#     RANGE gmax
# }

# PARAMETER {
#     gmax  = 0.002 (mho/cm2)
# }

# ASSIGNED { 
#     v (mV)
#     eca (mV)
#     ica (mA/cm2)
#     ralpha (/ms)
#     rbeta (/ms)
#     salpha (/ms)
#     sbeta (/ms)
#     dalpha (/ms)
#     dbeta (/ms)
# }

# STATE {
#     r s d
# }

# BREAKPOINT {
#     SOLVE states METHOD cnexp
#     ica  = gmax*r*r*r*s*(v-eca)
# }

# INITIAL {
#     settables(v)
#     r = ralpha/(ralpha+rbeta)
#     s = (salpha*(dbeta+dalpha) - (salpha*dbeta))/
#               ((salpha+sbeta)*(dalpha+dbeta) - (salpha*dbeta))
#     d = (dbeta*(salpha+sbeta) - (salpha*dbeta))/
#               ((salpha+sbeta)*(dalpha+dbeta) - (salpha*dbeta))
# }

# DERIVATIVE states {  
#     settables(v)      
#     r' = ((ralpha*(1-r)) - (rbeta*r))
#     d' = ((dbeta*(1-s-d)) - (dalpha*d))
#     s' = ((salpha*(1-s-d)) - (sbeta*s))
# }

# UNITSOFF

# PROCEDURE settables(v (mV)) {
#     LOCAL  bd
#     TABLE ralpha, rbeta, salpha, sbeta, dalpha, dbeta 
#           FROM -100 TO 100 WITH 200

#     ralpha = 1.0/(1.7+exp(-(v+28.2)/13.5))
#     rbeta  = exp(-(v+63.0)/7.8)/(exp(-(v+28.8)/13.1)+1.7)

#     salpha = exp(-(v+160.3)/17.8)
#     sbeta  = (sqrt(0.25+exp((v+83.5)/6.3))-0.5) * 
#                      (exp(-(v+160.3)/17.8))

#     bd     = sqrt(0.25+exp((v+83.5)/6.3))
#     dalpha = (1.0+exp((v+37.4)/30.0))/(240.0*(0.5+bd))
#     dbeta  = (bd-0.5)*dalpha
# }

# UNITSON


h.load_file("stdrun.hoc")
# h.load_file("kinetics.hoc")
# h.load_file('mosinit.hoc')

soma = h.Section(name = "soma")
soma.nseg = 1
soma.L = 18.8
soma.diam = 18.8
soma.Ra = 123
soma.insert("hh")
soma.insert("CaT")
soma.insert('htc')

for seg in soma:
	seg.ena = 71.5 
	seg.ek = -89.1
	seg.hh.gnabar = 0.25
	seg.hh.gl = 0.0001666
	seg.hh.el = -60
	seg.eca = 126.1
    
	seg.CaT.gmax = 0.02
	seg.htc.ghbar = 0.0000
    
for seg in soma: # syntax: ignore
    seg.eca = 126.1

iclamp = h.IClamp(soma(0.5))
iclamp.delay = 700
iclamp.dur = 1600
iclamp.amp = -0.05

# clamp vector i
i_clamp = h.Vector().record(iclamp._ref_i)

v = h.Vector().record(soma(0.5)._ref_v)  # Membrane potential vector

# calcium current (ica)
i_ca = h.Vector().record(soma(0.5)._ref_ica)  # Membrane potential vector

t = h.Vector().record(h._ref_t)  # Time stamp vector

# r,s gates
r = h.Vector().record(soma(0.5).CaT._ref_r)
s = h.Vector().record(soma(0.5).CaT._ref_s)

# Ih current
i_h = h.Vector().record(soma(0.5).htc._ref_i)

# sodium current (ina) from HH
i_na = h.Vector().record(soma(0.5)._ref_ina)

# potassium current (ik)
i_k = h.Vector().record(soma(0.5)._ref_ik)


h.finitialize(-65 * mV)
h.continuerun(3000 * ms)

plt.figure(1)

plt.subplot(5, 1, 1)
plt.plot(t, i_clamp)
plt.xlabel("t (ms)")
plt.ylabel("I (mA)")


plt.subplot(5, 1, 2)

plt.plot(t, v)
plt.xlabel("t (ms)")
plt.ylabel("V (mV)")

plt.subplot(5, 1, 3)

plt.plot(t, i_ca)
plt.xlabel("t (ms)")
plt.ylabel("I_Ca (mA)")


plt.subplot(5, 1, 4)
plt.xlabel("t (ms)")
plt.ylabel("r, s gates")
plt.plot(t, r, label="r")
plt.plot(t, s, label="s")
plt.legend()

plt.subplot(5, 1, 5)
plt.xlabel("t (ms)")
plt.ylabel("I_h (mA)")
plt.plot(t, i_h)
plt.ylim(-0.002, 0.002)

# plt.show()

# print available HH currents
print(dir(soma(0.5).hh))



plt.figure(2)
plt.subplot(2, 1, 1)
plt.plot(t, i_na)
plt.xlabel("t (ms)")
plt.ylabel("I_Na (mA)")

plt.subplot(2, 1, 2)
plt.plot(t, i_k)
plt.xlabel("t (ms)")
plt.ylabel("I_K (mA)")

plt.show()