///////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
///////////////////////////////
#include "emojis-test/emojis-test.h"
#include "emojis/emojis.h"
#include "submodules/c_greatest/greatest/greatest.h"
#include "bench/bench.h"
///////////////////////////////
TEST t_list_emojis_t_h(void){
  PASS();
}

TEST t_list_emojis_t_v(void){
  struct Vector *emojis;
  BENCHMARK_QTY(benchmark_list_emojis, 20)
  emojis = get_emojis_t_v();  
  END_BENCHMARK(benchmark_list_emojis)
  struct emojis_t *e;
  for(size_t i=0;i<vector_size(emojis);i++)  {
    e = get_emoji_t(i);
    printf(" #%.5lu %s -> %s (%lu chars)\n",i,e->name,e->emoji,e->chars);
  }
  printf("%lu emojis\n",vector_size(emojis));
  BENCHMARK_SUMMARY(benchmark_list_emojis);
  PASS();
}

TEST t_list_emojis_qty(void){
  printf("%lu emojis\n",get_emojis_qty());  
  PASS();
}

TEST t_list_emojis_names(void){
  size_t id = 0;
  struct Vector *emojis_names_v = get_emojis_names_v();
  printf("%lu emoji names\n",vector_size(emojis_names_v));
  struct emojis_t *e = get_emoji_t(id);
  printf("%lu: %s\n",id, e->name);
    
  PASS();
}

SUITE(s_list_emojis_names) {
  RUN_TEST(t_list_emojis_t_v);
  RUN_TEST(t_list_emojis_names);
  RUN_TEST(t_list_emojis_qty);
  RUN_TEST(t_list_emojis_t_h);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_list_emojis_names);    
} /* main */
