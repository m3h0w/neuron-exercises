from neuron import h
import matplotlib.pyplot as plt
from tqdm import tqdm


# Create a section (a piece of a neuron)
soma = h.Section(name='soma')

# Insert passive properties
soma.insert('pas')

# Create a stimulus
stim = h.IClamp(soma(0.5))
stim.delay = 5
stim.dur = 1
stim.amp = 1.0

# Initialize a vector to record time
t = h.Vector().record(h._ref_t)

# Initialize a vector to record membrane potential
v = h.Vector().record(soma(0.5)._ref_v)

# Run a simulation
h.finitialize(-65)
# h.continuerun(100)
# while h.t < 100:
# use tqdm
dt = 0.1
run_for = 100
for _ in tqdm(range(int(run_for / dt))):
    h.fadvance()
    # print('Simulation time: ', h.t)

# Plot the results
plt.figure()
plt.plot(t, v)
plt.xlabel('time (ms)')
plt.ylabel('mV')
plt.show()