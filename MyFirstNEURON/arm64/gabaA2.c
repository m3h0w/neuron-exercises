/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__GABA
#define _nrn_initial _nrn_initial__GABA
#define nrn_cur _nrn_cur__GABA
#define _nrn_current _nrn_current__GABA
#define nrn_jacob _nrn_jacob__GABA
#define nrn_state _nrn_state__GABA
#define _net_receive _net_receive__GABA 
#define release release__GABA 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define Prethresh _p[0]
#define Prethresh_columnindex 0
#define gmax _p[1]
#define gmax_columnindex 1
#define i _p[2]
#define i_columnindex 2
#define g _p[3]
#define g_columnindex 3
#define C _p[4]
#define C_columnindex 4
#define R _p[5]
#define R_columnindex 5
#define R0 _p[6]
#define R0_columnindex 6
#define R1 _p[7]
#define R1_columnindex 7
#define lastrelease _p[8]
#define lastrelease_columnindex 8
#define _g _p[9]
#define _g_columnindex 9
#define _nd_area  *_ppvar[0]._pval
#define pre	*_ppvar[2]._pval
#define _p_pre	_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  2;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_exptable(void*);
 static double _hoc_release(void*);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(Object* _ho) { void* create_point_process(int, Object*);
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt(void*);
 static double _hoc_loc_pnt(void* _vptr) {double loc_point_process(int, void*);
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(void* _vptr) {double has_loc_point(void*);
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(void* _vptr) {
 double get_loc_point_process(void*); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 "exptable", _hoc_exptable,
 "release", _hoc_release,
 0, 0
};
#define _f_exptable _f_exptable_GABA
#define exptable exptable_GABA
 extern double _f_exptable( double );
 extern double exptable( double );
 /* declare global and static user variables */
#define Alpha Alpha_GABA
 double Alpha = 0.53;
#define Beta Beta_GABA
 double Beta = 0.18;
#define Cdur Cdur_GABA
 double Cdur = 1;
#define Cmax Cmax_GABA
 double Cmax = 1;
#define Deadtime Deadtime_GABA
 double Deadtime = 1;
#define Erev Erev_GABA
 double Erev = -80;
#define Rtau Rtau_GABA
 double Rtau = 0;
#define Rinf Rinf_GABA
 double Rinf = 0;
#define usetable usetable_GABA
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_GABA", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "Cmax_GABA", "mM",
 "Cdur_GABA", "ms",
 "Alpha_GABA", "/ms",
 "Beta_GABA", "/ms",
 "Erev_GABA", "mV",
 "Deadtime_GABA", "ms",
 "Rtau_GABA", "ms",
 "gmax", "umho",
 "i", "nA",
 "g", "umho",
 "C", "mM",
 "lastrelease", "ms",
 0,0
};
 static double delta_t = 1;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "Cmax_GABA", &Cmax_GABA,
 "Cdur_GABA", &Cdur_GABA,
 "Alpha_GABA", &Alpha_GABA,
 "Beta_GABA", &Beta_GABA,
 "Erev_GABA", &Erev_GABA,
 "Deadtime_GABA", &Deadtime_GABA,
 "Rinf_GABA", &Rinf_GABA,
 "Rtau_GABA", &Rtau_GABA,
 "usetable_GABA", &usetable_GABA,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 static void _hoc_destroy_pnt(void* _vptr) {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"GABA",
 "Prethresh",
 "gmax",
 0,
 "i",
 "g",
 "C",
 "R",
 "R0",
 "R1",
 "lastrelease",
 0,
 0,
 "pre",
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 10, _prop);
 	/*initialize range parameters*/
 	Prethresh = 0;
 	gmax = 0;
  }
 	_prop->param = _p;
 	_prop->param_size = 10;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _gabaA2_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 10, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 GABA /Users/mehow/src-uni/neuron/MyFirstNEURON/gabaA2.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double *_t_exptable;
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int release();
 static double _n_exptable(double);
 
static int  release (  ) {
   double _lq ;
 _lq = ( ( t - lastrelease ) - Cdur ) ;
   if ( _lq > Deadtime ) {
     if ( pre > Prethresh ) {
       C = Cmax ;
       R0 = R ;
       lastrelease = t ;
       }
     }
   else if ( _lq < 0.0 ) {
     }
   else if ( C  == Cmax ) {
     R1 = R ;
     C = 0. ;
     }
   if ( C > 0.0 ) {
     R = Rinf + ( R0 - Rinf ) * exptable ( _threadargscomma_ - ( t - lastrelease ) / Rtau ) ;
     }
   else {
     R = R1 * exptable ( _threadargscomma_ - Beta * ( t - ( lastrelease + Cdur ) ) ) ;
     }
   
/*VERBATIM*/
	return 0;
  return 0; }
 
static double _hoc_release(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 release (  );
 return(_r);
}
 static double _mfac_exptable, _tmin_exptable;
 static void _check_exptable();
 static void _check_exptable() {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  if (!usetable) {return;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_exptable =  - 10.0 ;
   _tmax =  10.0 ;
   _dx = (_tmax - _tmin_exptable)/2000.; _mfac_exptable = 1./_dx;
   for (_i=0, _x=_tmin_exptable; _i < 2001; _x += _dx, _i++) {
    _t_exptable[_i] = _f_exptable(_x);
   }
  }
 }

 double exptable(double _lx){ _check_exptable();
 return _n_exptable(_lx);
 }

 static double _n_exptable(double _lx){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 return _f_exptable(_lx); 
}
 _xi = _mfac_exptable * (_lx - _tmin_exptable);
 if (isnan(_xi)) {
  return _xi; }
 if (_xi <= 0.) {
 return _t_exptable[0];
 }
 if (_xi >= 2000.) {
 return _t_exptable[2000];
 }
 _i = (int) _xi;
 return _t_exptable[_i] + (_xi - (double)_i)*(_t_exptable[_i+1] - _t_exptable[_i]);
 }

 
