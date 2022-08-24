#pragma once
#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

////////////////////////////////////////////////////
#include "ansi-codes.h"
#include "ansi-utils/ansi-utils.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "tiny-regex-c/re.h"
#include "vt100-utils/vt100-utils.h"
////////////////////////////////////////////////////
#include "vt100utils/vt100utils.h"
////////////////////////////////////////////////////
#include "vt100utils/tuibox.h"
////////////////////////////////////////////////////
#include "wildcardcmp/wildcardcmp.h"
////////////////////////////////////////////////////
#define UP_ARROW      "[A"
#define DOWN_ARROW    "[B"
#define TAB_KEY       "[A"
#define MIN(a, b)    (a < b ? a : b)
///////////////////////////////////////////////////////
enum change_selection_type_t {
  CHANGE_SELECTION_TYPE_NEXT,
  CHANGE_SELECTION_TYPE_PREV,
  CHANGE_SELECTION_TYPES_QTY,
};
static const char                 *TEST_STR = "F2DEEA90-F1F2-4C73-9BB8-3593319834D8";
static ui_t                       u;
static struct vt100_node_t        *head;
static struct ac_confirm_option_t AC_CONFIRM_DEFAULT_OPTION = {
  .text           = "undefined",
  .selected       = false,
  .color          = AC_RED,
  .selected_color = AC_GREEN,
};
void ac_confirm_module_deinit(module(ac_confirm) *exports);
void click(ui_box_t *b, int x, int y);
void mouse_scrolled_down(void *BINDING_DATA);
void mouse_scrolled_down(void *BINDING_DATA);
void clicked(void *BINDING_DATA);
void focus_out(void *BINDING_DATA);
void focus_in(void *BINDING_DATA);
void reload_options();
void select_prev();
void select_next();
void change_selection_index(int CHANGE_SELECTION_TYPE);
void set_selection_index(size_t NEW_SELECTION_INDEX);
int ac_confirm_module_init(module(ac_confirm) *exports);
size_t get_index_by_uuid(char *UUID);
char *ac_confirm_render_ui(void);
char *ac_confirm_render_option_button(struct ac_confirm_option_t *O);
struct Vector *ac_confirm_render_options();
struct Vector *ac_confirm_render_option_buttons();
struct ac_confirm_option_t *ac_confirm_render_option(char *TEXT, char *COLOR);
struct ac_confirm_option_t *ac_confirm_get_option_by_uuid(char *UUID);
struct vt100_node_t *parse_seq(char *SEQ);
struct vt100_node_t *get_node_by_uuid(char *UUID);

extern struct binding_type_t *binding_types[];

static char *__TEST_STR(char *SEQ){
  char *s;

  asprintf(&s, "%s%s", SEQ, TEST_STR);
  return(s);
}

static void stop() {
  ui_free(&u);
  vt100_free(head);
  exit(0);
}
struct unhandled_escaped_handlers_t {
  char *name;
  void (*handler)(void *);
  char *escaped_wildcards[33];
  char *regex_bind_datas[33];
} static unhandled_escaped_handlers[] = {
  { .name             = "click",     .handler = clicked,
    .regex_bind_datas ={
      ";[\\d]+;[\\d]+m",
      NULL,
    },
    .escaped_wildcards ={
      "\\x1b[<0;*",
      NULL,
    }, },
  { .name             = "focus-in",  .handler = focus_in,   .escaped_wildcards  = {
      "\\x1b[I0;*",
      "\\x1b[I65;*",
      "\\x1b[I64;*",
      "\\xoa[I0;x*",
      "\\x1b[I~;*",
      NULL,
    },
    .regex_bind_datas ={
      NULL,
    }, },
  { .name             = "focus-out", .handler = focus_out,  .escaped_wildcards  = {
      "\\x1b[O0;*",
      "\\x1b[O64;*",
      "\\x1b[O65;*",
      "\\x1b[O\\x*",
      "\\x09[O\\x*",
      "\\xoa[O0;x*",
      "\\x1b[O~;*",
      NULL,
    },
    .regex_bind_datas ={
      NULL,
    }, },
  { .name             = "shift-tab", .handler = select_prev,.escaped_wildcards  = {
      "\\x1b[Z\\x*",
      "\\x1b[Z~\\x*",
      "\\x1b[Z0;*",
      "\\x1b[Z65;*",
      "\\x1b[Z64;*",
      NULL,
    },
    .regex_bind_datas ={
      NULL,
    }, },
  { .name             = "tab",       .handler = select_next,.escaped_wildcards  = {
      "\\x09\\xb2i\\x80\\xff\\x7f",
      "\\x09[A*",
      "\\x09[B*",
      "\\x09[6~\\x*",
      "\\x09[5~\\x*",
      "\\x09[Z\\x*",
      "\\x09[I64;*",
      "\\x09[<64;*",
      "\\x09[I0;*",
      "\\x09[Z~\\x*",
      "\\x09[Z0;*",
      "\\x09[<0;*",
      "\\x09[?65;*",
      "\\x09[<65;*",
      "s[B\\x*",
      NULL,
    },
    .regex_bind_datas ={
      NULL,
    }, },
  { 0 },
};

