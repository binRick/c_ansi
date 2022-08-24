////////////////////////////////////////////

////////////////////////////////////////////
#include "iface-test/iface-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "iface-test/croak.h"
#include "iface-test/frog.h"
#include "interface99/interface99.h"

////////////////////////////////////////////
TEST t_iface_test(){
  Frog *paul  = Frog_new("Paul");
  Frog *steve = Frog_new("Steve");

  VCALL(DYN(Frog, Croak, paul), croak);
  VCALL(DYN(Frog, Croak, steve), croak);

  Frog_free(paul);
  Frog_free(steve);
  PASS();
}

SUITE(s_iface_test) {
  RUN_TEST(t_iface_test);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_iface_test);
  GREATEST_MAIN_END();
}
