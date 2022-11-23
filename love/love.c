#pragma once
#ifndef LOVE_C
#define LOVE_C
#define LOCAL_DEBUG_MODE    LOVE_DEBUG_MODE
////////////////////////////////////////////
#include "love/love.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
#include "module/def.h"
#include "module/require.h"
#include "module/module.h"
#include "c_libansilove/include/ansilove.h"
#include "tempdir.c/tempdir.h"
#include "c_bat/bat/bat.h"
#include "vips/vips.h"
//#include "c_hl/hl/hl.h"
////////////////////////////////////////////
#define DEFAULT_WIDTH 120
#define DEFAULT_FONT "terminus"
static bool LOVE_DEBUG_MODE = false;
///////////////////////////////////////////////////////////////////////
struct love_priv_t {
  char *name, *font,*path;
  char *png_path,*styled_path;
  size_t len;
  char *buf;
  int width;
  struct ansilove_ctx ctx;
  struct ansilove_options options;
  struct StringFNStrings lines;
  bool rendered;
};
int __get_width__(module(love) *exports) {
  clib_module_init(love, exports);
  return(exports->priv->width);
}
char *__get_font__(module(love) *exports) {
  clib_module_init(love, exports);
  return(exports->priv->font);
}
void __load_file__(module(love) *exports, const char *path){
  clib_module_init(love, exports);
}
void __love_cfg_load_str__(struct love_priv_t *cfg,char *str){
  log_info("__love_cfg_load_str........%lu|%s",strlen(str),cfg->font);

}
void __love_cfg_save_file__(struct love_priv_t *cfg,char *path){
  log_info("__love_cfg_save_file........%s|%s",path,cfg->font);
  if(!fsio_write_binary_file(path, cfg->buf,cfg->len)){
    log_error("Failed to write love file");
    exit(EXIT_FAILURE);
  }


}
void __love_cfg_load_styled_file__(struct love_priv_t *cfg,char *path,enum love_style_mode_t style){
  char *new_path;
  asprintf(&new_path,"%s%lld-%d/%s",gettempdir(),timestamp(),getpid(),basename(path));
  fsio_mkdirs_parent(new_path,0700);

//  fsio_write_binary_file(new_path,fsio_read_binary_file(path),fsio_file_size(path));
  switch(style){
    case LOVE_STYLE_BAT:
      log_info("Styling %s file %s with bat", bytes_to_string(fsio_file_size(new_path)),new_path);
      break;
    default:
      break;
  }
  fsio_remove(new_path);
  free(new_path);
}
void __love_cfg_load_file__(struct love_priv_t *cfg,char *path){
  cfg->path=path;
  log_info("__love_cfg_load_file__........%s|%s",path,cfg->font);
  if(!fsio_file_exists(path)){
    log_error("File \"%s\" Does not exist",path);
    exit(EXIT_FAILURE);
  }
//  cfg->buf = hl_bat(path);
  cfg->len=strlen(cfg->buf);
  Dn(strlen(cfg->buf));
  Dn(cfg->len);
  cfg->lines = stringfn_split_lines_and_trim(cfg->buf);
  Di(cfg->lines.count);

}
struct love_priv_t *__love_cfg__(char *name){
  struct love_priv_t *p=calloc(1,sizeof(struct love_priv_t));
  p->name=strdup(name);
  p->width=DEFAULT_WIDTH;
  p->font=strdup(DEFAULT_FONT);
  ansilove_init(&(p->ctx), &(p->options));
  log_info("new love cfg");
  return(p);
}
void __load_files__(module(love) *exports, const char **path, int qty){
  clib_module_init(love, exports);
}
void __load_str__(module(love) *exports, char *str){
  size_t l = strlen(str);
  clib_module_init(love, exports);
  Dn(l);
  char *s;
// asprintf(&s,"%s",str);
  log_info("Loading %lu byte string",strlen(s));
//  log_info("Loading %lu byte string",strlen(str));
}
bool __love_style_file_to_png__(const char *path, const char *png){
  char *new_path, *styled;
  struct ansilove_ctx ctx;
  struct ansilove_options options;
  ansilove_init(&ctx, &options);
  asprintf(&new_path,"%s%lld-%d/%s",gettempdir(),timestamp(),getpid(),basename(path));
  styled = fsio_read_text_file(path);
  fsio_write_text_file(new_path,styled);
  char *b=hl_bat(new_path);
  fsio_write_text_file(new_path,b);
  Ds(new_path);
  Ds(png);
  ansilove_loadfile(&ctx, new_path);
  ansilove_ansi(&ctx, &options);
  ansilove_savefile(&ctx, png);
  Dn(fsio_file_size(png));
  ansilove_clean(&ctx);
  return(true);
}
bool __style_file_to_path__(const char *path, const char *dst){
  char *new_path, *styled, *png_path, *extension,*conv_path;
  extension=fsio_file_extension(dst);
  Ds(extension);
  struct ansilove_ctx ctx;
  struct ansilove_options options;
  ansilove_init(&ctx, &options);
  asprintf(&new_path,"%s%lld-%d/%s",gettempdir(),timestamp(),getpid(),basename(path));
  asprintf(&png_path,"%s%lld-%d/%s.%s",gettempdir(),timestamp(),getpid(),basename(path),"png");
  asprintf(&conv_path,"%s%lld-%d/%s.%s",gettempdir(),timestamp(),getpid(),stringfn_replace(basename(path),'.','_'),stringfn_trim(stringfn_replace(extension,'.',' ')));
  styled = fsio_read_text_file(path);
  char *ret=fsio_read_text_file(styled);
  fsio_write_text_file(new_path,styled);
  ansilove_loadfile(&ctx, new_path);
  ansilove_ansi(&ctx, &options);
  ansilove_savefile(&ctx, png_path);
  ansilove_clean(&ctx);
  VipsImage *v = vips_image_new_from_file(png_path,NULL);
  Di(vips_image_get_width(v));
  Di(vips_image_get_height(v));
  vips_image_write_to_file(v,conv_path,NULL);
  Ds(new_path);
  Ds(conv_path);
  Ds(png_path);
  Dn(fsio_file_size(new_path));
  Dn(fsio_file_size(png_path));
  Dn(fsio_file_size(conv_path));
  fsio_remove(png_path);
  fsio_remove(new_path);
  fsio_write_binary_file(dst,fsio_read_binary_file(conv_path),fsio_file_size(conv_path));
  fsio_remove(conv_path);
  return(true);
}
char *__love_style_str__(char *str){
  char *p,*buf;
//  asprintf(&p,"%s%lld-%d/%s",gettempdir(),timestamp(),getpid(),);
  fsio_write_text_file(p,str);
  buf=hl_bat(p);
  fsio_remove(p);
  free(p);

  return(buf);
}
char *__love_style_file__(char *src_file){
  char *p,*buf;
  asprintf(&p,"%s%lld-%d/%s",gettempdir(),timestamp(),getpid(),basename(src_file));
  fsio_write_text_file(p,fsio_read_text_file(src_file));
  buf=hl_bat(p);
  fsio_remove(p);
  free(p);

  return(buf);
}

