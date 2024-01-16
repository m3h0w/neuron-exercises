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
 
#define nrn_init _nrn_init__iH
#define _nrn_initial _nrn_initial__iH
#define nrn_cur _nrn_cur__iH
#define _nrn_current _nrn_current__iH
#define nrn_jacob _nrn_jacob__iH
#define nrn_state _nrn_state__iH
#define _net_receive _net_receive__iH 
#define evaluate_fct evaluate_fct__iH 
#define states states__iH 
 
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
#define ghbar _p[0]
#define ghbar_columnindex 0
#define ih _p[1]
#define ih_columnindex 1
#define tau_s _p[2]
#define tau_s_columnindex 2
#define tau_f _p[3]
#define tau_f_columnindex 3
#define tau_c _p[4]
#define tau_c_columnindex 4
#define s1 _p[5]
#define s1_columnindex 5
#define s2 _p[6]
#define s2_columnindex 6
#define f1 _p[7]
#define f1_columnindex 7
#define f2 _p[8]
#define f2_columnindex 8
#define cai _p[9]
#define cai_columnindex 9
#define eh _p[10]
#define eh_columnindex 10
#define Ds1 _p[11]
#define Ds1_columnindex 11
#define Ds2 _p[12]
#define Ds2_columnindex 12
#define Df1 _p[13]
#define Df1_columnindex 13
#define Df2 _p[14]
#define Df2_columnindex 14
#define h_inf _p[15]
#define h_inf_columnindex 15
#define alpha_s _p[16]
#define alpha_s_columnindex 16
#define alpha_f _p[17]
#define alpha_f_columnindex 17
#define beta_s _p[18]
#define beta_s_columnindex 18
#define beta_f _p[19]
#define beta_f_columnindex 19
#define C _p[20]
#define C_columnindex 20
#define k2 _p[21]
#define k2_columnindex 21
#define tadj _p[22]
#define tadj_columnindex 22
#define s0 _p[23]
#define s0_columnindex 23
#define f0 _p[24]
#define f0_columnindex 24
#define v _p[25]
#define v_columnindex 25
#define _g _p[26]
#define _g_columnindex 26
#define _ion_eh	*_ppvar[0]._pval
#define _ion_ih	*_ppvar[1]._pval
#define _ion_dihdv	*_ppvar[2]._pval
#define _ion_cai	*_ppvar[3]._pval
 
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
 static void _hoc_evaluate_fct(void);
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
 "setdata_iH", _hoc_setdata,
 "evaluate_fct_iH", _hoc_evaluate_fct,
 0, 0
};
 /* declare global and static user variables */