struct ac_confirm_option_t *ac_confirm_init_option(char *NEW_OPTION_TEXT){
  struct ac_confirm_option_t *O = calloc(1, sizeof(struct ac_confirm_option_t));

  O->text           = NEW_OPTION_TEXT ? NEW_OPTION_TEXT : AC_CONFIRM_DEFAULT_OPTION.text;
  O->selected       = AC_CONFIRM_DEFAULT_OPTION.selected;
  O->color          = AC_CONFIRM_DEFAULT_OPTION.color;
  O->selected_color = AC_CONFIRM_DEFAULT_OPTION.selected_color;
  uuid4_generate(O->uuid);
  return(O);
}

bool ac_confirm_add_option(struct ac_confirm_option_t *NEW_OPTION){
  vector_push(require(ac_confirm)->options, (void *)NEW_OPTION);
}

size_t ac_confirm_get_options_qty(void){
  return(vector_size(require(ac_confirm)->options));
}

struct ac_confirm_option_t *ac_confirm_render_option(__attribute__((unused)) char *TEXT, __attribute__((unused)) char *COLOR){
  struct ac_confirm_option_t *O = calloc(1, sizeof(struct ac_confirm_option_t));

  __attribute__((unused)) char *s = AC_GREEN "" AC_BLACK_GREEN " xxxxxxxx " AC_NOINVERSE AC_GREEN "";

  return(O);
}

void select_prev(){
  change_selection_index(CHANGE_SELECTION_TYPE_PREV);
}

void select_next(void){
  change_selection_index(CHANGE_SELECTION_TYPE_NEXT);
}

size_t get_index_by_uuid(char *UUID){
  struct vt100_node_t *tmp_ = head->next;
  size_t              i     = 0;

  while (tmp_ != NULL) {
    if (tmp_->str) {
      struct ac_confirm_option_t *O = require(ac_confirm)->get_option_by_uuid((char *)(u.b.data[i]->data2));
      assert(O != NULL);
      if (strcmp(UUID, O->uuid) == 0) {
        return(i);
      }
      i++;
    }
    tmp_ = tmp_->next;
  }
  fprintf(stderr, AC_RED "NOT FOUND\n"AC_RESETALL);

  return(-1);
}

void set_selection_index(size_t NEW_SELECTION_INDEX){
  if (NEW_SELECTION_INDEX < 0) {
    NEW_SELECTION_INDEX = require(ac_confirm)->get_options_qty() - 1;
  }else if (NEW_SELECTION_INDEX > require(ac_confirm)->get_options_qty() - 1) {
    NEW_SELECTION_INDEX = 0;
  }
  struct ac_confirm_option_t *NEW_SELECTION = (struct ac_confirm_option_t *)vector_get(require(ac_confirm)->options, NEW_SELECTION_INDEX);
  assert(NEW_SELECTION != NULL);
  for (size_t i = 0; i < require(ac_confirm)->get_options_qty(); i++) {
    struct ac_confirm_option_t *O = (struct ac_confirm_option_t *)vector_get(require(ac_confirm)->options, i);
    O->selected = false;
  }
  NEW_SELECTION->selected = true;
  reload_options();
}

