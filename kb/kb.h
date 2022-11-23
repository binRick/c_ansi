#pragma once
#ifndef KB_H
#define KB_H
//////////////////////////////////////
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "hash/hash.h"
#include "libcyaml/include/cyaml/cyaml.h"
#include "parson/parson.h"
#include "vips/vips.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
enum kb_csv_cols_t {
  KB_CSV_COL_CHARACTER,
  KB_CSV_COL_X,
  KB_CSV_COL_Y,
  KB_CSV_COL_WIDTH,
  KB_CSV_COL_HEIGHT,
  KB_CSV_COLS_QTY,
};
const char *kb_required_keys[]       = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
}; const size_t kb_required_keys_qty = sizeof(kb_required_keys) / sizeof(kb_required_keys[0]);
struct kb_location_t *kb_get_location_key(char *key);
const char *csv_fmt_cols[] = {
  [KB_CSV_COL_CHARACTER] = "%s",
  [KB_CSV_COL_X]         = "%lu",
  [KB_CSV_COL_Y]         = "%lu",
  [KB_CSV_COL_WIDTH]     = "%lu",
  [KB_CSV_COL_HEIGHT]    = "%lu",
};
const char *csv_cols[] = {
  [KB_CSV_COL_CHARACTER] = "character",
  [KB_CSV_COL_X]         = "x",
  [KB_CSV_COL_Y]         = "y",
  [KB_CSV_COL_WIDTH]     = "width",
  [KB_CSV_COL_HEIGHT]    = "height",
};
struct kb_location_t {
  const char *character, *assets_path, *format;
  int        x, y, width, height;
  VipsImage  *vip;
};
struct kb_locations_t {
  char                 *name;
  struct kb_location_t *locations;
  size_t               locations_count;
};
//////////////////////////////////////
JSON_Value *get_locations_value(void);
JSON_Array *get_locations_array(void);
size_t get_locations_qty(void);
char *get_locations_str(void);
const cyaml_schema_field_t kb_location_schema[] = {
  CYAML_FIELD_STRING_PTR("character", CYAML_FLAG_POINTER, struct kb_location_t, character, 0, CYAML_UNLIMITED),
  CYAML_FIELD_INT("x",                CYAML_FLAG_DEFAULT, struct kb_location_t, x),
  CYAML_FIELD_INT("y",                CYAML_FLAG_DEFAULT, struct kb_location_t, y),
  CYAML_FIELD_INT("width",            CYAML_FLAG_DEFAULT, struct kb_location_t, width),
  CYAML_FIELD_INT("height",           CYAML_FLAG_DEFAULT, struct kb_location_t, height),
  CYAML_FIELD_END,
};
const cyaml_schema_field_t kb_locations_schema[] = {
  CYAML_FIELD_SEQUENCE("locations", CYAML_FLAG_POINTER, struct kb_locations_t, locations, &kb_location_schema, 0, CYAML_UNLIMITED),
  CYAML_FIELD_END,
};
const cyaml_schema_value_t top_schema = {
  CYAML_VALUE_MAPPING(CYAML_FLAG_POINTER, struct kb_locations_t, kb_locations_schema),
};
const cyaml_config_t       config = {
  .log_fn    = cyaml_log,
  .mem_fn    = cyaml_mem,
  .log_level = CYAML_LOG_WARNING,
};
enum kb_csv_cols_t kb_csv_col_name_id(const char *name);
char *kb_csv_col_stringify(enum kb_csv_cols_t col, void *data);
void kb_parse_config(const char *config);
char *kb_get_config_json(void);
char *kb_get_config_yaml(void);
char *kb_get_config_csv(void);
char *kb_get_assets_path(char *character, char *format);
char **kb_get_missing_keys(int *qty);
char **kb_get_csv_lines(int *qty);
hash_t *kb_get_csv_hash(void);
struct kb_location_t **kb_get_locations(int *qty);
VipsImage **kb_get_location_images(struct kb_location_t **, int qty, int *vips_qty);
#endif
