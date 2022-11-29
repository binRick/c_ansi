#pragma once
#ifndef TRAY_C
#define TRAY_C
////////////////////////////////////////////
#include "tray/tray.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_eventemitter/include/eventemitter.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_tray/tray.h"
#include "c_vector/vector/vector.h"
#include "chan/src/chan.h"
#include "chan/src/queue.h"
#include "incbin/incbin.h"
#include "log/log.h"
#include "module/def.h"
#include "module/module.h"
#include "module/require.h"
#include "ms/ms.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
#define TRAY_APPINDICATOR    1
////////////////////////////////////////////
struct tray_priv_t {
//  struct tray_menu menu;
};

/*
   struct tray{};
   struct tray_menu{};
   static struct tray *get_tray(void){
   struct tray *t=calloc(1,sizeof(struct tray));
   //  t->icon=TRAY_ICON1;
   //  t->tooltip="tt";
   t->menu = (struct tray_menu[]){
            {.text = "Hello", .cb = hello_cb},
            {.text = "Checked", .checked = 1, .checkbox = 1, .cb = toggle_cb},
            {.text = "Disabled", .disabled = 1},
            {.text = "-"},
            {.text = NULL},
   };
   return(t);
   }
 */

////////////////////////////////////////////
int tray_init(module(tray) *exports) {
  clib_module_init(tray, exports);
  exports->log_mode = TRAY_LOG_MODE_NONE;
  exports->priv     = calloc(1, sizeof(struct tray_priv_t));
//  exports->priv->menu=calloc(1,sizeof(struct tray_menu));
  return(EXIT_SUCCESS);
}

void tray_deinit(module(tray) *exports) {
  clib_module_deinit(tray);
}
////////////////////////////////////////////
#endif
