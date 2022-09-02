#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/////////////////////////////////////
#include "emojis/emojis.h"
#include "wcwidth/wcwidth.h"
/////////////////////////////////////
static struct Vector *__emojis_t = NULL, *__emojis_names_v = NULL;
static size_t        emojis_qty = 0;
/////////////////////////////////////
struct emojis_t *get_emoji_t_by_name(const char *name){
  int i = get_emoji_t_index_by_name(name);

  if (i < 0) {
    return(NULL);
  }
  return(get_emoji_t(i));
}

int get_emoji_t_index_by_name(const char *name){
  for (size_t i = 0; i < get_emojis_qty(); i++) {
    if (strcmp(get_emoji_t(i)->name, name) == 0) {
      return(i);
    }
  }
  return(-1);
}

size_t get_emojis_t_qty(){
  return(vector_size(get_emojis_t_v()));
}
struct Vector *get_emojis_t_v(){
  if (__emojis_t != NULL) {
    return(__emojis_t);
  }
  struct Vector *v = vector_new();
  for (size_t i = 0; i < get_emojis_qty(); i++) {
    vector_push(v, (struct emojis_t *)get_emoji_t(i));
  }
  __emojis_t = v;
  return(__emojis_t);
}

char **emojis_emojis_a(){
  return(vector_to_array(get_emojis_emojis_v()));
}

struct Vector *get_emojis_emojis_v(){
  if (__emojis_names_v != NULL) {
    return(__emojis_names_v);
  }
  struct Vector *v = vector_new();
  for (size_t i = 0; i < get_emojis_qty(); i++) {
    vector_push(v, (char *)(get_emoji_t(i)->emoji));
  }
  __emojis_names_v = v;
  return(__emojis_names_v);
}

struct Vector *get_emojis_names_v(){
  if (__emojis_names_v != NULL) {
    return(__emojis_names_v);
  }
  struct Vector *v = vector_new();
  for (size_t i = 0; i < get_emojis_qty(); i++) {
    vector_push(v, (char *)(get_emoji_t(i)->name));
  }
  __emojis_names_v = v;
  return(__emojis_names_v);
}

struct emojis_t *get_emoji_t(size_t index){
  if (index >= get_emojis_qty()) {
    return(NULL);
  }
  emojis_t *e = &(emojis_table[index]);
  e->chars   = strlen(e->emoji);
  e->wcwidth = string_width(e->emoji);
  return(e);
}

size_t get_emojis_qty(){
  if (emojis_qty > 0) {
    return(emojis_qty);
  }
  emojis_qty = sizeof(emojis_table) / sizeof(emojis_table[0]);
  return(emojis_qty);
}
