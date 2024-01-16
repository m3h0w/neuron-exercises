#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _HH1_reg(void);
extern void _HH2_reg(void);
extern void _ampa_reg(void);
extern void _ampa2_reg(void);
extern void _cadyn_reg(void);
extern void _gabaA_reg(void);
extern void _gabaA2_reg(void);
extern void _gabaB_reg(void);
extern void _gabaB2_reg(void);
extern void _ia_reg(void);
extern void _iahp_reg(void);
extern void _iahp2_reg(void);
extern void _ic_reg(void);
extern void _ican_reg(void);
extern void _ih_reg(void);
extern void _il_reg(void);
extern void _im_reg(void);
extern void _it_reg(void);
extern void _it2_reg(void);
extern void _leak_reg(void);
extern void _nmda_reg(void);
extern void _nmda2_reg(void);
extern void _synstim_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"HH1.mod\"");
    fprintf(stderr, " \"HH2.mod\"");
    fprintf(stderr, " \"ampa.mod\"");
    fprintf(stderr, " \"ampa2.mod\"");
    fprintf(stderr, " \"cadyn.mod\"");
    fprintf(stderr, " \"gabaA.mod\"");
    fprintf(stderr, " \"gabaA2.mod\"");
    fprintf(stderr, " \"gabaB.mod\"");
    fprintf(stderr, " \"gabaB2.mod\"");
    fprintf(stderr, " \"ia.mod\"");
    fprintf(stderr, " \"iahp.mod\"");
    fprintf(stderr, " \"iahp2.mod\"");
    fprintf(stderr, " \"ic.mod\"");
    fprintf(stderr, " \"ican.mod\"");
    fprintf(stderr, " \"ih.mod\"");
    fprintf(stderr, " \"il.mod\"");
    fprintf(stderr, " \"im.mod\"");
    fprintf(stderr, " \"it.mod\"");
    fprintf(stderr, " \"it2.mod\"");
    fprintf(stderr, " \"leak.mod\"");
    fprintf(stderr, " \"nmda.mod\"");
    fprintf(stderr, " \"nmda2.mod\"");
    fprintf(stderr, " \"synstim.mod\"");
    fprintf(stderr, "\n");
  }
  _HH1_reg();
  _HH2_reg();
  _ampa_reg();
  _ampa2_reg();
  _cadyn_reg();
  _gabaA_reg();
  _gabaA2_reg();
  _gabaB_reg();
  _gabaB2_reg();
  _ia_reg();
  _iahp_reg();
  _iahp2_reg();
  _ic_reg();
  _ican_reg();
  _ih_reg();
  _il_reg();
  _im_reg();
  _it_reg();
  _it2_reg();
  _leak_reg();
  _nmda_reg();
  _nmda2_reg();
  _synstim_reg();
}

#if defined(__cplusplus)
}
#endif