void change_selection_by_uuid(char *NEW_SELECTED_UUID){
  size_t index = get_index_by_uuid(NEW_SELECTED_UUID);

  assert(index >= 0);
  set_selection_index(index);
}

struct vt100_node_t *get_node_by_uuid(char *UUID){
  struct vt100_node_t *tmp_ = head->next;
  size_t              i     = 0;

  while (tmp_ != NULL) {
    if (tmp_->str) {
      struct ac_confirm_option_t *O = require(ac_confirm)->get_option_by_uuid((char *)(u.b.data[i]->data2));
      assert(O != NULL);
      if (strcmp(UUID, O->uuid) == 0) {
        return(u.b.data[i]);
      }
      i++;
    }
    tmp_ = tmp_->next;
  }
  fprintf(stderr, AC_RED "NOT FOUND\n"AC_RESETALL);
  return((struct vt100_node_t *)NULL);
}

void change_selection_index(int CHANGE_SELECTION_TYPE) {
  size_t NEW_SELECTION_INDEX = -1;

  for (size_t i = 0; i < require(ac_confirm)->get_options_qty(); i++) {
    struct ac_confirm_option_t *O = (struct ac_confirm_option_t *)vector_get(require(ac_confirm)->options, i);
    if (O->selected == true) {
      O->selected = false;
      switch (CHANGE_SELECTION_TYPE) {
      case CHANGE_SELECTION_TYPE_NEXT:
        NEW_SELECTION_INDEX = i + 1;
        break;
      case CHANGE_SELECTION_TYPE_PREV:
        if (i == 0) {
          NEW_SELECTION_INDEX = require(ac_confirm)->get_options_qty() - 1;
        }else{
          NEW_SELECTION_INDEX = i - 1;
        }
        break;
      }
      return(set_selection_index(NEW_SELECTION_INDEX));
    }
  }
  return;
}

void reload_options() {
  if (false) {
    int      ind;
    ui_box_t *tmpv;
    vec_foreach(&(u.b), tmpv, ind){
      fprintf(stderr,
              "#foreach>%d> uuid:%s|id:%d|len:%d\n",
              ind,
              (char *)tmpv->data2,
              tmpv->id,
              u.b.length
              );
    }
  }
  {
    size_t              i     = 0;
    struct vt100_node_t *tmp_ = head->next;
    while (tmp_ != NULL) {
      if (tmp_->str) {
        struct ac_confirm_option_t *O = require(ac_confirm)->get_option_by_uuid((char *)(u.b.data[i]->data2));
        assert(O != NULL);
        struct vt100_node_t        *P[2];
        P[0] = parse_seq(O->color);
        P[1] = parse_seq(O->selected_color);
        if (O->selected == true) {
          tmp_->bg.type  = P[1]->bg.type;
          tmp_->bg.value = P[1]->bg.value;
          tmp_->fg.type  = P[1]->fg.type;
          tmp_->fg.value = P[1]->fg.value;
        }else{
          tmp_->bg.type  = P[0]->bg.type;
          tmp_->bg.value = P[0]->bg.value;
          tmp_->fg.type  = P[0]->fg.type;
          tmp_->fg.value = P[0]->fg.value;
        }
        if (false) {
          fprintf(stderr,
                  "#%lu> Text: %s\n\t  Foreground: %i\n\t  Background: %i\n  Mode: %i|"
                  "data2:%s|id:%d|"
                  "str:%s|"
                  "\n\tO uuid:%s|"
                  "\n\t" "%s" "O selected:%s|" AC_RESETALL
                  "\n\tO selectedcolor:%s|"
                  "\n\tO color:%s|"
                  "\n\tparsed          color fg:%d@%d|bg:%d@%d|"
                  "\n\tparsed selected color fg:%d@%d|bg:%d@%d|"
                  "\n",
                  i,
                  tmp_->str,
                  tmp_->fg.value,
                  tmp_->bg.value,
                  tmp_->mode,
                  (char *)(u.b.data[i]->data2),
                  (u.b.data[i]->id),
                  tmp_->str,
                  O->uuid,
                  (O->selected == true) ? AC_GREEN : AC_RED,
                  (true == O->selected) ? "Yes" : "No",
                  strdup_escaped(O->selected_color), strdup_escaped(O->color),
                  P[0]->fg.type, P[0]->fg.value, P[0]->bg.type, P[0]->bg.value,
                  P[1]->fg.type, P[1]->fg.value, P[1]->bg.type, P[1]->bg.value
                  );
        }
        i++;
      }
      tmp_ = tmp_->next;
    }
  }
  ui_draw(&u);
} /* down */

