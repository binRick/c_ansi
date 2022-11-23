
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "kb-test/kb-test.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "kb/kb.h"
#include "vips/vips.h"


TEST t_kb_parse_config(void *cfg){
  kb_parse_config((char*)cfg);
  PASS();
  char *s;
  asprintf(&s,"");
  PASSm(s);

}
TEST t_kb_get_missing_keys(){
  int qty=0;
  kb_get_missing_keys(&qty);
  PASS();
}
TEST t_kb_write_location_images(){
  char *fmt="png";
  int vqty=0,qty=0;
  VipsImage *vips;
  struct kb_location_t **l=kb_get_locations(&qty);
  ASSERT_GTm("Zero Locations Acquired",qty,0);
  ASSERT_NEQm("Invalid Locations Array", l,NULL);
  VipsImage **v=kb_get_location_images(l,qty,&vqty);
  ASSERT_GTm("Failed to acquire images",vqty,0);
  ASSERT_NEQm("Invalid VipsImages Array",v,NULL);
  for(int i=0;i<vqty;i++){
    size_t len=0;
    vips=v[i];
    Ds(l[i]->assets_path);
    fsio_mkdirs_parent(l[i]->assets_path,0700);
    if(!fsio_file_exists(l[i]->assets_path))
      if(vips_image_write_to_file(vips,l[i]->assets_path,NULL))
        FAIL();
    len=fsio_file_size(l[i]->assets_path);
    ASSERT_GTm("Invalid vips write file size",len,0);
  }

  char *s;
  asprintf(&s,"Processed %d vips images",vqty);
  PASSm(s);
}
TEST t_kb_location_images(){
  int vqty=0,qty=0;
  struct kb_location_t **l=kb_get_locations(&qty);
  ASSERT_GTm("Zero Locations Acquired",qty,0);
  ASSERT_NEQm("Invalid Locations Array", l,NULL);
  VipsImage **v=kb_get_location_images(l,qty,&vqty);
  ASSERT_GTm("Failed to acquire images",vqty,0);
  ASSERT_NEQm("Invalid VipsImages Array",v,NULL);
  char *s;
  asprintf(&s,"Processed %d vips images",vqty);
  PASSm(s);
}
TEST t_kb_locations(){
  int qty=0;
  struct kb_location_t **l=kb_get_locations(&qty);
  ASSERT_GTm("Zero Locations Acquired",qty,0);
  ASSERT_NEQm("Invalid Locations Array", l,NULL);
  char *s;
  asprintf(&s,"Acquired %d locations",qty);
  for(int i=0;i<qty;i++){
    log_info("%s |%dx%d|%dx%d|", l[i]->character,l[i]->width,l[i]->height,l[i]->x,l[i]->y);
  }
  PASSm(s);
}
TEST t_kb_csv_hash(){
  hash_t *h = kb_get_csv_hash();
  hash_t *ih;
  hash_each(h,{
    Ds(key);
    ih=(struct hash_t*)val;
    hash_each(ih,{
        int id=kb_csv_col_name_id(key);
        Di(id);
        char *str;
        //= kb_csv_col_stringify(id, val);
        //Ds(str);
      Ds(key);
        });
      });
  PASS();
}
TEST t_kb_csv_lines(){
  int qty=0;
  char **lines;

  lines=kb_get_csv_lines(&qty);
  ASSERT_GTE(qty,1);
  for(int i=0;i<qty;i++)
    Ds(lines[i]);

  PASS();
}
TEST t_kb_cat_config(void *cfg){
  ASSERT_NEQ((char*)cfg,NULL);
  PASSm((char*)cfg);
}

SUITE(s_kb_test) {
  RUN_TESTp(t_kb_cat_config, (void*)kb_get_config_json());
  RUN_TESTp(t_kb_cat_config,(void*)kb_get_config_yaml());
  RUN_TESTp(t_kb_cat_config,(void*)kb_get_config_csv());
  RUN_TEST(t_kb_csv_lines);
  RUN_TEST(t_kb_csv_hash);
  RUN_TESTp(t_kb_parse_config,(void*)kb_get_config_yaml());
  RUN_TEST(t_kb_locations);
  RUN_TEST(t_kb_location_images);
  RUN_TEST(t_kb_write_location_images);
  RUN_TEST(t_kb_get_missing_keys);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_kb_test);
  GREATEST_MAIN_END();
}
