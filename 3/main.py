from neuron import h, gui # type: ignore
from neuron.units import ms, mV # type: ignore
import matplotlib.pyplot as plt
import numpy as np
# import lambda for calculating nseg from neuron



def chain(*iterables):
    for iterable in iterables:
        yield from iterable

h.load_file('stdrun.hoc')

soma = h.Section(name='soma')
apical = h.Section(name='apical')
basilar = h.Section(name='basilar')
axon = h.Section(name='axon')

apical.connect(soma(1))
basilar.connect(soma(0))
axon.connect(soma(0))

soma.L = 30
soma.diam = 30
soma.nseg = 1

apical.L = 600
apical.diam = 1
apical.nseg = 23

basilar.L = 200
basilar.diam = 2
basilar.nseg = 5

axon_length = 1000 # um
axon.L = axon_length
axon.diam = 1
axon.nseg = 37

for sec in h.allsec():
    sec.Ra = 100
    sec.cm = 1

for sec in h.allsec():
    length_constant = 1e5 * np.sqrt(sec.diam/(4*np.pi*100*sec.Ra*sec.cm))
    nseg = int((sec.L/(0.1*length_constant)+0.9)/2)*2 + 1
    print(sec.name(), "nseg =", nseg)

soma.insert('hh')

apical.insert('pas')

basilar.insert('pas')

for sec in chain(apical, basilar):
    sec.pas.g = 1e-5 * 2
    sec.pas.e = -65

axon.insert('hh')

syn = h.AlphaSynapse(0.5, sec=soma)
syn.onset = 0.5
syn.gmax = 0.05
syn.tau = 0.1
syn.e = 0

v = h.Vector().record(soma(0.5)._ref_v)
t = h.Vector().record(h._ref_t)

v_axon_list = [
    h.Vector().record(axon(0)._ref_v),
    h.Vector().record(axon(0.5)._ref_v),
    h.Vector().record(axon(1)._ref_v),
]

dt = 0.025
tstop = 10
v_init = -65

h.finitialize(v_init)
h.fcurrent()
h.continuerun(tstop)

plt.figure()
plt.plot(t, v)
plt.ylim(-90, 40)
plt.xlabel('t (ms)')
plt.ylabel('V (mV)')

# plot topology
# h.define_shape()
# ps = h.PlotShape(True)
# ps.size(-200, 200, -200, 200)
# ps.variable('v')
# ps.exec_menu('Shape Plot')
# ps.show(0)

fig, ax = plt.subplots(1, 1)
for v_axon in v_axon_list:
    ax.plot(t, v_axon)
    ax.set_xlabel('t (ms)')
    ax.set_ylabel('V (mV)')
    ax.set_ylim(-90, 40)
    ax.legend(['axon(0)', 'axon(0.5)', 'axon(1)'])

# calculate peaks for each part of the axon
peak_t_list = []
for v_axon in v_axon_list:
    axon = np.array(v_axon)
    peak, peak_i = np.max(axon), np.argmax(axon)
    peak_t = peak_i * dt
    peak_t2 = t[peak_i]
    print(peak, peak_i, peak_t, peak_t2)
    peak_t_list.append(peak_t)
    
# calculate conduction velocity
prev_t = None
v_list = []
for t in peak_t_list:
    if prev_t and t:
        velocity = (axon_length / (t - prev_t)) / 1000
        v_list.append(velocity)
        
    prev_t = t

average_velocity = np.mean(v_list)
print("average velocity:", average_velocity, "m/s")

plt.show()