struct vt100_node_t *parse_seq(char *SEQ){
  char                *ts    = __TEST_STR(SEQ);
  struct vt100_node_t *_head = vt100_decode(ts);
  struct vt100_node_t *_tmp  = _head;

  while (_tmp != NULL) {
    if (false) {
      fprintf(stderr, AC_RED "str:%s\n" AC_RESETALL, _tmp->str);
    }
    if (_tmp->str != NULL && (strcmp(_tmp->str, TEST_STR) == 0)) {
      return(_tmp);
    }
    _tmp = _tmp->next;
  }
  fprintf(stderr, AC_RED "NOT FOUND\n"AC_RESETALL);
  return((struct vt100_node_t *)NULL);
}

void hover(ui_box_t *b, int x, int y, __attribute__((unused)) int down) {
  if (false) {
    fprintf(stderr, "hover.uuid:%s.....%dx%d\n", (char *)b->data2, x, y);
  }
}

void draw(ui_box_t *b, char *out) {
  struct vt100_node_t *node = b->data1;
  char                *sgr  = vt100_sgr(node, NULL);

  sprintf(out, "%s%s", sgr, node->str);
  if (false) {
    fprintf(stderr, "draw..uuid:%s....\n\t|sgr:%s\n\t|out:%s\n\t|fg:%d|bg:%d|[%s]|%d|\n",
            (char *)b->data2,
            strdup_escaped(sgr),
            strdup_escaped(out),
            node->fg.value, node->bg.value, (char *)node->str, node->len);
  }
  free(sgr);

  {
    {
      printf("\x1b[%i;%iH", 1, u.ws.ws_col - 18);
      printf("\x1b[36m(Press \"q\" to exit)");
      printf("\x1b[%i;%iH", 2, u.ws.ws_col - 17);
      printf("\x1b[32mColumns   %i\x1b[0m", u.ws.ws_col);
      printf("\x1b[%i;%iH", 3, u.ws.ws_col - 17);
      printf("\x1b[32mRows      %i\x1b[0m", u.ws.ws_row);
      printf("\x1b[%i;%iH", 4, u.ws.ws_col - 17);
      printf("\x1b[32mOptions   %lu\x1b[0m", require(ac_confirm)->get_options_qty());
    }
    {
      printf("\x1b[%i;%iH", 4, 4);
      printf("\x1b[35m┌");
      for (int x = 1; x < 10; x++) {
        printf("─");
      }
      printf("┐");
    }
    {
      for (int i = 0; i < (int)require(ac_confirm)->get_options_qty(); i++) {
        printf("\x1b[%i;%iH", 5 + i, 4);
        printf("\x1b[35m│");
        printf("\x1b[%i;%iH", 5 + i, 4 + 10);
        printf("\x1b[35m│");
      }
    }
    {
      printf("\x1b[%i;%iH", (int)require(ac_confirm)->get_options_qty() + 5, 4);
      printf("\x1b[35m└");
      for (int x = 1; x < 10; x++) {
        printf("─");
      }
      printf("┘");
      printf("\x1b[0m");
    }
  }
} /* draw */

void click(ui_box_t *b, int x, int y) {
  struct vt100_node_t *node = b->data1;

  if (false) {
    fprintf(stderr, AC_YELLOW "click....uuid:%s..%dx%d: fg:%d|bg:%d|[%s]|%d|\n" AC_RESETALL,
            (char *)b->data2, x, y, node->fg.value, node->bg.value, (char *)node->str, node->len
            );
  }
  change_selection_by_uuid((char *)b->data2);
}

