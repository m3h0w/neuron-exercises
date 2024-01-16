/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
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
 
#define nrn_init _nrn_init__HH
#define _nrn_initial _nrn_initial__HH
#define nrn_cur _nrn_cur__HH
#define _nrn_current _nrn_current__HH
#define nrn_jacob _nrn_jacob__HH
#define nrn_state _nrn_state__HH
#define _net_receive _net_receive__HH 
#define _f_rates _f_rates__HH 
#define rates rates__HH 
#define states states__HH 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define gnabar _p[0]
#define gnabar_columnindex 0
#define gkbar _p[1]
#define gkbar_columnindex 1
#define gl _p[2]
#define gl_columnindex 2
#define el _p[3]
#define el_columnindex 3
#define ina _p[4]
#define ina_columnindex 4
#define ik _p[5]
#define ik_columnindex 5
#define il _p[6]
#define il_columnindex 6
#define m_inf _p[7]
#define m_inf_columnindex 7
#define h_inf _p[8]
#define h_inf_columnindex 8
#define n_inf _p[9]
#define n_inf_columnindex 9
#define tau_m _p[10]
#define tau_m_columnindex 10
#define tau_h _p[11]
#define tau_h_columnindex 11
#define tau_n _p[12]
#define tau_n_columnindex 12
#define m _p[13]
#define m_columnindex 13
#define h _p[14]
#define h_columnindex 14
#define n _p[15]
#define n_columnindex 15
#define ena _p[16]
#define ena_columnindex 16
#define ek _p[17]
#define ek_columnindex 17
#define Dm _p[18]
#define Dm_columnindex 18
#define Dh _p[19]
#define Dh_columnindex 19
#define Dn _p[20]
#define Dn_columnindex 20
#define tadj _p[21]
#define tadj_columnindex 21
#define v _p[22]
#define v_columnindex 22
#define _g _p[23]
#define _g_columnindex 23
#define _ion_ena	*_ppvar[0]._pval
#define _ion_ina	*_ppvar[1]._pval
#define _ion_dinadv	*_ppvar[2]._pval
#define _ion_ek	*_ppvar[3]._pval
#define _ion_ik	*_ppvar[4]._pval
#define _ion_dikdv	*_ppvar[5]._pval
 
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
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_rates(void);
 static void _hoc_states(void);
 static void _hoc_vtrap(void);
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

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_HH", _hoc_setdata,
 "rates_HH", _hoc_rates,
 "states_HH", _hoc_states,
 "vtrap_HH", _hoc_vtrap,
 0, 0
};
#define vtrap vtrap_HH
 extern double vtrap( _threadargsprotocomma_ double , double );
 
static void _check_rates(double*, Datum*, Datum*, NrnThread*); 
static void _check_table_thread(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, int _type) {
   _check_rates(_p, _ppvar, _thread, _nt);
 }
 /* declare global and static user variables */
#define usetable usetable_HH
 double usetable = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "usetable_HH", 0, 1,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gnabar_HH", "mho/cm2",
 "gkbar_HH", "mho/cm2",
 "gl_HH", "mho/cm2",
 "el_HH", "mV",
 "ina_HH", "mA/cm2",
 "ik_HH", "mA/cm2",
 "il_HH", "mA/cm2",
 0,0
};
 static double delta_t = 1;
 static double h0 = 0;
 static double m0 = 0;
 static double n0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "usetable_HH", &usetable_HH,
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
 
static int _ode_count(int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"HH",
 "gnabar_HH",
 "gkbar_HH",
 "gl_HH",
 "el_HH",
 0,
 "ina_HH",
 "ik_HH",
 "il_HH",
 "m_inf_HH",
 "h_inf_HH",
 "n_inf_HH",
 "tau_m_HH",
 "tau_h_HH",
 "tau_n_HH",
 0,
 "m_HH",
 "h_HH",
 "n_HH",
 0,
 0};
 static Symbol* _na_sym;
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 24, _prop);
 	/*initialize range parameters*/
 	gnabar = 0.1;
 	gkbar = 0.01;
 	gl = 0;
 	el = 0;
 	_prop->param = _p;
 	_prop->param_size = 24;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 6, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[3]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[4]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[5]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static void _initlists();
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _HH1_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("na", -10000.);
 	ion_reg("k", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
     _nrn_thread_table_reg(_mechtype, _check_table_thread);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 24, 6);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "k_ion");
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 HH /Users/mehow/src-uni/neuron/MyFirstNEURON/HH1.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double *_t_m_inf;
 static double *_t_tau_m;
 static double *_t_h_inf;
 static double *_t_tau_h;
 static double *_t_n_inf;
 static double *_t_tau_n;
