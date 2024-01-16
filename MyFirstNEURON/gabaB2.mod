COMMENT
-----------------------------------------------------------------------------
Simple synaptic mechanism derived for first order kinetics of
binding of transmitter to postsynaptic receptors.

A. Destexhe & Z. Mainen, The Salk Institute, March 12, 1993.
Last modif. Sept 8, 1993.

Reference:

Destexhe, A., Mainen, Z. and Sejnowski, T.J.  An efficient method for 
computing synaptic conductances based on a kinetic model of receptor binding.
Neural Computation, 6: 14-18, 1994.
-----------------------------------------------------------------------------

  MODIFIED KINETIC MODEL FOR G-PROTEIN GATED SYNAPTIC CHANNELS

For a large family of synaptic receptors, the neurotransmitter does not gate
the ionic channel directly, but through an intracellular second-messenger,
based on the activation of G-proteins.  The most probable mechanism for many
of these neurotransmitters is the direct activation/deactivation of a K+
channel by the G-protein itself.  In this family of receptors, the cholinergic
(muscarinic M2) and GABAergic (GABA_B) receptors are the most extensively
studied.

For the GABA_B-mediated synaptic response, it is assumed that the transmitter
GABA binds to a receptor which catalyzes the intracellular activation of a
G-protein subunit (G_alpha), which itself diffuses and binds to an associated
K+ channel.  The present file contains a first-order model for GABA-B
receptors, which was shown to be equivalent to a more detailed model of the
entire G-protein cascade (Destexhe et al., J. Computational Neuroscience, 1:
195-231, 1994).

Parameters estimated from whole cell recordings of synaptic currents on
hippocampal neurons (Otis et al, J. Physiol. 463: 391-407, 1993).   The model
was directly fit to averaged currents (see Destexhe et al., J. Neurophysiol.
72: 803-818, 1994).

-----------------------------------------------------------------------------
ENDCOMMENT

INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}

NEURON {
	POINT_PROCESS GABAB1
	POINTER pre
	RANGE C, R, R0, R1, g, gmax, lastrelease, Prethresh
	NONSPECIFIC_CURRENT i
	GLOBAL Cmax, Cdur, Alpha, Beta, Erev, Deadtime, Rinf, Rtau
}

UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(umho) = (micromho)
	(mM) = (milli/liter)
}

PARAMETER {

	Cmax	= 1	(mM)		: max transmitter concentration
	Cdur	= 85	(ms)		: transmitter duration (rising phase)
	Alpha	= 0.016	(/ms mM)	: forward (binding) rate
	Beta	= 0.0047 (/ms)		: backward (unbinding) rate
	Erev	= -95	(mV)		: reversal potential (potassium)
	Prethresh = 0 			: voltage level nec for release
	Deadtime = 1	(ms)		: mimimum time between release events
	gmax		(umho)		: maximum conductance
}

ASSIGNED {
	v		(mV)		: postsynaptic voltage
	i 		(nA)		: current = g*(v - Erev)
	g 		(umho)		: conductance
	C		(mM)		: transmitter concentration
	R				: fraction of open channels
	R0				: open channels at start of release
	R1				: open channels at end of release
	Rinf				: steady state channels open
	Rtau		(ms)		: time constant of channel binding
	pre 				: pointer to presynaptic variable
	lastrelease	(ms)		: time of last spike
}

INITIAL {
	R = 0
	C = 0
	Rinf = Cmax*Alpha / (Cmax*Alpha + Beta)
	Rtau = 1 / ((Alpha * Cmax) + Beta)
	lastrelease = -999
}

BREAKPOINT {
	SOLVE release
	g = gmax * R
	i = g*(v - Erev)
}

PROCEDURE release() { LOCAL q
	:will crash if user hasn't set pre with the connect statement 

	q = ((t - lastrelease) - Cdur)		: time since last release ended

						: ready for another release?
	if (q > Deadtime) {
		if (pre > Prethresh) {		: spike occured?
			C = Cmax			: start new release
			R0 = R
			lastrelease = t
		}
						
	} else if (q < 0) {			: still releasing?
	
		: do nothing
	
	} else if (C == Cmax) {			: in dead time after release
		R1 = R
		C = 0.
	}

	if (C > 0) {				: transmitter being released?

	   R = Rinf + (R0 - Rinf) * exptable (- (t - lastrelease) / Rtau)
				
	} else {				: no release occuring

  	   R = R1 * exptable (- Beta * (t - (lastrelease + Cdur)))
	}

	VERBATIM
	return 0;
	ENDVERBATIM
}

FUNCTION exptable(x) { 
	TABLE  FROM -10 TO 10 WITH 2000

	if ((x > -10) && (x < 10)) {
		exptable = exp(x)
	} else {
		exptable = 0.
	}
}
