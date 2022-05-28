#include "ansi-utils.h"


void restore_palette(){
  printf(AC_RESTORE_PALETTE);
}


void save_palette(){
  printf(AC_SAVE_PALETTE);
}

