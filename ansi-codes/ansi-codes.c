#pragma once
#include "ansi-codes.h"
#include "ansi-utils/ansi-utils.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/include/vector.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "vt100utils/demos/tuibox.h"
#include "vt100utils/vt100utils.h"
#include <assert.h>
#define DISABLE_MOUSE_SEQUENCE       "\033[?1003l\033[?1002l\033[?1000l\033[?1006l\033[?1015l"
#define MOUSE_MODE_CLICKS            "\033[?1002l\033[?1003l\033[?1000h"
#define MOUSE_MODE_DRAG              "\033[?1003l\033[?1000h\033[?1002h"
#define MOUSE_MODE_MOVEMENT          "\033[?1000h\033[?1002h\033[?1003h"
#define MOUSE_MODE_X                 "\033[?1015h\033[?1006h"
#define MOUSE_MODE_DISABLE_SCROLL    "\033[?1049h"
#define MOUSE_MODE_ALL               MOUSE_MODE_CLICKS MOUSE_MODE_DRAG MOUSE_MODE_MOVEMENT MOUSE_MODE_DISABLE_SCROLL
#define TEST_STR                     "TEST"
enum change_selection_type_t {
  CHANGE_SELECTION_TYPE_NEXT,
  CHANGE_SELECTION_TYPE_PREV,
  CHANGE_SELECTION_TYPES_QTY,
};
void reload_options();
void select_prev();
void select_next();
void change_selection_index(int CHANGE_SELECTION_TYPE);
void set_selection_index(size_t NEW_SELECTION_INDEX);
struct vt100_node_t *get_node_by_uuid(char *UUID);
size_t get_index_by_uuid(char *UUID);


char *__TEST_STR(char *SEQ){
  char *s;

  asprintf(&s, "%s%s", SEQ, TEST_STR);
  return(s);
}
static struct ac_confirm_option_t AC_CONFIRM_DEFAULT_OPTION = {
  .text           = "undefined",
  .selected       = false,
  .color          = AC_RED,
  .selected_color = AC_GREEN,
};
char *ac_confirm_render_ui(void);
struct Vector *ac_confirm_render_options();
struct ac_confirm_option_t *ac_confirm_render_option(char *TEXT, char *COLOR);
struct ac_confirm_option_t *ac_confirm_get_option_by_uuid(char *UUID);
struct Vector *ac_confirm_render_option_buttons();
struct vt100_node_t *parse_seq(char *SEQ);
char *ac_confirm_render_option_button(struct ac_confirm_option_t *O);


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


ui_t                u;
struct vt100_node_t *head;


//int                 w = 50;


struct ac_confirm_option_t *ac_confirm_render_option(char *TEXT, char *COLOR){
  struct ac_confirm_option_t *O = calloc(1, sizeof(struct ac_confirm_option_t));
  char                       *s = AC_GREEN "" AC_BLACK_GREEN " xxxxxxxx " AC_NOINVERSE AC_GREEN "";

  return(O);
}
int w = 20;


void draw1(ui_box_t *b, char *out) {
  struct vt100_node_t *tmp = head->next;
  char                *sgr;
  int                 len      = 0;
  int                 full_len = 0;

  while (tmp != NULL) {
    sgr       = vt100_sgr(tmp, NULL);
    full_len += sprintf(
      out + full_len,
      "%s%.*s",
      sgr,
      MAX(0, w - len),
      tmp->str
      );
    len += tmp->len;
    free(sgr);
    tmp = tmp->next;
  }
  sprintf(
    out + full_len,
    "%s\n",
    w < 47 ? "..." : ""
    );
}
#define MIN(a, b)    (a < b ? a : b)
/*
 * void draw1(void)     {
 * int                 x; char *sgr;
 * struct vt100_node_t *tmp;
 * int                 off = 0;
 *
 * printf("\x1b[0;0H\x1b[2J\x1b[36m(Press \"q\" to exit)\n\x1b[32mColumn width:%i\x1b[0m\n\n", w);
 * tmp = head->next;
 * printf("        \x1b[35m┌");
 * for (x = 1; x < w + 2; x++) {
 *  printf("─");
 * }
 * printf("┐\n        ");
 *
 * while (tmp != NULL) {
 *   fprintf(stderr,
 *    "Text: %s\n  Foreground: %i\n  Background: %i\n  Mode: %i\n\n",
 *    tmp->str,
 *    tmp->fg.value,
 *    tmp->bg.value,
 *    tmp->mode
 *  );
 *  x = 0;
 *
 *  //printf("│\x1b[0m ");
 *  while (x < w) {
 *    sgr = vt100_sgr(tmp, NULL);
 *    printf("%s%.*s", sgr, MIN(w - x - 1, tmp->len - off - 1), tmp->str + off);
 *    if (tmp->len - off - 1 > w - x - 1) {
 *      off += w - x - 1;
 *      x    = w;
 *    } else {
 *      x  += tmp->len - off - 1;
 *      off = 0;
 *      tmp = tmp->next;
 *
 *      if (tmp == NULL) {
 *        x++;
 *        free(sgr);
 *        break;
 *      }
 *    }
 *    free(sgr);
 *  }
 *  for ( ; x < w; x++) {
 *    printf(" ");
 *  }
 *  printf(" \x1b[35m│\n        ");
 * }
 */

