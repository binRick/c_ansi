#pragma once
#ifndef KB_C
#define KB_C
#define LOCAL_DEBUG_MODE    KB_DEBUG_MODE
////////////////////////////////////////////
#include "kb/kb.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "incbin/incbin.h"
#include "libcyaml/include/cyaml/cyaml.h"
#include "log/log.h"
#include "ms/ms.h"
#include "parson/parson.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "vips/vips.h"
INCBIN(kb_png, "assets/kb.png");
INCBIN(kb_qoir, "assets/kb.qoir");
INCBIN(kb_locations_qoir, "assets/kb_cropped.qoir");
INCBIN(kb_locations_qoi, "assets/kb_cropped.qoi");
INCBIN(kb_locations_png, "assets/kb_cropped.png");
INCBIN(kb_locations_json, "assets/kb_cropped.json");
INCBIN(kb_locations_yaml, "assets/kb_cropped.yaml");
INCBIN(kb_locations_csv, "assets/kb_cropped.csv");
////////////////////////////////////////////
static bool KB_DEBUG_MODE = false;
static double
            red[] = { 255, 0, 0, 255 },
  yellow[]        = { 255, 255, 0, 255 },
  green[]         = { 0, 255, 0, 255 },
  transparent[]   = { 0, 0, 0, 0 }
;
enum kb_color_name_t {
  KB_COLOR_RED,
  KB_COLOR_YELLOW,
  KB_COLOR_GREEN,
  KB_COLOR_TRANSPARENT,
  KB_COLORS_QTY,
};
typedef double kb_color_t[4];
kb_color_t kb_colors[] = {
  [KB_COLOR_RED]         = { 255, 0,   0, 255 },
  [KB_COLOR_YELLOW]      = { 255, 255, 0, 255 },
  [KB_COLOR_GREEN]       = { 0,   255, 0, 255 },
  [KB_COLOR_TRANSPARENT] = { 0,   0,   0, 0   },
};

//kb_color_t kb_color_red = kb_colors[KB_COLOR_RED];
///////////////////////////////////////////////////////////////////////
size_t get_locations_qty(){
  return(100);
//  return(json_object_get_count(get_locations_array()));
}

JSON_Array *get_locations_array(){
  return(json_object_get_array(get_locations_value(), "locations"));
}

void kb_parse_config(const char *config){
  log_info("parsing config %s", bytes_to_string(strlen(config)));
  unsigned long         qty  = 0;
  struct kb_locations_t *loc = calloc(1, sizeof(struct kb_locations_t));
  cyaml_err_t           err;
  /*
     err = cyaml_load_data(config,strlen(config),&config,&top_schema,(struct cyaml_data_t**)&loc,NULL);
     if (err != CYAML_OK) {
      log_error("%s", cyaml_strerror(err));
      exit(EXIT_FAILURE);
     }
   */
  log_info("parsed");
  Dn(loc->locations_count);
}
enum kb_csv_cols_t kb_csv_col_name_id(const char *name){
  for (int i = 0; i < KB_CSV_COLS_QTY; i++)
    if (stringfn_equal(name,
                       csv_cols[i]))
      return(i);

  return(KB_CSV_COLS_QTY);
}

char *kb_csv_col_stringify(enum kb_csv_cols_t col, void *data){
  char *s;

  asprintf(&s, csv_fmt_cols[col], data);
  return(s);
}

hash_t *kb_get_csv_hash(){
  hash_t                 *h  = hash_new();
  int                    qty = 0;
  char                   **lines;
  struct StringFNStrings split;

  lines = kb_get_csv_lines(&qty);
  for (int i = 0; i < qty; i++) {
    split = stringfn_split(lines[i], ',');
    if (split.count != KB_CSV_COLS_QTY) continue;
    hash_t *ch = hash_new();
    for (int x = 0; x < KB_CSV_COLS_QTY; x++)
      switch (x) {
      case KB_CSV_COL_CHARACTER:
        hash_set(h, split.strings[x], (void *)ch);
        hash_set(ch, csv_cols[KB_CSV_COL_CHARACTER], (void *)(strdup(split.strings[x])));
      case KB_CSV_COL_X:
      case KB_CSV_COL_Y:
      case KB_CSV_COL_WIDTH:
      case KB_CSV_COL_HEIGHT:
        hash_set(ch, csv_cols[x], (void *)(size_t)(atoi(split.strings[x])));
        break;
      default:
        hash_set(ch, csv_cols[x], (void *)(strdup(split.strings[x])));
        break;
      }
  }
  return(h);
}

char **kb_get_csv_lines(int *qty){
  struct StringFNStrings lines = stringfn_split_lines_and_trim(kb_get_config_csv());

  *qty = lines.count;
  return(lines.strings);
}

char *kb_get_config_csv(){
  return(gkb_locations_csvData);
}

char *kb_get_config_json(){
  return(gkb_locations_jsonData);
}