void mouse_scrolled_down(__attribute__((unused)) void *BINDING_DATA){
  select_next();
  return;
}

void focus_out(__attribute__((unused)) void *BINDING_DATA){
  fprintf(stderr, "focus out!\n");
}

void clicked(__attribute__((unused)) void *BINDING_DATA){
  fprintf(stderr, "clicked!\n");
}

void focus_in(__attribute__((unused)) void *BINDING_DATA){
  fprintf(stderr, "focus in!\n");
}

void mouse_scrolled_up(__attribute__((unused)) void *BINDING_DATA){
  select_prev();
  return;
}
/*
 * int        match_length;
 * const char *string_to_search = "ahem.. 'hello world !' ..";
 * re_t       pattern           = re_compile("[Hh]ello [Ww]orld\\s*[!]?");
 * int        match_idx         = re_matchp(pattern, string_to_search, &match_length);
 */

void unhandled_input(void *BINDING_DATA){
  bool                                is_handled = false;
  struct unhandled_escaped_handlers_t *tmp       = unhandled_escaped_handlers;

  while (tmp != NULL && tmp->handler != NULL && *(tmp->escaped_wildcards) != NULL) {
    char **tmp1 = tmp->escaped_wildcards;
    char **tmp2 = tmp->regex_bind_datas;
    while (*tmp1 != NULL) {
      if (1 == wildcardcmp(*tmp1, strdup_escaped((char *)BINDING_DATA))) {
        while (*tmp2 != NULL) {
          fprintf(stderr, "[BINDING_MODE_UNHANDLED_INPUT]  checking regex '%s'\n", *tmp2);

          int  match_length;
          re_t pattern   = re_compile(*tmp2);
          int  match_idx = re_matchp(pattern, strdup_escaped((char *)BINDING_DATA), &match_length);
          fprintf(stderr, "[BINDING_MODE_UNHANDLED_INPUT]  checked regex '%s'    match len: %d | match_idx: %d | target len: %lu|\n", *tmp2, match_length, match_idx, strlen(strdup_escaped((char *)BINDING_DATA)));

          *(tmp2)++;
        }
        fprintf(stderr, "[BINDING_MODE_UNHANDLED_INPUT]  match for %s!- '%s' -> '%s'\n",
                tmp->name,
                *tmp1,
                strdup_escaped((char *)BINDING_DATA)
                );
        tmp->handler((void *)NULL);
        is_handled = true;
        break;
      }
      *(tmp1)++;
    }
    tmp++;
  }
  if (false == is_handled) {
    fprintf(stderr, "[BINDING_MODE_UNHANDLED_INPUT]      escaped:'%s' (%lu chars)"
            "\n",
            strdup_escaped((char *)BINDING_DATA),
            strlen((char *)BINDING_DATA)
            );
  }

  return;
} /* unhandled_input */

