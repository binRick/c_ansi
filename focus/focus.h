#pragma once
#ifndef FOCUS_H
#define FOCUS_H
//////////////////////////////////////
#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//////////////////////////////////////
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "c_focus/src/c_focus.h"
//////////////////////////////////////

module(focus) {
  define(focus, CLIB_MODULE);
  void (*callback)(c_focus_event_callback_t cb);
  void (*block)(c_focus_event_block_t cb);
  struct {
    char *(*serialize)(struct c_focus_event_t*);
  } event;
  struct {
    bool (*callback)(c_focus_event_callback_t cb);
    bool (*block)(c_focus_event_block_t cb);
  } start;
  bool (*stop)(void);
  void (*log)(const char *path);
};

int __focus_init(module(focus) *exports);
void __focus_deinit(module(focus) *exports);
bool __focus_stop(void);
bool __focus_start_callback(c_focus_event_callback_t cb);
bool __focus_start_block(c_focus_event_block_t cb);
void __focus_log_path(const char *path);

exports(focus) {
  .init   = __focus_init,
  .log=__focus_log_path,
  .deinit = __focus_deinit,
  .callback=__c_focus_callback,
  .block=__c_focus_block,
  .stop=__focus_stop,
  .event.serialize=__c_focus_serialize_event,
  .start.block=__focus_start_block,
  .start.callback=__focus_start_callback,
};
#endif
