#pragma once
/////////////////////////////////////////////////////
#include <stdlib.h>
#include <string.h>
/////////////////////////////////////////////////////
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "string-utils/string-utils.h"
/////////////////////////////////////////////////////

char *int_to_string(const int b){
      struct StringBuffer *sb = stringbuffer_new_with_options(8,true);
      if(b == 1)
          stringbuffer_append_string(sb,"Yes");
      else
          stringbuffer_append_string(sb,"No");
      char *s = stringbuffer_to_string(sb);
      stringbuffer_release(sb);
      return(s);
}

char *int_to_icon(const int b){
      struct StringBuffer *sb = stringbuffer_new_with_options(8,true);
      if(b == 1)
          stringbuffer_append_string(sb,"✅");
      else
          stringbuffer_append_string(sb,"❌");
      char *s = stringbuffer_to_string(sb);
      stringbuffer_release(sb);
      return(s);
    
}

char *strip_non_ascii(const char *s){
      struct StringBuffer *sb = stringbuffer_new_with_options(strlen(s),true);
      for(size_t i=0;i<strlen(s);i++){
          char *substring = stringfn_substring(s,i,1);
          if(substring){
              if(stringfn_is_ascii(substring)){
                  stringbuffer_append_string(sb,substring);
              }
              free(substring);
          }
      }
      char *stripped = stringbuffer_to_string(sb);
      stringbuffer_release(sb);
      return(stripped);
}


