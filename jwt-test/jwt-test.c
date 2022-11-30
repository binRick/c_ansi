
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_eventemitter/include/eventemitter.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "chan/src/chan.h"
#include "chan/src/queue.h"
#include "incbin/incbin.h"
#include "jwt-test/jwt-test.h"
#include "jwt.h"
#include "log/log.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "ms/ms.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"

TEST t_jwt_test1(){
  char          *opt_key_name = "test-rsa256.pem";
  int           free_key = 0;
  jwt_alg_t     opt_alg = JWT_ALG_RS256;
  time_t        iat = time(NULL);
  char          *k = NULL, *v = NULL;
  int           claims_count = 0;
  int           i            = 0;
  unsigned char key[10240];
  size_t        key_len = 0;
  FILE          *fp_priv_key;
  int           ret  = 0;
  jwt_t         *jwt = NULL;
  struct kv {
    char *key;
    char *val;
  } opt_claims[100];

  memset(opt_claims, 0, sizeof(opt_claims));
  char *opt_json = NULL;

  opt_claims[0].key = "name";
  opt_claims[0].val = "richard";
  claims_count++;

  asprintf(&opt_json, "{\"name\":\"%s\"}", "richard");

  ret = jwt_new(&jwt);
  if (ret != 0 || jwt == NULL) {
    fprintf(stderr, "invalid jwt\n");
    FAIL();
  }
  ret = jwt_add_grant_int(jwt, "iat", iat);
  for (i = 0; i < claims_count; i++) {
    fprintf(stderr, "Adding claim %s with value %s\n", opt_claims[i].key, opt_claims[i].val);
    jwt_add_grant(jwt, opt_claims[i].key, opt_claims[i].val);
  }
  ret = jwt_add_grants_json(jwt, opt_json);
  if (ret != 0) {
    fprintf(stderr, "Input json is invalid\n");
    FAIL();
  }
  ret = jwt_set_alg(jwt, opt_alg, opt_alg == JWT_ALG_NONE ? NULL : key, opt_alg == JWT_ALG_NONE ? 0 : key_len);
  if (ret < 0) {
    fprintf(stderr, "jwt incorrect algorithm\n");
    FAIL();
  }

  jwt_dump_fp(jwt, stderr, 1);

  fprintf(stderr, "jwt algo %s!\n", jwt_alg_str(opt_alg));

  char *out = jwt_encode_str(jwt);

  printf("%s\n", out);

  jwt_free_str(out);

  if (opt_json != NULL)
    free(opt_json);

  jwt_free(jwt);

  if (free_key)
    free(opt_key_name);

  PASS();
} /* t_jwt_test1 */

SUITE(s_jwt_test) {
  RUN_TEST(t_jwt_test1);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_jwt_test);
  GREATEST_MAIN_END();
}