#define cac cac_iH
 double cac = 0.0005;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "cac_iH", "mM",
 "ghbar_iH", "mho/cm2",
 "ih_iH", "mA/cm2",
 "tau_s_iH", "ms",
 "tau_f_iH", "ms",
 "tau_c_iH", "ms",
 0,0
};
 static double delta_t = 1;
 static double f20 = 0;
 static double f10 = 0;
 static double s20 = 0;
 static double s10 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "cac_iH", &cac_iH,
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
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[4]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"iH",
 "ghbar_iH",
 0,
 "ih_iH",
 "tau_s_iH",
 "tau_f_iH",
 "tau_c_iH",
 0,
 "s1_iH",
 "s2_iH",
 "f1_iH",
 "f2_iH",
 0,
 0};
 static Symbol* _h_sym;
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 27, _prop);
 	/*initialize range parameters*/
 	ghbar = 4e-05;
 	_prop->param = _p;
 	_prop->param_size = 27;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_h_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* eh */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ih */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dihdv */
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[3]._pval = &prop_ion->param[1]; /* cai */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _ih_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("h", 1.0);
 	ion_reg("ca", -10000.);
 	_h_sym = hoc_lookup("h_ion");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 27, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "h_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "h_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "h_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 iH /Users/mehow/src-uni/neuron/MyFirstNEURON/ih.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "hyperpolarization-activated current (H-current) ";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int evaluate_fct(_threadargsprotocomma_ double, double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[4], _dlist1[4];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   evaluate_fct ( _threadargscomma_ v , cai ) ;
   Ds1 = alpha_s * s0 - beta_s * s1 + k2 * ( s2 - C * s1 ) ;
   Df1 = alpha_f * f0 - beta_f * f1 + k2 * ( f2 - C * f1 ) ;
   Ds2 = - k2 * ( s2 - C * s1 ) ;
   Df2 = - k2 * ( f2 - C * f1 ) ;
   s0 = 1.0 - s1 - s2 ;
   f0 = 1.0 - f1 - f2 ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 evaluate_fct ( _threadargscomma_ v , cai ) ;
 Ds1 = Ds1  / (1. - dt*( ( - ( beta_s )*( 1.0 ) ) + ( k2 )*( ( ( - ( C )*( 1.0 ) ) ) ) )) ;
 Df1 = Df1  / (1. - dt*( ( - ( beta_f )*( 1.0 ) ) + ( k2 )*( ( ( - ( C )*( 1.0 ) ) ) ) )) ;
 Ds2 = Ds2  / (1. - dt*( ( - k2 )*( ( 1.0 ) ) )) ;
 Df2 = Df2  / (1. - dt*( ( - k2 )*( ( 1.0 ) ) )) ;
 s0 = 1.0 - s1 - s2 ;
 f0 = 1.0 - f1 - f2 ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   evaluate_fct ( _threadargscomma_ v , cai ) ;
    s1 = s1 + (1. - exp(dt*(( - ( beta_s )*( 1.0 ) ) + ( k2 )*( ( ( - ( C )*( 1.0 ) ) ) ))))*(- ( ( alpha_s )*( s0 ) + ( k2 )*( ( s2 ) ) ) / ( ( - ( beta_s )*( 1.0 ) ) + ( k2 )*( ( ( - ( C )*( 1.0 ) ) ) ) ) - s1) ;
    f1 = f1 + (1. - exp(dt*(( - ( beta_f )*( 1.0 ) ) + ( k2 )*( ( ( - ( C )*( 1.0 ) ) ) ))))*(- ( ( alpha_f )*( f0 ) + ( k2 )*( ( f2 ) ) ) / ( ( - ( beta_f )*( 1.0 ) ) + ( k2 )*( ( ( - ( C )*( 1.0 ) ) ) ) ) - f1) ;
    s2 = s2 + (1. - exp(dt*(( - k2 )*( ( 1.0 ) ))))*(- ( ( - k2 )*( ( ( - ( C )*( s1 ) ) ) ) ) / ( ( - k2 )*( ( 1.0 ) ) ) - s2) ;
    f2 = f2 + (1. - exp(dt*(( - k2 )*( ( 1.0 ) ))))*(- ( ( - k2 )*( ( ( - ( C )*( f1 ) ) ) ) ) / ( ( - k2 )*( ( 1.0 ) ) ) - f2) ;
   s0 = 1.0 - s1 - s2 ;
   f0 = 1.0 - f1 - f2 ;
   }
  return 0;
}
 
static int  evaluate_fct ( _threadargsprotocomma_ double _lv , double _lcai ) {
   h_inf = 1.0 / ( 1.0 + exp ( ( _lv + 68.9 ) / 6.5 ) ) ;
   tau_s = exp ( ( _lv + 183.6 ) / 15.24 ) / tadj ;
   tau_f = exp ( ( _lv + 158.6 ) / 11.2 ) / ( 1.0 + exp ( ( _lv + 75.0 ) / 5.5 ) ) / tadj ;
   alpha_s = h_inf / tau_s ;
   alpha_f = h_inf / tau_f ;
   beta_s = ( 1.0 - h_inf ) / tau_s ;
   beta_f = ( 1.0 - h_inf ) / tau_f ;
   C = _lcai * _lcai / ( cac * cac ) ;
   k2 = 4e-4 * tadj ;
    return 0; }
 
