#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//////////////////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "submodules/uuid4/src/uuid4.h"

char *ac_confirm_render(void);
void color_reset();

enum ac_confirm_mode_t {
  AC_CONFIRM_LOG_NONE,
  AC_CONFIRM_LOG_INFO,
  AC_CONFIRM_LOG_ERROR,
  AC_CONFIRM_LOG_DEBUG,
  AC_CONFIRM_LOG_QTY,
};

#define AC_CONFIRM_LOG_DEFAULT    AC_CONFIRM_LOG_INFO
struct ac_confirm_option_t {
  char *text;
  char *selected_color;
  char *color;
  bool selected;
  char *button_s;
  char uuid[UUID4_LEN];
};

// Module Type Interface
module(ac_confirm) {
  define(ac_confirm, CLIB_MODULE);
  //////////////////////////////////////////////////////////////////////////////////////
  //     Config
  //////////////////////////////////////////////////////////////////////////////////////
  enum ac_confirm_mode_t mode;
  //////////////////////////////////////////////////////////////////////////////////////
  //     Properties
  //////////////////////////////////////////////////////////////////////////////////////
  struct Vector *options;
  //////////////////////////////////////////////////////////////////////////////////////
  //     Utility Functions
  //////////////////////////////////////////////////////////////////////////////////////
  int                        (*render_ui)(void);
  char                       *(*render_option_buttons)(void);
  struct ac_confirm_option_t *(*render_option)(char *TEXT, char *COLOR);
  struct ac_confirm_option_t *(*get_option_by_uuid)(char *UUID);
  char                       *(*render_option_button)(struct ac_confirm_option_t *OPTION);
  bool                       (*add_option)(struct ac_confirm_option_t *NEW_OPTION);
  size_t                     (*get_options_qty)(void);
  struct ac_confirm_option_t *(*init_option)(char *NEW_OPTION_TEXT);
  //////////////////////////////////////////////////////////////////////////////////////
};

int  ac_confirm_module_init(module(ac_confirm) * exports);
void ac_confirm_module_deinit(module(ac_confirm) * exports);
struct ac_confirm_option_t *ac_confirm_init_option(char *NEW_OPTION_TEXT);
bool ac_confirm_add_option(struct ac_confirm_option_t *NEW_OPTION);
size_t ac_confirm_get_options_qty(void);

exports(ac_confirm) {
  .mode                  = AC_CONFIRM_LOG_DEFAULT,
  .init                  = ac_confirm_module_init,
  .deinit                = ac_confirm_module_deinit,
  .render_ui             = NULL,
  .render_option_buttons = NULL,
  .render_option_button  = NULL,
  .render_option         = NULL,
  .get_option_by_uuid    = NULL,
  .get_options_qty       = ac_confirm_get_options_qty,
  .init_option           = ac_confirm_init_option,
  .add_option            = ac_confirm_add_option,
};
