#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/////////////////////////////////////
#include "emojis/emojis.h"
/////////////////////////////////////
static struct Vector *__emojis_t = NULL, *__emojis_names_v = NULL;
static size_t emojis_qty = 0;
static struct djbhash __emojis_h = { NULL };
/////////////////////////////////////
struct emojis_t *get_emoji_t_by_name(const char *name){
    int i = get_emoji_t_index_by_name(name);
    if(i<0)
        return NULL;
    return(get_emoji_t(i));
}
int get_emoji_t_index_by_name(const char *name){
struct Vector *emojis = get_emojis_t_v();
    for(size_t i=0;i<get_emojis_qty();i++)
        if(strcmp(get_emoji_t(i)->name,name)==0)
           return(i);
    return(-1);
}
struct Vector *get_emojis_t_v(){
    if(__emojis_t != NULL)
        return(__emojis_t);
    struct Vector *v = vector_new();
    for(size_t i=0;i<get_emojis_qty();i++)
        vector_push(v,(struct emojis_t*)get_emoji_t(i));
    __emojis_t = v;
    return(__emojis_t);
}

struct Vector *get_emojis_names_v(){
    if(__emojis_names_v != NULL)
        return(__emojis_names_v);
    struct Vector *v = vector_new();
    for(size_t i=0;i<get_emojis_qty();i++)
        vector_push(v,(char*)(get_emoji_t(i)->name));
    __emojis_names_v = v;
    return(__emojis_names_v);
}

struct emojis_t *get_emoji_t(size_t index){
    if(index>=get_emojis_qty())
        return NULL;
    emojis_t *e = &(emojis_table[index]);
    e->chars = strlen(e->emoji);
    return(e);
}

size_t get_emojis_qty(){
    if(emojis_qty>0)
        return(emojis_qty);
    emojis_qty = sizeof(emojis_table)/sizeof(emojis_table[0]);
    return(emojis_qty);
}





