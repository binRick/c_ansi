#include "emojis-test/emojis-test.h"
#include "emojis/emojis.h"
#include "greatest/greatest.h"

TEST t_list_emojis_v(void){
  struct Vector *emojis = get_emojis_v();  
  for(size_t i=0;i<vector_size(emojis);i++)  {
    struct emojis_t *e = get_emoji_t(i);
    printf(" #%lu: %s|%s\n",i,e->name,e->emoji);
  }
  printf("%lu emojis\n",vector_size(emojis));
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
  RUN_TEST(t_list_emojis_qty);
  RUN_TEST(t_list_emojis_names);
  RUN_TEST(t_list_emojis_v);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_list_emojis_names);    
} /* main */