/*
 * printf("\x1b[35m└");
 * for (x = 1; x < w + 2; x++) {
 *  printf("─");
 * }
 * printf("┘");
 * printf("\n\n\x1b[0m");
 * }
 */


void shrink() {
  if (w > 4) {
    w--;
  }
  //draw();
}


void grow() {
  if (w < u.ws.ws_col - 3) {
    w++;
  }
  //draw();
}


void select_prev(){
  change_selection_index(CHANGE_SELECTION_TYPE_PREV);
}

void select_next(){
  change_selection_index(CHANGE_SELECTION_TYPE_NEXT);
}


size_t get_index_by_uuid(char *UUID){
    struct vt100_node_t *tmp_ = head->next;
    size_t i=0;
    while (tmp_ != NULL) {
      if (tmp_->str) {
        struct ac_confirm_option_t *O = require(ac_confirm)->get_option_by_uuid((char *)(u.b.data[i]->data2));
        assert(O != NULL);
        if(strcmp(UUID,O->uuid)==0){
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
    assert(index>=0);
    set_selection_index(index);
}

struct vt100_node_t *get_node_by_uuid(char *UUID){
    struct vt100_node_t *tmp_ = head->next;
    size_t i=0;
    while (tmp_ != NULL) {
      if (tmp_->str) {
        struct ac_confirm_option_t *O = require(ac_confirm)->get_option_by_uuid((char *)(u.b.data[i]->data2));
        assert(O != NULL);
        if(strcmp(UUID,O->uuid)==0){
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
  fprintf(stderr, "down.....\n");
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
    fprintf(stderr, AC_RED "str:%s\n" AC_RESETALL, _tmp->str);
    if (_tmp->str != NULL && (strcmp(_tmp->str, TEST_STR) == 0)) {
      return(_tmp);
    }
    _tmp = _tmp->next;
  }
  fprintf(stderr, AC_RED "NOT FOUND\n"AC_RESETALL);
  return((struct vt100_node_t *)NULL);
}


void stop() {
  ui_free(&u);
  vt100_free(head);
  exit(0);
}


void hover(ui_box_t *b, int x, int y, int down) {
  fprintf(stderr, "hover.uuid:%s.....%dx%d\n", (char *)b->data2, x, y);
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
}


void click(ui_box_t *b, int x, int y) {
  struct vt100_node_t *node = b->data1;
  fprintf(stderr, AC_YELLOW "click....uuid:%s..%dx%d: fg:%d|bg:%d|[%s]|%d|\n" AC_RESETALL, 
          (char *)b->data2, x, y, node->fg.value, node->bg.value, (char *)node->str, node->len
          );
  change_selection_by_uuid((char*)b->data2);
  //reload_options();
}


char *ac_confirm_render_ui(){
  struct Vector *RenderedOptionButtons = require(ac_confirm)->render_option_buttons();

  printf("%lu rendered buttons\n", vector_size(RenderedOptionButtons));
  char *bb = "\x1b[32m\x1b[0m\x1b[32m\x1b[7m Yes \x1b[0m\x1b[32m";

  ui_new(0, &u);

  printf("\x1b[?1049h\x1b[0m\x1b[2J\x1b[?1003h\x1b[?1015h\x1b[?1006h\x1b[?25l");

//  x = (u.ws.ws_col - 50) / 2;
//  y = (u.ws.ws_row - 10) / 2;
  size_t              index = 0;
  //head = vt100_decode("\x1b[38;5;106;48;5;20mOption 1" AC_RESETALL "\x1B[38;5;125m❌\x1B[38;5;112m☑\x1B[38;5;120m🔳\x1B[38;5;106m✖️");
  struct StringBuffer *sb = stringbuffer_new();

  for (size_t i = 0; i < vector_size(RenderedOptionButtons); i++) {
    char *RenderedOptionButton = vector_get(RenderedOptionButtons, i);
    stringbuffer_append_string(sb, RenderedOptionButton);
  }
  char *seq = stringbuffer_to_string(sb);

  fprintf(stderr, "rendered seqs:         '%s'\n", strdup_escaped(seq));
  head = vt100_decode(seq);
  //"\x1b[38;5;106;48;5;20mOption 1" AC_RESETALL "\x1B[38;5;125m❌\x1B[38;5;112m☑\x1B[38;5;120m🔳\x1B[38;5;106m✖️");
  struct vt100_node_t *tmp = head->next;
  int                 y = 5, x = 5;
  size_t              added_qty = 0;

  while (tmp != NULL) {
    if (tmp->str != NULL) {
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
      int added_id = ui_add(
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

  reload_options();
  ui_draw(&u);

  ui_loop(&u) {
    ui_update(&u);
  }
} /* ac_confirm_render */
#undef MIN


void ac_confirm_module_deinit(module(ac_confirm) *exports) {
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

struct Vector *ac_confirm_render_option_buttons(){
  char          *s                       = NULL;
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


void color_reset(){
  printf("\x1b[0m");
}