char *__file__(char *src_file){
  char *new_path, *styled, *png_path;
  struct ansilove_ctx ctx;
  struct ansilove_options options;
  ansilove_init(&ctx, &options);
  asprintf(&new_path,"%s%lld-%d/%s",gettempdir(),timestamp(),getpid(),basename(src_file));
  asprintf(&png_path,"%s%lld-%d/%s.png",gettempdir(),timestamp(),getpid(),basename(src_file));
  styled = fsio_read_text_file(src_file);
  char *ret=fsio_read_text_file(styled);
  fsio_write_text_file(new_path,styled);
  Ds(new_path);
  Ds(png_path);
  ansilove_loadfile(&ctx, new_path);
  ansilove_ansi(&ctx, &options);
  ansilove_savefile(&ctx, png_path);
  Dn(fsio_file_size(png_path));
  ansilove_clean(&ctx);

}
char *__test__(module(love) *exports){
  struct ansilove_ctx ctx;
  struct ansilove_options options;
  ansilove_init(&ctx, &options);
  ansilove_loadfile(&ctx, "Makefile");
  ansilove_ansi(&ctx, &options);
  ansilove_savefile(&ctx, "Makefile.png");
  Dn(fsio_file_size("Makefile.png"));
  ansilove_clean(&ctx);
}
char *__get_test__(module(love) *exports){
  clib_module_init(love, exports);
  return(strdup("xxxxxxxX"));
}
module(love)*__cfg_set_content__(struct love_priv_t *cfg,const char *CONTENT){
  cfg->ctx.maplen = cfg->ctx.length = strlen(CONTENT);
  cfg->ctx.buffer = (uint8_t *)CONTENT;
  return(require(love));
}
void __save_str__(module(love) *exports, int *len){
  clib_module_init(love, exports);
}
bool __set_width__(module(love) *exports, int width) {
  clib_module_init(love, exports);
  exports->priv->width=width;
  return(true);
}
bool __set_font__(module(love) *exports, const char *font) {
  clib_module_init(love, exports);
  exports->priv->font=strdup(font);
  return(true);
}
void love_save_file(module(love) *exports, const char *path) {
  clib_module_init(love, exports);
  ansilove_savefile(&exports->priv->ctx, path);
}
void love_load_file(module(love) *exports, const char *path) {
  clib_module_init(love, exports);
  ansilove_loadfile(&exports->priv->ctx, path);
}
void __love_cfg_render__(struct love_priv_t *cfg){
  ansilove_ansi(&(cfg->ctx),&(cfg->options));
  cfg->rendered=true;
}