char *kb_get_config_yaml(){
  return(gkb_locations_yamlData);
}

char *get_locations_str(){
  return(gkb_locations_yamlData);
}

JSON_Value *get_locations_value(){
  return(json_parse_string(gkb_locations_jsonData));
}
static void __attribute__((constructor)) __constructor__kb(void){
  if (getenv("DEBUG") != NULL || getenv("DEBUG_kb") != NULL) {
    log_debug("Enabling kb Debug Mode");
    KB_DEBUG_MODE = true;
  }
  setenv("TMPDIR", "/tmp/", 1);
}

VipsImage **kb_get_location_images(struct kb_location_t **locs, int qty, int *vips_qty){
  struct Vector        *v = vector_new();
  struct kb_location_t *I;
  VipsImage            *kb;

  if (!(kb = vips_image_new_from_buffer(gkb_locations_pngData, gkb_locations_pngSize, "", NULL))) {
    log_error("Failed to vips parse buffer");
    exit(EXIT_FAILURE);
  }
  vector_push(v, (void *)kb);
  VipsImage *vips_overlay;

  for (int i = 0; i < qty; i++) {
    I = (struct kb_location_t *)locs[i];
    //log_info("acquiring [%s] %dx%d item from %dx%d",I->character,I->width,I->height,I->x,I->y);
    VipsImage *vi, *vo, *vips_overlayed;
    if (!(vi = vips_image_copy_memory(kb))) {
      log_error("copy memory failed");
      exit(EXIT_FAILURE);
    }
    if (vips_crop(vi, &vo, I->x, I->y, I->width, I->height, NULL)) {
      log_error("Crop failed");
      exit(EXIT_FAILURE);
    }
    if (!(vips_overlay = vips_image_new_from_image(vo, kb_colors[KB_COLOR_YELLOW], VIPS_NUMBER(kb_colors[KB_COLOR_YELLOW])))) {
      log_error("vips copy failed");
      exit(EXIT_FAILURE);
    }
    if (vips_draw_rect(vips_overlay,
                       transparent, VIPS_NUMBER(transparent),
                       15, 15, vips_overlay->Xsize - 20, vips_overlay->Ysize - 20,
                       "fill", true,
                       NULL)) {
      log_error("vips rect draw failed");
      exit(EXIT_FAILURE);
    }
    if (vips_composite2(vo, vips_overlay, &vips_overlayed, VIPS_BLEND_MODE_OVER, NULL)) {
      log_error("vips composite failed");
      exit(EXIT_FAILURE);
    }
    vector_push(v, (void *)vips_overlayed);
    //log_info("cropped %dx%d image",vips_image_get_width(vi),vips_image_get_height(vi));
  }
  *vips_qty = vector_size(v);
  return(vector_to_array(v));
} /* kb_get_location_images */

struct kb_location_t *kb_get_location_key(char *key){
  int                  qty = 0;
  struct kb_location_t **l = kb_get_locations(&qty);

  for (int i = 0; i < qty; i++)
    if (stringfn_equal(l[i]->character, key))
      return(l[i]);

  return(NULL);
}
struct kb_location_t **kb_get_locations(int *qty){
  char          *format = "png";
  hash_t        *h = kb_get_csv_hash(), *ih;
  struct Vector *v = vector_new();
  int           vips_qty = 0, i = 0;
  VipsImage     **vips = kb_get_location_images(vector_to_array(v), vector_size(v), &vips_qty);

  hash_each(h, {
    ih                      = (hash_t *)val;
    struct kb_location_t *l = calloc(1, sizeof(struct kb_location_t));
    l->character            = (char *)key;
    l->width                = (int)(size_t)hash_get(ih, "width");
    l->height               = (int)(size_t)hash_get(ih, "height");
    l->x                    = (int)(size_t)hash_get(ih, "x");
    l->y                    = (int)(size_t)hash_get(ih, "y");
    l->vip                  = vips[i] ? vips[i] : 0;
    l->format               = format;
    l->assets_path          = kb_get_assets_path(l->character, l->format);
    i++;
    vector_push(v, (void *)l);
  });

  *qty = vector_size(v);
  return(vector_to_array(v));
}

char *kb_get_assets_path(char *character, char *format){
  char *s;

  asprintf(&s, "%s/kb_cropped_assets/character-%s.%s", "kb/assets", character, format);
  return(s);
}

char **kb_get_missing_keys(int *qty){
  struct kb_location_t *I;
  struct Vector        *v = vector_new();

  for (int i = 0; i < kb_required_keys_qty; i++)
    if (!(I = kb_get_location_key(kb_required_keys[i]))) {
      log_warn("Failed to get location for key \"%s\"", kb_required_keys[i]);
      vector_push(v, (void *)strdup(kb_required_keys[i]));
    }
  *qty = vector_size(v);
  return(vector_to_array(v));
}
////////////////////////////////////////////
#undef LOCAL_DEBUG_MODE
#endif