static int _reset;
static char *modelname = "Hodgkin-Huxley like sodium, potassium, and leak channels";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int _f_rates(_threadargsprotocomma_ double);
static int rates(_threadargsprotocomma_ double);
static int states(_threadargsproto_);
 static void _n_rates(_threadargsprotocomma_ double _lv);
 
static int  states ( _threadargsproto_ ) {
   rates ( _threadargscomma_ v ) ;
   m = m + ( 1.0 - exp ( - dt / tau_m ) ) * ( m_inf - m ) ;
   h = h + ( 1.0 - exp ( - dt / tau_h ) ) * ( h_inf - h ) ;
   n = n + ( 1.0 - exp ( - dt / tau_n ) ) * ( n_inf - n ) ;
    return 0; }
 
static void _hoc_states(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 states ( _p, _ppvar, _thread, _nt );
 hoc_retpushx(_r);
}
 static double _mfac_rates, _tmin_rates;
  static void _check_rates(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  static int _maktable=1; int _i, _j, _ix = 0;
  double _xi, _tmax;
  static double _sav_dt;
  static double _sav_celsius;
  if (!usetable) {return;}
  if (_sav_dt != dt) { _maktable = 1;}
  if (_sav_celsius != celsius) { _maktable = 1;}
  if (_maktable) { double _x, _dx; _maktable=0;
   _tmin_rates =  - 100.0 ;
   _tmax =  100.0 ;
   _dx = (_tmax - _tmin_rates)/200.; _mfac_rates = 1./_dx;
   for (_i=0, _x=_tmin_rates; _i < 201; _x += _dx, _i++) {
    _f_rates(_p, _ppvar, _thread, _nt, _x);
    _t_m_inf[_i] = m_inf;
    _t_tau_m[_i] = tau_m;
    _t_h_inf[_i] = h_inf;
    _t_tau_h[_i] = tau_h;
    _t_n_inf[_i] = n_inf;
    _t_tau_n[_i] = tau_n;
   }
   _sav_dt = dt;
   _sav_celsius = celsius;
  }
 }

 static int rates(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _lv) { 
#if 0
_check_rates(_p, _ppvar, _thread, _nt);
#endif
 _n_rates(_p, _ppvar, _thread, _nt, _lv);
 return 0;
 }

 static void _n_rates(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _lv){ int _i, _j;
 double _xi, _theta;
 if (!usetable) {
 _f_rates(_p, _ppvar, _thread, _nt, _lv); return; 
}
 _xi = _mfac_rates * (_lv - _tmin_rates);
 if (isnan(_xi)) {
  m_inf = _xi;
  tau_m = _xi;
  h_inf = _xi;
  tau_h = _xi;
  n_inf = _xi;
  tau_n = _xi;
  return;
 }
 if (_xi <= 0.) {
 m_inf = _t_m_inf[0];
 tau_m = _t_tau_m[0];
 h_inf = _t_h_inf[0];
 tau_h = _t_tau_h[0];
 n_inf = _t_n_inf[0];
 tau_n = _t_tau_n[0];
 return; }
 if (_xi >= 200.) {
 m_inf = _t_m_inf[200];
 tau_m = _t_tau_m[200];
 h_inf = _t_h_inf[200];
 tau_h = _t_tau_h[200];
 n_inf = _t_n_inf[200];
 tau_n = _t_tau_n[200];
 return; }
 _i = (int) _xi;
 _theta = _xi - (double)_i;
 m_inf = _t_m_inf[_i] + _theta*(_t_m_inf[_i+1] - _t_m_inf[_i]);
 tau_m = _t_tau_m[_i] + _theta*(_t_tau_m[_i+1] - _t_tau_m[_i]);
 h_inf = _t_h_inf[_i] + _theta*(_t_h_inf[_i+1] - _t_h_inf[_i]);
 tau_h = _t_tau_h[_i] + _theta*(_t_tau_h[_i+1] - _t_tau_h[_i]);
 n_inf = _t_n_inf[_i] + _theta*(_t_n_inf[_i+1] - _t_n_inf[_i]);
 tau_n = _t_tau_n[_i] + _theta*(_t_tau_n[_i+1] - _t_tau_n[_i]);
 }

 