char *ac_confirm_render_ui(){
  struct Vector *RenderedOptionButtons = require(ac_confirm)->render_option_buttons();

  __attribute__((unused)) char *bb = "\x1b[32m\x1b[0m\x1b[32m\x1b[7m Yes \x1b[0m\x1b[32m";

  ui_new(0, &u);
  binding_types[BINDING_MODE_MOUSE_SCROLL_UP]->handler   = mouse_scrolled_up;
  binding_types[BINDING_MODE_MOUSE_SCROLL_DOWN]->handler = mouse_scrolled_down;
  binding_types[BINDING_MODE_UNHANDLED_INPUT]->handler   = unhandled_input;
//  x = (u.ws.ws_col - 50) / 2;
//  y = (u.ws.ws_row - 10) / 2;
  size_t              index = 0;
  struct StringBuffer *sb   = stringbuffer_new();

  for (size_t i = 0; i < vector_size(RenderedOptionButtons); i++) {
    char *RenderedOptionButton = vector_get(RenderedOptionButtons, i);
    stringbuffer_append_string(sb, RenderedOptionButton);
  }
  char *seq = stringbuffer_to_string(sb);

  head = vt100_decode(seq);
  struct vt100_node_t *tmp = head->next;
  int                 y = 5, x = 5;
  size_t              added_qty = 0;

  while (tmp != NULL) {
    if (tmp->str != NULL) {
      if (false) {
        fprintf(stderr,
                "#%lu> Text: %s\n x:%d|y:%d| Foreground: %i/%d\n  Background: %i/%d\n  Mode: %i\n\n",
                index,
                tmp->str,
                x, y,
                tmp->fg.value,
                tmp->fg.type,
                tmp->bg.value,
                tmp->bg.type,
                tmp->mode
                );
      }
      size_t added_id = ui_add(
        x, y,
        tmp->len, 1,
        0,
        NULL, 0,
        draw,
        click,
        hover,
        tmp,
        (void *)(((struct ac_confirm_option_t *)vector_get(require(ac_confirm)->options, index))->uuid),
        &u
        );
      assert(added_id == index);
      y++;
      index++;
      added_qty++;
    }
    tmp = tmp->next;
  }
  assert(added_qty == vector_size(RenderedOptionButtons));
  ui_key("q", stop, &u);
  ui_key("r", reload_options, &u);
  ui_key("n", select_next, &u);
  ui_key("p", select_prev, &u);
  ui_key(UP_ARROW, select_prev, &u);
  ui_key(DOWN_ARROW, select_next, &u);
  ui_key("[H", select_prev, &u);
  ui_key("[H;", select_prev, &u);
  ui_key("[H~", select_prev, &u);
  ui_key("[F~", select_next, &u);
  ui_key("[F", select_next, &u);
  ui_key("[F;", select_next, &u);
  ui_key("[5~", select_prev, &u);
  ui_key("[6~", select_next, &u);
  reload_options();

  ui_draw(&u);
  ui_loop(&u) {
    ui_update(&u);
  }
} /* ac_confirm_render */
#undef MIN

void ac_confirm_module_deinit(__attribute__((unused)) module(ac_confirm) *exports) {
  clib_module_deinit(ac_confirm);
  return;
}

int ac_confirm_module_init(module(ac_confirm) *exports) {
  clib_module_init(ac_confirm, exports);
  uuid4_init();
  exports->mode                  = AC_CONFIRM_LOG_DEFAULT;
  exports->options               = vector_new();
  exports->render_ui             = ac_confirm_render_ui;
  exports->get_option_by_uuid    = ac_confirm_get_option_by_uuid;
  exports->render_option_buttons = ac_confirm_render_option_buttons;
  exports->render_option         = ac_confirm_render_option;
  exports->render_option_button  = ac_confirm_render_option_button;
  return(0);
}

char *ac_confirm_render_option_button(struct ac_confirm_option_t *O){
  char *b;

  asprintf(&b,
           "\x1b%s%s",
           O->text,
           (true == O->selected) ? O->selected_color : O->color
           );
  return(b);
}

void ac_confirm_redraw(){
  ui_redraw(&u);
}

struct Vector *ac_confirm_render_option_buttons(){
  struct Vector *rendered_option_buttons = vector_new();

  for (size_t i = 0; i < require(ac_confirm)->get_options_qty(); i++) {
    struct ac_confirm_option_t *O = (struct ac_confirm_option_t *)vector_get(require(ac_confirm)->options, i);
    O->button_s = require(ac_confirm)->render_option_button(O);
    vector_push(rendered_option_buttons, O->button_s);
  }
  return(rendered_option_buttons);
}
struct ac_confirm_option_t *ac_confirm_get_option_by_uuid(char *UUID){
  for (size_t i = 0; i < vector_size(require(ac_confirm)->options); i++) {
    struct ac_confirm_option_t *O = (struct ac_confirm_option_t *)vector_get(require(ac_confirm)->options, i);
    if (strcmp(UUID, O->uuid) == 0) {
      return(O);
    }
  }

  return(NULL);
}

void tb_sig_handler(int sig){
  if (SIGWINCH == sig) {
    struct winsize winsz;

    ioctl(0, TIOCGWINSZ, &winsz);
    fprintf(stderr, "SIGWINCH raised, window size: %d rows / %d columns\n", winsz.ws_row, winsz.ws_col);
    ac_confirm_redraw();
  }
}
