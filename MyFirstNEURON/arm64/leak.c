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
 
#define nrn_init _nrn_init__leak
#define _nrn_initial _nrn_initial__leak
#define nrn_cur _nrn_cur__leak
#define _nrn_current _nrn_current__leak
#define nrn_jacob _nrn_jacob__leak
#define nrn_state _nrn_state__leak
#define _net_receive _net_receive__leak 
 
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
#define pna _p[0]
#define pna_columnindex 0
#define pk _p[1]
#define pk_columnindex 1
#define pca _p[2]
#define pca_columnindex 2
#define pcl _p[3]
#define pcl_columnindex 3
#define pmg _p[4]
#define pmg_columnindex 4
#define ina _p[5]
#define ina_columnindex 5
#define ik _p[6]
#define ik_columnindex 6
#define ica _p[7]
#define ica_columnindex 7
#define icl _p[8]
#define icl_columnindex 8
#define img _p[9]
#define img_columnindex 9
#define nai _p[10]
#define nai_columnindex 10
#define nao _p[11]
#define nao_columnindex 11
#define ki _p[12]
#define ki_columnindex 12
#define ko _p[13]
#define ko_columnindex 13
#define cai _p[14]
#define cai_columnindex 14
#define cao _p[15]
#define cao_columnindex 15
#define cli _p[16]
#define cli_columnindex 16
#define clo _p[17]
#define clo_columnindex 17
#define mgi _p[18]
#define mgi_columnindex 18
#define mgo _p[19]
#define mgo_columnindex 19
#define v _p[20]
#define v_columnindex 20
#define _g _p[21]
#define _g_columnindex 21
#define _ion_nai	*_ppvar[0]._pval
#define _ion_nao	*_ppvar[1]._pval
#define _ion_ina	*_ppvar[2]._pval
#define _ion_dinadv	*_ppvar[3]._pval
#define _ion_ki	*_ppvar[4]._pval
#define _ion_ko	*_ppvar[5]._pval
#define _ion_ik	*_ppvar[6]._pval
#define _ion_dikdv	*_ppvar[7]._pval
#define _ion_cai	*_ppvar[8]._pval
#define _ion_cao	*_ppvar[9]._pval
#define _ion_ica	*_ppvar[10]._pval
#define _ion_dicadv	*_ppvar[11]._pval
#define _ion_cli	*_ppvar[12]._pval
#define _ion_clo	*_ppvar[13]._pval
#define _ion_icl	*_ppvar[14]._pval
#define _ion_dicldv	*_ppvar[15]._pval
#define _ion_mgi	*_ppvar[16]._pval
#define _ion_mgo	*_ppvar[17]._pval
#define _ion_img	*_ppvar[18]._pval
#define _ion_dimgdv	*_ppvar[19]._pval
 
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
 static void _hoc_ghk(void);
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
 "setdata_leak", _hoc_setdata,
 "ghk_leak", _hoc_ghk,
 0, 0
};
#define ghk ghk_leak
 extern double ghk( _threadargsprotocomma_ double , double , double , double );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "pna_leak", "cm/s",
 "pk_leak", "cm/s",
 "pca_leak", "cm/s",
 "pcl_leak", "cm/s",
 "pmg_leak", "cm/s",
 "ina_leak", "mA/cm2",
 "ik_leak", "mA/cm2",
 "ica_leak", "mA/cm2",
 "icl_leak", "mA/cm2",
 "img_leak", "mA/cm2",
 0,0
};
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
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
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"leak",
 "pna_leak",
 "pk_leak",
 "pca_leak",
 "pcl_leak",
 "pmg_leak",
 0,
 "ina_leak",
 "ik_leak",
 "ica_leak",
 "icl_leak",
 "img_leak",
 0,
 0,
 0};
 static Symbol* _na_sym;
 static Symbol* _k_sym;
 static Symbol* _ca_sym;
 static Symbol* _cl_sym;
 static Symbol* _mg_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 22, _prop);
 	/*initialize range parameters*/
 	pna = 2.07e-07;
 	pk = 3.45e-06;
 	pca = 0;
 	pcl = 0;
 	pmg = 0;
 	_prop->param = _p;
 	_prop->param_size = 22;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 20, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* nai */
 	_ppvar[1]._pval = &prop_ion->param[2]; /* nao */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[4]._pval = &prop_ion->param[1]; /* ki */
 	_ppvar[5]._pval = &prop_ion->param[2]; /* ko */
 	_ppvar[6]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[7]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[8]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[9]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[10]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[11]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 prop_ion = need_memb(_cl_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[12]._pval = &prop_ion->param[1]; /* cli */
 	_ppvar[13]._pval = &prop_ion->param[2]; /* clo */
 	_ppvar[14]._pval = &prop_ion->param[3]; /* icl */
 	_ppvar[15]._pval = &prop_ion->param[4]; /* _ion_dicldv */
 prop_ion = need_memb(_mg_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[16]._pval = &prop_ion->param[1]; /* mgi */
 	_ppvar[17]._pval = &prop_ion->param[2]; /* mgo */
 	_ppvar[18]._pval = &prop_ion->param[3]; /* img */
 	_ppvar[19]._pval = &prop_ion->param[4]; /* _ion_dimgdv */
 
}
 static void _initlists();
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _leak_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("na", -10000.);
 	ion_reg("k", -10000.);
 	ion_reg("ca", -10000.);
 	ion_reg("cl", 1.0);
 	ion_reg("mg", 2.0);
 	_na_sym = hoc_lookup("na_ion");
 	_k_sym = hoc_lookup("k_ion");
 	_ca_sym = hoc_lookup("ca_ion");
 	_cl_sym = hoc_lookup("cl_ion");
 	_mg_sym = hoc_lookup("mg_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 22, 20);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 6, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 7, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 8, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 9, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 10, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 11, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 12, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 13, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 14, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 15, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 16, "mg_ion");
  hoc_register_dparam_semantics(_mechtype, 17, "mg_ion");
  hoc_register_dparam_semantics(_mechtype, 18, "mg_ion");
  hoc_register_dparam_semantics(_mechtype, 19, "mg_ion");
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 leak /Users/mehow/src-uni/neuron/MyFirstNEURON/leak.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96480.0;
 static double R = 8.314;
static int _reset;
static char *modelname = "passive sodium, potassium, calcium, chloride and magnesium channels";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
double ghk ( _threadargsprotocomma_ double _lv , double _lci , double _lco , double _lz ) {
   double _lghk;
 double _le , _lw ;
 _lw = _lv * ( .001 ) * _lz * FARADAY / ( R * ( celsius + 273.16 ) ) ;
   if ( fabs ( _lw ) > 1e-4 ) {
     _le = _lw / ( exp ( _lw ) - 1.0 ) ;
     }
   else {
     _le = 1.0 - _lw / 2.0 ;
     }
   _lghk = - ( .001 ) * _lz * FARADAY * ( _lco - _lci * exp ( _lw ) ) * _le ;
   
return _lghk;
 }
 
static void _hoc_ghk(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  ghk ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 hoc_retpushx(_r);
}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 2);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 3, 4);
   nrn_update_ion_pointer(_k_sym, _ppvar, 4, 1);
   nrn_update_ion_pointer(_k_sym, _ppvar, 5, 2);
   nrn_update_ion_pointer(_k_sym, _ppvar, 6, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 7, 4);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 8, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 9, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 10, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 11, 4);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 12, 1);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 13, 2);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 14, 3);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 15, 4);
   nrn_update_ion_pointer(_mg_sym, _ppvar, 16, 1);
   nrn_update_ion_pointer(_mg_sym, _ppvar, 17, 2);
   nrn_update_ion_pointer(_mg_sym, _ppvar, 18, 3);
   nrn_update_ion_pointer(_mg_sym, _ppvar, 19, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{

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
  nai = _ion_nai;
  nao = _ion_nao;
  ki = _ion_ki;
  ko = _ion_ko;
  cai = _ion_cai;
  cao = _ion_cao;
  cli = _ion_cli;
  clo = _ion_clo;
  mgi = _ion_mgi;
  mgo = _ion_mgo;
 initmodel(_p, _ppvar, _thread, _nt);
     }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   ina = pna * ghk ( _threadargscomma_ v , nai , nao , 1.0 ) ;
   ik = pk * ghk ( _threadargscomma_ v , ki , ko , 1.0 ) ;
   ica = pca * ghk ( _threadargscomma_ v , cai , cao , 2.0 ) ;
   icl = pcl * ghk ( _threadargscomma_ v , cli , clo , - 1.0 ) ;
   img = pmg * ghk ( _threadargscomma_ v , mgi , mgo , 2.0 ) ;
   }
 _current += ina;
 _current += ik;
 _current += ica;
 _current += icl;
 _current += img;

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
  nai = _ion_nai;
  nao = _ion_nao;
  ki = _ion_ki;
  ko = _ion_ko;
  cai = _ion_cai;
  cao = _ion_cao;
  cli = _ion_cli;
  clo = _ion_clo;
  mgi = _ion_mgi;
  mgo = _ion_mgo;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dimg;
 double _dicl;
 double _dica;
 double _dik;
 double _dina;
  _dina = ina;
  _dik = ik;
  _dica = ica;
  _dicl = icl;
  _dimg = img;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dinadv += (_dina - ina)/.001 ;
  _ion_dikdv += (_dik - ik)/.001 ;
  _ion_dicadv += (_dica - ica)/.001 ;
  _ion_dicldv += (_dicl - icl)/.001 ;
  _ion_dimgdv += (_dimg - img)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
  _ion_ik += ik ;
  _ion_ica += ica ;
  _ion_icl += icl ;
  _ion_img += img ;
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

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/mehow/src-uni/neuron/MyFirstNEURON/leak.mod";
static const char* nmodl_file_text = 
  "TITLE passive sodium, potassium, calcium, chloride and magnesium channels\n"
  "\n"
  "COMMENT\n"
  "        Assembled for MyFirstNEURON by Arthur Houweling\n"
  "ENDCOMMENT\n"
  "\n"
  "INDEPENDENT { t FROM 0 TO 1 WITH 1 (ms) }\n"
  "\n"
  "UNITS {\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "	(mM) = (milli/liter)\n"
  "        FARADAY = 96480 (coul)\n"
  "        R       = 8.314 (volt-coul/degC)\n"
  "}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX leak\n"
  "	USEION na READ nai,nao WRITE ina\n"
  "	USEION k READ ki,ko WRITE ik\n"
  "	USEION ca READ cai,cao WRITE ica\n"
  "        USEION cl READ cli,clo WRITE icl VALENCE 1 \n"
  "	: negative valence not accepted\n"
  "	: if 'ecl' is needed in a MOD-file use '-ecl' instead\n"
  "        USEION mg READ mgi,mgo WRITE img VALENCE 2\n"
  "	RANGE pna,pk,pca,pcl,pmg,ina,ik,ica,icl,img\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	v		(mV)	\n"
  "        celsius		(degC)\n"
  "	nai		(mM)\n"
  "	nao		(mM)\n"
  "	pna= 2.07e-7	(cm/s)\n"
  "        ki      	(mM)\n"
  "        ko      	(mM)\n"
  "        pk= 3.45e-6	(cm/s)\n"
  "        cai     	(mM)\n"
  "        cao     	(mM)\n"
  "        pca= 0		(cm/s)\n"
  "        cli     	(mM)\n"
  "        clo     	(mM)\n"
  "        pcl= 0		(cm/s)\n"
  "        mgi     	(mM)\n"
  "        mgo     	(mM)\n"
  "        pmg= 0		(cm/s)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	ina	(mA/cm2)\n"
  "	ik      (mA/cm2)\n"
  "	ica	(mA/cm2)\n"
  "        icl     (mA/cm2)\n"
  "	img	(mA/cm2)\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	ina = pna * ghk(v,nai,nao,1)\n"
  "        ik = pk * ghk(v,ki,ko,1)\n"
  "        ica = pca * ghk(v,cai,cao,2)\n"
  "        icl = pcl * ghk(v,cli,clo,-1)\n"
  "        img = pmg * ghk(v,mgi,mgo,2)\n"
  "}\n"
  "\n"
  "FUNCTION ghk( v(mV), ci(mM), co(mM), z)  (millicoul/cm3) { LOCAL e, w\n"
  "        w = v * (.001) * z*FARADAY / (R*(celsius+273.16))\n"
  "        if (fabs(w)>1e-4) \n"
  "          { e = w / (exp(w)-1) }\n"
  "        else \n"
  "	: denominator is small -> Taylor series\n"
  "          { e = 1-w/2 }\n"
  "        ghk = - (.001) * z*FARADAY * (co-ci*exp(w)) * e\n"
  "}\n"
  "\n"
  ;
#endif