static int  _f_rates ( _threadargsprotocomma_ double _lv ) {
   double _lalpha , _lbeta , _lq10 , _ltinc ;
 tadj = pow( 3.0 , ( ( celsius - 23.5 ) / 10.0 ) ) ;
   _lalpha = .091 * vtrap ( _threadargscomma_ _lv + 38.0 , 5.0 ) ;
   _lbeta = .062 * vtrap ( _threadargscomma_ - ( _lv + 38.0 ) , 5.0 ) ;
   tau_m = 1.0 / ( _lalpha + _lbeta ) / tadj ;
   m_inf = _lalpha / ( _lalpha + _lbeta ) ;
   _lalpha = .016 * exp ( - ( _lv + 55.0 ) / 15.0 ) ;
   _lbeta = 2.07 / ( 1.0 + exp ( ( 17.0 - _lv ) / 21.0 ) ) ;
   tau_h = 1.0 / ( _lalpha + _lbeta ) / tadj ;
   h_inf = _lalpha / ( _lalpha + _lbeta ) ;
   _lalpha = .01 * vtrap ( _threadargscomma_ _lv + 45.0 , 5.0 ) ;
   _lbeta = .17 * exp ( - ( _lv + 50.0 ) / 40.0 ) ;
   tau_n = 1.0 / ( _lalpha + _lbeta ) / tadj ;
   n_inf = _lalpha / ( _lalpha + _lbeta ) ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 
#if 1
 _check_rates(_p, _ppvar, _thread, _nt);
#endif
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double vtrap ( _threadargsprotocomma_ double _lx , double _lb ) {
   double _lvtrap;
 if ( fabs ( _lx / _lb ) < 1e-6 ) {
     _lvtrap = _lb + _lx / 2.0 ;
     }
   else {
     _lvtrap = _lx / ( 1.0 - exp ( - _lx / _lb ) ) ;
     }
   
return _lvtrap;
 }
 
static void _hoc_vtrap(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  vtrap ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ hoc_execerror("HH", "cannot be used with CVODE"); return 0;}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 4);
   nrn_update_ion_pointer(_k_sym, _ppvar, 3, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 4, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 5, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  h = h0;
  m = m0;
  n = n0;
 {
   rates ( _threadargscomma_ v ) ;
   m = m_inf ;
   h = h_inf ;
   n = n_inf ;
   }
 
}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];

#if 0
 _check_rates(_p, _ppvar, _thread, _nt);