double _f_exptable (  double _lx ) {
   double _lexptable;
 if ( ( _lx > - 10.0 )  && ( _lx < 10.0 ) ) {
     _lexptable = exp ( _lx ) ;
     }
   else {
     _lexptable = 0. ;
     }
   
return _lexptable;
 }
 
static double _hoc_exptable(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
  _r =  exptable (  *getarg(1) );
 return(_r);
}
 
static int _ode_count(int _type){ hoc_execerror("GABA", "cannot be used with CVODE"); return 0;}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
 {
   R = 0.0 ;
   C = 0.0 ;
   R0 = 0.0 ;
   R1 = 0.0 ;
   Rinf = Cmax * Alpha / ( Cmax * Alpha + Beta ) ;
   Rtau = 1.0 / ( ( Alpha * Cmax ) + Beta ) ;
   lastrelease = - 999.0 ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   g = gmax * R ;
   i = g * ( v - Erev ) ;
   }
 _current += i;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
 { error =  release();
 if(error){fprintf(stderr,"at line 149 in file gabaA2.mod:\n	SOLVE release\n"); nrn_complain(_p); abort_run(error);}
 }}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
   _t_exptable = makevector(2001*sizeof(double));
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/mehow/src-uni/neuron/MyFirstNEURON/gabaA2.mod";
static const char* nmodl_file_text = 
  "COMMENT\n"
  "-----------------------------------------------------------------------------\n"
  "Simple synaptic mechanism derived for first order kinetics of\n"
  "binding of transmitter to postsynaptic receptors.\n"
  "\n"
  "A. Destexhe & Z. Mainen, The Salk Institute, March 12, 1993.\n"
  "Last modif. Sept 8, 1993.\n"
  "\n"
  "Reference:\n"
  "\n"
  "Destexhe, A., Mainen, Z. and Sejnowski, T.J.  An efficient method for \n"
  "computing synaptic conductances based on a kinetic model of receptor binding.\n"
  "Neural Computation, 6: 14-18, 1994.\n"
  "-----------------------------------------------------------------------------\n"
  "\n"
  "During the arrival of the presynaptic spike (detected by threshold \n"
  "crossing), it is assumed that there is a brief pulse (duration=Cdur)\n"
  "of neurotransmitter C in the synaptic cleft (the maximal concentration\n"
  "of C is Cmax).  Then, C is assumed to bind to a receptor Rc according \n"
  "to the following first-order kinetic scheme:\n"
  "\n"
  "Rc + C ---(Alpha)--> Ro							(1)\n"
  "       <--(Beta)--- \n"
  "\n"
  "where Rc and Ro are respectively the closed and open form of the \n"
  "postsynaptic receptor, Alpha and Beta are the forward and backward\n"
  "rate constants.  If R represents the fraction of open gates Ro, \n"
  "then one can write the following kinetic equation:\n"
  "\n"
  "dR/dt = Alpha * C * (1-R) - Beta * R					(2)\n"
  "\n"
  "and the postsynaptic current is given by:\n"
  "\n"
  "Isyn = gmax * R * (V-Erev)						(3)\n"
  "\n"
  "where V is the postsynaptic potential, gmax is the maximal conductance \n"
  "of the synapse and Erev is the reversal potential.\n"
  "\n"
  "If C is assumed to occur as a pulse in the synaptic cleft, such as\n"
  "\n"
  "C     _____ . . . . . . Cmax\n"
  "      |   |\n"
  " _____|   |______ . . . 0 \n"
  "     t0   t1\n"
  "\n"
  "then one can solve the kinetic equation exactly, instead of solving\n"
  "one differential equation for the state variable and for each synapse, \n"
  "which would be greatly time consuming...  \n"
  "\n"
  "Equation (2) can be solved as follows:\n"
  "\n"
  "1. during the pulse (from t=t0 to t=t1), C = Cmax, which gives:\n"
  "\n"
  "   R(t-t0) = Rinf + [ R(t0) - Rinf ] * exp (- (t-t0) / Rtau )		(4)\n"
  "\n"
  "where \n"
  "   Rinf = Alpha * Cmax / (Alpha * Cmax + Beta) \n"
  "and\n"
  "   Rtau = 1 / (Alpha * Cmax + Beta)\n"
  "\n"
  "2. after the pulse (t>t1), C = 0, and one can write:\n"
  "\n"
  "   R(t-t1) = R(t1) * exp (- Beta * (t-t1) )				(5)\n"
  "\n"
  "There is a pointer called \"pre\" which must be set to the variable which\n"
  "is supposed to trigger synaptic release.  This variable is usually the\n"
  "presynaptic voltage but it can be the presynaptic calcium concentration, \n"
  "or other.  Prethresh is the value of the threshold at which the release is\n"
  "initiated.\n"
  "\n"
  "Once pre has crossed the threshold value given by Prethresh, a pulse\n"
  "of C is generated for a duration of Cdur, and the synaptic conductances\n"
  "are calculated accordingly to eqs (4-5).  Another event is not allowed to\n"
  "occur for Deadtime milliseconds following after pre rises above threshold.\n"
  "\n"
  "The user specifies the presynaptic location in hoc via the statement\n"
  "	connect pre_GABA[i] , v.section(x)\n"
  "\n"
  "where x is the arc length (0 - 1) along the presynaptic section (the currently\n"
  "specified section), and i is the synapse number (Which is located at the\n"
  "postsynaptic location in the usual way via\n"
  "	postsynaptic_section {loc_GABA(i, x)}\n"
  "Notice that loc_GABA() must be executed first since that function also\n"
  "allocates space for the synapse.\n"
  "-----------------------------------------------------------------------------\n"
  "  GABA SYNAPSE (GABA-A receptors)\n"
  "\n"
  "  Parameters estimated from whole cell recordings of synaptic currents on\n"
  "  hippocampal neurons (Otis TS and Mody I Neurosci. 49: 13-32, 1992).\n"
  "  The model was directly fit to averaged currents (Destexhe et al., \n"
  "  J. Neurophysiol. 72: 803-818, 1994).\n"
  "\n"
  "-----------------------------------------------------------------------------\n"
  "ENDCOMMENT\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	POINT_PROCESS GABA\n"
  "	POINTER pre\n"
  "	RANGE C, R, R0, R1, g, gmax, lastrelease, Prethresh\n"
  "	NONSPECIFIC_CURRENT i\n"
  "	GLOBAL Cmax, Cdur, Alpha, Beta, Erev, Deadtime, Rinf, Rtau\n"
  "}\n"
  "UNITS {\n"
  "	(nA) = (nanoamp)\n"
  "	(mV) = (millivolt)\n"
  "	(umho) = (micromho)\n"
  "	(mM) = (milli/liter)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "\n"
  "	Cmax	= 1	(mM)		: max transmitter concentration\n"
  "	Cdur	= 1	(ms)		: transmitter duration (rising phase)\n"
  "	Alpha	= 0.53	(/ms mM)	: forward (binding) rate\n"
  "	Beta	= 0.18	(/ms)		: backward (unbinding) rate\n"
  "	Erev	= -80	(mV)		: reversal potential\n"
  "	Prethresh = 0 			: voltage level nec for release\n"
  "	Deadtime = 1	(ms)		: mimimum time between release events\n"
  "	gmax		(umho)		: maximum conductance\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	v		(mV)		: postsynaptic voltage\n"
  "	i 		(nA)		: current = g*(v - Erev)\n"
  "	g 		(umho)		: conductance\n"
  "	C		(mM)		: transmitter concentration\n"
  "	R				: fraction of open channels\n"
  "	R0				: open channels at start of release\n"
  "	R1				: open channels at end of release\n"
  "	Rinf				: steady state channels open\n"
  "	Rtau		(ms)		: time constant of channel binding\n"
  "	pre 				: pointer to presynaptic variable\n"
  "	lastrelease	(ms)		: time of last spike\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	R = 0\n"
  "	C = 0\n"
  "	R0 = 0\n"
  "	R1 = 0\n"
  "	Rinf = Cmax*Alpha / (Cmax*Alpha + Beta)\n"
  "	Rtau = 1 / ((Alpha * Cmax) + Beta)\n"
  "	lastrelease = -999\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE release\n"
  "	g = gmax * R\n"
  "	i = g*(v - Erev)\n"
  "}\n"
  "\n"
  "PROCEDURE release() { LOCAL q\n"
  "	:will crash if user hasn't set pre with the connect statement \n"
  "\n"
  "	q = ((t - lastrelease) - Cdur)		: time since last release ended\n"
  "\n"
  "						: ready for another release?\n"
  "	if (q > Deadtime) {\n"
  "		if (pre > Prethresh) {		: spike occured?\n"
  "			C = Cmax			: start new release\n"
  "			R0 = R\n"
  "			lastrelease = t\n"
  "		}\n"
  "						\n"
  "	} else if (q < 0) {			: still releasing?\n"
  "	\n"
  "		: do nothing\n"
  "	\n"
  "	} else if (C == Cmax) {			: in dead time after release\n"
  "		R1 = R\n"
  "		C = 0.\n"
  "	}\n"
  "\n"
  "	if (C > 0) {				: transmitter being released?\n"
  "\n"
  "	   R = Rinf + (R0 - Rinf) * exptable (- (t - lastrelease) / Rtau)\n"
  "				\n"
  "	} else {				: no release occuring\n"
  "\n"
  "  	   R = R1 * exptable (- Beta * (t - (lastrelease + Cdur)))\n"
  "	}\n"
  "\n"
  "	VERBATIM\n"
  "	return 0;\n"
  "	ENDVERBATIM\n"
  "}\n"
  "\n"
  "FUNCTION exptable(x) { \n"
  "	TABLE  FROM -10 TO 10 WITH 2000\n"
  "\n"
  "	if ((x > -10) && (x < 10)) {\n"
  "		exptable = exp(x)\n"
  "	} else {\n"
  "		exptable = 0.\n"
  "	}\n"
  "}\n"
  ;
#endif
