#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _CaT_reg(void);
extern void _htc_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"CaT.mod\"");
    fprintf(stderr, " \"htc.mod\"");
    fprintf(stderr, "\n");
  }
  _CaT_reg();
  _htc_reg();
}

#if defined(__cplusplus)
}
#endif