#endif
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
  ena = _ion_ena;
  ek = _ion_ek;
 initmodel(_p, _ppvar, _thread, _nt);
  }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   ina = gnabar * m * m * m * h * ( v - ena ) ;
   ik = gkbar * n * n * n * n * ( v - ek ) ;
   il = gl * ( v - el ) ;
   }
 _current += ina;
 _current += ik;
 _current += il;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
  ena = _ion_ena;
  ek = _ion_ek;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dik;
 double _dina;
  _dina = ina;
  _dik = ik;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dinadv += (_dina - ina)/.001 ;
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
  _ion_ik += ik ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
  ena = _ion_ena;
  ek = _ion_ek;
 {  { states(_p, _ppvar, _thread, _nt); }
  }  }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
   _t_m_inf = makevector(201*sizeof(double));
   _t_tau_m = makevector(201*sizeof(double));
   _t_h_inf = makevector(201*sizeof(double));
   _t_tau_h = makevector(201*sizeof(double));
   _t_n_inf = makevector(201*sizeof(double));
   _t_tau_n = makevector(201*sizeof(double));
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/mehow/src-uni/neuron/MyFirstNEURON/HH1.mod";
static const char* nmodl_file_text = 
  "TITLE Hodgkin-Huxley like sodium, potassium, and leak channels\n"
  "\n"
  "COMMENT\n"
  "        *********************************************\n"
  "        reference:      McCormick & Huguenard (1992) \n"
  "			J.Neurophysiology 68(4), 1384-1400\n"
  "        found in:       cortical pyramidal cells\n"
  "        *********************************************\n"
  "        Assembled for MyFirstNEURON by Arthur Houweling\n"
  "ENDCOMMENT\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "UNITS {\n"
  "        (mA) = (milliamp)\n"
  "        (mV) = (millivolt)\n"
  "}\n"
  " \n"
  "NEURON {\n"
  "        SUFFIX HH\n"
  "        USEION na READ ena WRITE ina\n"
  "        USEION k READ ek WRITE ik\n"
  "        NONSPECIFIC_CURRENT il\n"
  "        RANGE gnabar,gkbar,gl,el,m_inf,h_inf,n_inf,tau_m,tau_n,tau_h,ina,ik \n"
  "}\n"
  " \n"
  "PARAMETER {\n"
  "        v		(mV)\n"
  "        celsius		(degC)\n"
  "        dt		(ms)\n"
  "        gnabar= 0.1	(mho/cm2)\n"
  "        ena		(mV)\n"
  "        gkbar= 0.01	(mho/cm2)\n"
  "        ek		(mV)\n"
  "        gl= 0		(mho/cm2)\n"
  "        el		(mV)\n"
  "}\n"
  " \n"
  "STATE {\n"
  "        m h n\n"
  "}\n"
  " \n"
  "ASSIGNED {\n"
  "        ina	(mA/cm2)\n"
  "        ik	(mA/cm2)\n"
  "        il	(mA/cm2)\n"
  "        m_inf h_inf n_inf tau_m tau_h tau_n\n"
  "	tadj\n"
  "}\n"
  " \n"
  "BREAKPOINT {\n"
  "        SOLVE states\n"
  "        ina = gnabar * m*m*m*h * (v - ena)\n"
  "        ik = gkbar * n*n*n*n * (v - ek)      \n"
  "        il = gl * (v-el)\n"
  "}\n"
  " \n"
  "UNITSOFF\n"
  "INITIAL {\n"
  "	rates(v)\n"
  "	m = m_inf\n"
  "	h = h_inf\n"
  "	n = n_inf\n"
  "}\n"
  "\n"
  "PROCEDURE states() { \n"
  "        rates(v)   \n"
  "        m = m + (1-exp(-dt/tau_m)) * (m_inf-m)\n"
  "        h = h + (1-exp(-dt/tau_h)) * (h_inf-h)\n"
  "        n = n + (1-exp(-dt/tau_n)) * (n_inf-n)\n"
  "}\n"
  " \n"
  "PROCEDURE rates(v) { LOCAL alpha, beta, q10, tinc\n"
  "        TABLE m_inf, tau_m, h_inf, tau_h, n_inf, tau_n DEPEND dt, \n"
  "	      celsius FROM -100 TO 100 WITH 200\n"
  "	tadj = 3.0^((celsius-23.5)/10)\n"
  "	:\"m\" sodium activation system\n"
  "          alpha = .091 * vtrap(v+38,5)\n"
  "          beta =  .062 * vtrap(-(v+38),5) \n"
  "       	  tau_m = 1 / (alpha+beta) / tadj\n"
  "       	  m_inf = alpha/(alpha+beta)\n"
  "	:\"h\" sodium inactivation system\n"
  "       	  alpha = .016 * exp(-(v+55)/15)\n"
  "       	  beta = 2.07 / (1+exp((17-v)/21))\n"
  "       	  tau_h = 1 / (alpha+beta) / tadj\n"
  "       	  h_inf = alpha/(alpha+beta)\n"
  "	:\"n\" potassium activation system\n"
  "       	  alpha = .01*vtrap(v+45,5) \n"
  "       	  beta = .17*exp(-(v+50)/40)\n"
  "       	  tau_n = 1 / (alpha+beta) / tadj\n"
  "       	  n_inf = alpha/(alpha+beta)\n"
  "}\n"
  " \n"
  "FUNCTION vtrap( x, b) {\n"
  "	: Traps for 0 in denominator of rate equations\n"
  "	if (fabs(x/b) < 1e-6) {\n"
  "	  vtrap = b+x/2 }\n"
  "	else {\n"
  "	  vtrap = x / (1-exp(-x/b)) }\n"
  "}\n"
  "UNITSON\n"
  "\n"
  ;
#endif