static void _hoc_evaluate_fct(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 evaluate_fct ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 4;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  eh = _ion_eh;
  cai = _ion_cai;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 4; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  eh = _ion_eh;
  cai = _ion_cai;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_h_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_h_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_h_sym, _ppvar, 2, 4);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 1);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  f2 = f20;
  f1 = f10;
  s2 = s20;
  s1 = s10;
 {
   tadj = pow( 3.0 , ( ( celsius - 35.5 ) / 10.0 ) ) ;
   evaluate_fct ( _threadargscomma_ v , cai ) ;
   s1 = alpha_s / ( beta_s + alpha_s * ( 1.0 + C ) ) ;
   s2 = alpha_s * C / ( beta_s + alpha_s * ( 1.0 + C ) ) ;
   s0 = 1.0 - s1 - s2 ;
   f1 = alpha_f / ( beta_f + alpha_f * ( 1.0 + C ) ) ;
   f2 = alpha_f * C / ( beta_f + alpha_f * ( 1.0 + C ) ) ;
   f0 = 1.0 - f1 - f2 ;
   tau_c = 1.0 / ( 1.0 + C ) / k2 ;
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
  eh = _ion_eh;
  cai = _ion_cai;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   ih = ghbar * ( s1 + s2 ) * ( f1 + f2 ) * ( v - eh ) ;
   }
 _current += ih;

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
  eh = _ion_eh;
  cai = _ion_cai;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dih;
  _dih = ih;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dihdv += (_dih - ih)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ih += ih ;
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
  eh = _ion_eh;
  cai = _ion_cai;
 {   states(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = s1_columnindex;  _dlist1[0] = Ds1_columnindex;
 _slist1[1] = f1_columnindex;  _dlist1[1] = Df1_columnindex;
 _slist1[2] = s2_columnindex;  _dlist1[2] = Ds2_columnindex;
 _slist1[3] = f2_columnindex;  _dlist1[3] = Df2_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/mehow/src-uni/neuron/MyFirstNEURON/ih.mod";
static const char* nmodl_file_text = 
  "TITLE hyperpolarization-activated current (H-current) \n"
  "\n"
  "COMMENT\n"
  "	Two distinct activation gates are assumed with the same asymptotic \n"
  "	opening values, a fast gate (F) and a slow gate (S). The following \n"
  "	kinetic scheme is assumed\n"
  "\n"
  "	s0  --(Alpha)--> s1 + n Cai  --(k1)--> s2\n"
  "           <--(Beta)---             <--(k2)--\n"
  " \n"
  " 	f0  --(Alpha)--> f1 + n Cai  --(k1)--> f2\n"
  "           <--(Beta)---             <--(k2)--\n"
  "\n"
  "	where s0/f0, s1/f1, and s2/f2 are resp. fraction of closed slow/fast \n"
  "	gates, fraction of open unbound slow/fast gates, and fraction of open \n"
  "	calcium-bound slow/fast	gates, n is taken 2, and k1 = k2*C where \n"
  "	C = (cai/cac)^n and cac is the critical value at which Ca2+ binding \n"
  "	is half-activated.\n"
  "	\n"
  "	The total current is computed according\n"
  "\n"
  "	ih = ghbar * (s1+s2) * (f1+f2) * (v-eh)\n"
  "\n"
  "        *********************************************\n"
  "        reference:      Destexhe, Babloyantz & Sejnowski (1993)\n"
  "			Biophys.J. 65, 1538-1552\n"
  "        found in:       thalamocortical neurons\n"
  "        *********************************************\n"
  "	Maxim Bazhenov's first mod file\n"
  "        Rewritten for MyFirstNEURON by Arthur Houweling \n"
  "ENDCOMMENT\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX iH\n"
  "	USEION h READ eh WRITE ih VALENCE 1\n"
  "	USEION ca READ cai\n"
  "        RANGE ghbar, tau_s, tau_f, tau_c, ih\n"
  "	GLOBAL cac\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mA) 	= (milliamp)\n"
  "	(mV) 	= (millivolt)\n"
  "	(molar)	= (1/liter)\n"
  "	(mM) 	= (millimolar)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	v		(mV)\n"
  "	cai		(mM)\n"
  "	celsius		(degC)\n"
  "	eh	= -43	(mV)\n"
  "	ghbar	= 4e-5	(mho/cm2)\n"
  "	cac 	= 5e-4	(mM)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	s1			: fraction of open unbound slow gates \n"
  "	s2 			: fraction of open calcium-bound slow gates\n"
  "	f1	 		: fraction of open unbound fast gates\n"
  "	f2			: fraction of open calcium-bound fast gates\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	ih		(mA/cm2)\n"
  "        h_inf\n"
  "        tau_s		(ms)	: time constant slow gate\n"
  "        tau_f 		(ms)	: time constant fast gate\n"
  "	tau_c		(ms)	: time constant calcium binding \n"
  "        alpha_s		(1/ms)\n"
  "        alpha_f 	(1/ms)\n"
  "        beta_s 		(1/ms)\n"
  "        beta_f		(1/ms)\n"
  "	C\n"
  "	k2		(1/ms)\n"
  "	tadj\n"
  "	s0			: fraction of closed slow gates \n"
  "	f0			: fraction of closed fast gates\n"
  "}\n"
  "\n"
  "BREAKPOINT { \n"
  "	SOLVE states METHOD cnexp\n"
  "	ih = ghbar * (s1+s2) * (f1+f2) * (v-eh)\n"
  "}\n"
  "\n"
  "UNITSOFF\n"
  "DERIVATIVE states { \n"
  "	evaluate_fct(v,cai)\n"
  "\n"
  "	s1' = alpha_s*s0 - beta_s*s1 + k2*(s2-C*s1)\n"
  "        f1' = alpha_f*f0 - beta_f*f1 + k2*(f2-C*f1)\n"
  "        s2' = -k2*(s2-C*s1)\n"
  "        f2' = -k2*(f2-C*f1)\n"
  "\n"
  "        s0 = 1-s1-s2\n"
  "        f0 = 1-f1-f2\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	: Q10 assumed to be 3\n"
  "	tadj = 3^((celsius-35.5)/10)\n"
  "	evaluate_fct(v,cai)\n"
  "\n"
  "	s1 = alpha_s / (beta_s+alpha_s*(1+C))\n"
  "	s2 = alpha_s*C / (beta_s+alpha_s*(1+C))\n"
  "	s0 = 1-s1-s2\n"
  "	f1 = alpha_f / (beta_f+alpha_f*(1+C))\n"
  "	f2 = alpha_f*C / (beta_f+alpha_f*(1+C))\n"
  "	f0 = 1-f1-f2\n"
  "\n"
  "	tau_c = 1 / (1+C) / k2	: for plotting purposes\n"
  "}\n"
  "\n"
  "PROCEDURE evaluate_fct( v(mV), cai(mM)) {\n"
  "	h_inf = 1 / (1+exp((v+68.9)/6.5))\n"
  "	tau_s = exp((v+183.6)/15.24) / tadj\n"
  "	tau_f = exp((v+158.6)/11.2) / (1+exp((v+75)/5.5)) / tadj\n"
  "\n"
  "	alpha_s = h_inf / tau_s \n"
  "	alpha_f = h_inf / tau_f \n"
  "	beta_s = (1-h_inf) / tau_s\n"
  "	beta_f = (1-h_inf) / tau_f\n"
  "\n"
  "        C = cai*cai/(cac*cac)\n"
  "	k2 = 4e-4 * tadj	\n"
  "}	\n"
  "UNITSON\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  "\n"
  ;
#endif
