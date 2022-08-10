#pragma once
#include "ansi-codes.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/include/vector.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "vt100utils/demos/tuibox.h"
#include "vt100utils/vt100utils.h"
static inline char *ac_confirm_render_button(char *TEXT, char *COLOR);

static struct ac_confirm_option_t AC_CONFIRM_DEFAULT_OPTION = {
  .text           = "undefined",
  .selected       = false,
  .color          = AC_NONE,
  .selected_color = AC_GREEN,
};

char *ac_confirm_render_buttons();
struct ac_confirm_option_t *ac_confirm_init_option(char *NEW_OPTION_TEXT){
  struct ac_confirm_option_t *O = calloc(1, sizeof(struct ac_confirm_option_t));

  O->text           = NEW_OPTION_TEXT ? NEW_OPTION_TEXT : AC_CONFIRM_DEFAULT_OPTION.text;
  O->selected       = AC_CONFIRM_DEFAULT_OPTION.selected;
  O->color          = AC_CONFIRM_DEFAULT_OPTION.color;
  O->selected_color = AC_CONFIRM_DEFAULT_OPTION.selected_color;
  return(O);
}


int ac_confirm_module_init(module(ac_confirm) *exports) {
  clib_module_init(ac_confirm, exports);
  exports->mode    = AC_CONFIRM_LOG_DEFAULT;
  exports->options = vector_new();
  return(0);
}


void ac_confirm_module_deinit(module(ac_confirm) *exports) {
  clib_module_deinit(ac_confirm);
  return;
}


inline bool ac_confirm_add_option(struct ac_confirm_option_t *NEW_OPTION){
  vector_push(require(ac_confirm)->options, (void *)NEW_OPTION);
}


inline size_t ac_confirm_get_options_qty(void){
  return(vector_size(require(ac_confirm)->options));
}


static inline char *ac_confirm_render_button(char *TEXT, char *COLOR){
  char *s;

  asprintf(&s, "%s" "" ACDCS AC_NONE "%s" AC_INVERSE " %s " ACDCS AC_NONE "%s" "",
           COLOR, COLOR,
           TEXT,
           COLOR
           );
  return(s);
}


ui_t u;
struct vt100_node_t *head;
int                 w = 50;


#define MIN(a, b)    (a < b ? a : b)
void draw(void)     {
  int                 x; char *sgr;
  struct vt100_node_t *tmp;
  int                 off = 0;

  printf("\x1b[0;0H\x1b[2J\x1b[36m(Press \"q\" to exit)\n\x1b[32mColumn width:%i\x1b[0m\n\n", w);
  tmp = head->next;

  printf("        \x1b[35m┌");
  for (x = 1; x < w + 2; x++) {
    printf("─");
  }
  printf("┐\n        ");


  while (tmp != NULL) {
    x = 0;

    printf("│\x1b[0m ");
    while (x < w) {
      sgr = vt100_sgr(tmp, NULL);
      printf("%s%.*s", sgr, MIN(w - x - 1, tmp->len - off - 1), tmp->str + off);
      if (tmp->len - off - 1 > w - x - 1) {
        off += w - x - 1;
        x    = w;
      } else {
        x  += tmp->len - off - 1;
        off = 0;
        tmp = tmp->next;

        if (tmp == NULL) {
          x++;
          free(sgr);
          break;
        }
      }
      free(sgr);
    }

    for ( ; x < w; x++) {
      printf(" ");
    }
    printf(" \x1b[35m│\n        ");
  }

  printf("\x1b[35m└");
  for (x = 1; x < w + 2; x++) {
    printf("─");
  }
  printf("┘");

  printf("\n\n\x1b[0m");
} /* draw */


void shrink()     {
  if (w > 4) {
    w--;
  }
  draw();
}


void grow()     {
  if (w < u.ws.ws_col - 3) {
    w++;
  }
  draw();
}


void stop()     {
  ui_free(&u);
  vt100_free(head);
  exit(0);
}


inline char *ac_confirm_render(){
    char *buttons = ac_confirm_render_buttons();
  char *s;
  printf(buttons);
  asprintf(&s,"%s",buttons);
  //"\x1b[31mLorem magna aliqua. \x1b[32mUt. \x1b[33mDuis aute irure dolor in reprehenderit in voluptate velit esse cillum doloreeu fugiat nulla pariatur. \x1b[34mExcepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. %s", buttons);
  head = vt100_decode(s);
//  head = vt100_decode(buttons);

  ui_new(0, &u);

  ui_key("\x1b[C", grow, &u);
  ui_key("\x1b[D", shrink, &u);
  ui_key("q", stop, &u);
  draw();
  ui_loop(&u) {
    ui_update(&u);
  }
}
#undef MIN

char *ac_confirm_render_buttons(){
  char                *s  = NULL;
  struct StringBuffer *sb = stringbuffer_new();

  for (size_t i = 0; i < require(ac_confirm)->get_options_qty(); i++) {
    struct ac_confirm_option_t *O = (struct ac_confirm_option_t *)vector_get(require(ac_confirm)->options, i);
    char                       *b;
    asprintf(&b, "%s",
             ac_confirm_render_button(
               O->text,
               O->selected ? O->selected_color : O->color)
             );
    stringbuffer_append_string(sb, b);
    stringbuffer_append_string(sb, " ");
  }
  s = stringbuffer_to_string(sb);
  stringbuffer_release(sb);
  return(s);
}


void color_reset(){
  printf("\x1b[0m");
}
