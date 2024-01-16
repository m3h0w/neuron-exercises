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

soma = h.Section(name = "soma")
soma.nseg = 1
soma.L = 18.8
soma.diam = 18.8
soma.Ra = 123
soma.insert("hh")

for seg in soma:
	seg.ena = 71.5 
	seg.ek = -89.1
	seg.hh.gnabar = 0.25
	seg.hh.gl = 0.0001666
	seg.hh.el = -60
    
soma.insert("CaT")

for seg in soma: # syntax: ignore
    seg.eca = 126.1

iclamp = h.IClamp(soma(0.5))
iclamp.delay = 500
iclamp.dur = 500
iclamp.amp = -0.05

v = h.Vector().record(soma(0.5)._ref_v)  # Membrane potential vector

# calcium current (ica)
i = h.Vector().record(soma(0.5)._ref_ica)  # Membrane potential vector

t = h.Vector().record(h._ref_t)  # Time stamp vector


h.finitialize(-65 * mV)
h.continuerun(2000 * ms)

plt.subplot(2, 1, 1)

plt.plot(t, v)
plt.xlabel("t (ms)")
plt.ylabel("V (mV)")

plt.subplot(2, 1, 2)

plt.plot(t, i)
plt.xlabel("t (ms)")
plt.ylabel("I (mA)")
plt.show()

