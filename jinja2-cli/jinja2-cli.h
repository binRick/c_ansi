#pragma once
#include <stdbool.h>


struct jinja2_render_template_t {
  bool strict;
  char *output_file, *output_dir, *output_s;
  char *input_json_string, *stdout_s, *stderr_s;
  char *template_file;
  char *template_s;
  char *input_json_file;
  bool success;
  bool debug_mode;
};

struct jinja2_render_template_t *jinja2_init_config();
int jinja2_render_template(struct jinja2_render_template_t *CFG);
int jinja2_release_config(struct jinja2_render_template_t *CFG);
