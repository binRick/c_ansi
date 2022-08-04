#include <math.h>
#include "ansi-utils-test.h"
#include "ansi-codes.h"
#include "ansi-utils.h"
#include "ansi-rgb-utils.h"
#include "stringbuffer.h"
#include "stringfn.h"
#include "vt100utils/vt100utils.h"

const char TEST_ANSI_STRINGS[][1024*4] = {
    AC_BLUE "BLUE",
    "NONE",
    "\x1b[32mHello world! \x1b[45;4mGoodbye.",
    AC_RED "RED",
    AC_YELLOW "YELLOW 123" " " AC_BLUE "BLUE 123",
    AC_BOLD "Bold",
    AC_FG8(3) "YELLOW",
    AC_ITALIC "Italic",
    AC_UNDERLINE "Underline",
    AC_INVISIBLE "Invisible",
    AC_FG8(3) AC_ITALIC "Italic Yellow",
};


int vt100utils_test0(const char *str){
  char *str_tmp = malloc(strlen(str)+32);
  sprintf(str_tmp, "%s" AC_RESETALL, str);
  char *str_escaped = strdup_escaped(str_tmp);
  struct vt100_node_t *head = vt100_decode(str_tmp),
                      *tmp = head;
  printf(
    "" AC_RESETALL "%s" AC_RESETALL "" AC_ITALIC AC_FAINT "\n%s\n" AC_RESETALL ""
    "\n"
    , str, str_escaped
  );
  /*
  for(int i=0;tmp!=NULL;i++){	  
    if(tmp->str != NULL && strlen(tmp->str)>0){
     printf(
      "\t#%i>  '%s' :: |Foreground:%i|Background:%i|Mode:%i|\n"
      , i, tmp->str, tmp->fg.value, tmp->bg.value, tmp->mode
     );
    }
//    struct vt100_node_t *t = tmp;
    tmp = tmp->next;
  //  free(t);
  }
  fflush(stdout);
  fflush(stderr);
  if(str_tmp)
	  free(str_tmp);
  if(str_escaped)
	  free(str_escaped);
//  if(head)
//	  vt100_free(head);
*/
  return 0;
}

int main(int argc, char **argv) {
  float *c;
  static struct StringBuffer *SB;
  int res = -1,
      len = (sizeof(TEST_ANSI_STRINGS)/sizeof(TEST_ANSI_STRINGS[0]));

  SB = stringbuffer_new_with_options(1024,true);

  printf("Testing %d Strings\n",len);
  for(int i=0;i<len;i++){
    if(TEST_ANSI_STRINGS[i] != NULL){
        stringbuffer_append_string(SB,TEST_ANSI_STRINGS[i]);
//        stringbuffer_append_string(SB,", ");
    }
  }
//  assert(vt100utils_test0(stringbuffer_to_string(SB)) == 0);	

  stringbuffer_clear(SB);
  for(int i=0;i<3;i++){
    bright_color_init(i);
    for(int x=0;x<30;x++){
        c = calloc(4, sizeof(float));
        bright_color(x, c);
        char s[1024];
        sprintf(s, "\x1b[38;2;%g;%g;%gm" "%g/%g/%g\n",
                round(c[0] * 255.0), round(c[1] * 255.0), round(c[2] * 255.0),
                round(c[0] * 255.0), round(c[1] * 255.0), round(c[2] * 255.0)
              );
        free(c);  
        stringbuffer_append_string(SB,s);
 //       stringbuffer_append_string(SB,", ");
    }
  }
  assert(vt100utils_test0(stringbuffer_to_string(SB)) == 0);	

  stringbuffer_release(SB);
}

