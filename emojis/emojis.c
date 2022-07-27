#pragma once
/////////////////////////////////////
#include "emojis/emojis.h"
/////////////////////////////////////


struct Vector *get_emojis_v(){
    struct Vector *v = vector_new();
    for(size_t i=0;i<get_emojis_qty();i++)
        vector_push(v,(struct emojis_t*)get_emoji_t(i));
    return(v);
}

struct Vector *get_emojis_names_v(){
    struct Vector *v = vector_new();
    for(size_t i=0;i<get_emojis_qty();i++)
        vector_push(v,(char*)(get_emoji_t(i)->name));
    return(v);
}

struct emojis_t *get_emoji_t(size_t index){
    if(index>=emojis_table_qty)
        return NULL;
    emojis_t *e = &(emojis_table[index]);
    return(e);
}

size_t get_emojis_qty(){
    return(emojis_table_qty);
}