int __love_cfg_get_width__(struct love_priv_t *cfg){
  return(cfg->width);
}

char *__love_cfg_style_file__(struct love_priv_t *cfg, char *path){

}
char *__love_cfg_style_str__(struct love_priv_t *cfg, char *str){

}
char *__love_cfg_get_font__(struct love_priv_t *cfg){
  return(cfg->font);
}
void __love_cfg_set_width__(struct love_priv_t *cfg,int width){
  cfg->width=width;
}
void __love_cfg_set_font__(struct love_priv_t *cfg,char *font){
  cfg->font=font;
}
void __love_cfg_save_png__(struct love_priv_t *cfg,char *png){
  log_info("saving..%s",png);
  ansilove_savefile(&(cfg->ctx), png);
  if(fsio_file_size(png)<1){
    log_error("Failed Invalid PNG %s",png);
    log_info("Invalid cfg>   buf len: %lu", cfg->len);
    log_info("Invalid cfg>   rendered? %s", cfg->rendered?"Yes":"No");
  } 
}
void __love_render__(module(love) *exports) {
  clib_module_init(love, exports);
  ansilove_ansi(&(exports->priv->ctx),&(exports->priv->options));
  exports->priv->rendered=true;
}
void __love_free__(module(love) *exports) {
  clib_module_init(love, exports);
  ansilove_clean(&(exports->priv->ctx));
}
int __love_init__(module(love) *exports) {
  clib_module_init(love, exports);
  exports->priv=calloc(1,sizeof(struct love_priv_t));
//  exports->priv->width=DEFAULT_WIDTH;
//  asprintf(&(exports->priv->font),"%s",DEFAULT_FONT);
  ansilove_init(&(exports->priv->ctx), &(exports->priv->options));
  log_info("love init");
  return 0;
}
void __love_deinit__(module(love) *exports) {
  clib_module_deinit(love);
}
static void __attribute__((constructor)) __constructor__love(void){
  if (getenv("DEBUG") != NULL || getenv("DEBUG_love") != NULL) {
    log_debug("Enabling love Debug Mode");
    LOVE_DEBUG_MODE = true;
  }
  setenv("BAT_THEME","ansi",1);
  setenv("BAT_STYLE","numbers,grid",1);
  setenv("BAT_PAGER","",1);
  setenv("BAT_CONFIG","/dev/null",1);
  setenv("TMPDIR","/tmp/",1);
}
////////////////////////////////////////////
#undef LOCAL_DEBUG_MODE
#endif
