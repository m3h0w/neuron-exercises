from neuron import h, gui # type: ignore
from neuron.units import ms, mV # type: ignore
import matplotlib.pyplot as plt
import numpy as np
# import lambda for calculating nseg from neuron


def run(experiment_number=1):
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
    v_axon = h.Vector().record(axon(0.5)._ref_v)
    v_apical = h.Vector().record(apical(0.5)._ref_v)
    i_synapse = h.Vector().record(syn._ref_i)
    t = h.Vector().record(h._ref_t)

    dt = 0.025
    tstop = 10
    v_init = -65
    
    if experiment_number == 1:
        plt.figure(figsize=(12.8, 6.4))
        for t in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]:
            h.finitialize(v_init)
            h.fcurrent()
            h.continuerun(t*ms)

            rvp = h.RangeVarPlot('v', axon(1), apical(1)) 
            my_plot = rvp.plot(plt, label='t='+str(t)+'ms')

        plt.show()
    elif experiment_number == 2:
        tstop = 10

        fig, ax = plt.subplots(1, 4, figsize=(12.8, 6.4))
        # dt experiment for apical, soma, and axon
        for i, (name, sec, v) in enumerate(zip(['apical', 'soma', 'axon', 'synapse'], [apical, soma, axon, syn], [v_apical, v, v_axon, i_synapse])):
            ax[i].set_title(name)
            for dt in [0.025, 0.05, 0.1, 0.2, 0.4, 0.6, 1]:
                h.dt = dt
                h.finitialize(v_init)
                h.fcurrent()
                h.continuerun(tstop)

                ax[i].plot(t, v, label='dt='+str(dt)+'ms')
                ax[i].set_xlabel('t (ms)')
                ax[i].set_ylabel('v (mV)')
                ax[i].legend()

                if i != 3:
                    ax[i].set_ylim(-80, 60)
                else:
                    ax[i].set_xlim(0, 1)

        plt.tight_layout()
        plt.show()
    elif experiment_number == 3:
        fig, ax = plt.subplots(1, 3, figsize=(12.8, 6.4))
        for i, (name, sec, v) in enumerate(zip(['apical', 'soma', 'axon'], [apical, soma, axon], [v_apical, v, v_axon])):
            ax[i].set_title(name)
            for d_lambda in [0.05, 0.1, 0.2, 0.3, 1, 3]:                
                for sec in h.allsec(): 
                    length_constant = 1e5*np.sqrt(sec.diam/(4*np.pi*100*sec.Ra*sec.cm))
                    sec.nseg = int((sec.L/(d_lambda*length_constant)+0.9)/2)*2+1
                    print("d_lambda =", d_lambda, " nseg =", sec.nseg)

                h.finitialize(v_init)
                h.fcurrent()
                h.continuerun(tstop)

                ax[i].plot(t, v, label='d_lambda='+str(d_lambda))
                ax[i].set_xlabel('t (ms)')
                ax[i].set_ylabel('v (mV)')
                ax[i].legend()
                ax[i].set_ylim(-80, 60)
                ax[i].set_xlim(0, 2)

        
        plt.tight_layout()
        plt.show()
    elif experiment_number == 4:
        tstop_list = [1.5, 3, 5]
        fig, ax = plt.subplots(len(tstop_list), 1, figsize=(12.8, 6.4))
        for i, tstop in enumerate(tstop_list):
            ax[i].set_title('Space plot for tstop='+str(tstop)+'ms')
            for dl in [1, 0.3, 0.2, 0.1, 0.05]:
                for sec in h.allsec(): 
                    length_constant = 1e5*np.sqrt(sec.diam/(4*np.pi*100*sec.Ra*sec.cm))
                    sec.nseg = int((sec.L/(dl*length_constant)+0.9)/2)*2+1
                    print("d_lambda =", dl, " nseg =", sec.nseg)

                h.finitialize(v_init)
                h.fcurrent()
                h.continuerun(tstop*ms)

                rvp = h.RangeVarPlot('v', axon(1), apical(1)) 
                my_plot = rvp.plot(ax[i], label='d_lambda='+str(dl))
                # ax[i].plot(v, t, label='d_lambda='+str(dl))

            ax[i].set_ylim(-80, 60)
            ax[i].set_xlabel('position (um)')
            ax[i].set_ylabel('v (mV)')
            ax[i].legend()

        plt.legend()
        plt.show()
    else:
        raise ValueError('Invalid experiment number')

if __name__ == '__main__':
    # take argument and run experiment
    import sys
    experiment_number = int(sys.argv[1])
    run(experiment_number)
