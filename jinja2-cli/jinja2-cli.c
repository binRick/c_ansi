#define STDOUT_READ_BUFFER_SIZE    1024 * 8
///////////////////////////////////////////////////////
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <libproc.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
///////////////////////////////////////////////////////
#include "jinja2-cli.h"
///////////////////////////////////////////////////////
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "subprocess.h/subprocess.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "which/src/which.h"
///////////////////////////////////////////////////////
struct jinja2_render_template_t *jinja2_init_config(){
  struct jinja2_render_template_t *C = malloc(sizeof(struct jinja2_render_template_t));

  C->input_json_string = NULL;
  C->strict            = true;
  C->success           = false;
  C->stdout_s          = NULL;
  C->stderr_s          = NULL;
  C->debug_mode        = false;
  C->template_file     = NULL;
  C->input_json_file   = NULL;

  return(C);
}


int jinja2_render_template(struct jinja2_render_template_t *CFG){
  char                *READ_STDOUT;
  int                 exited, result;
  struct subprocess_s subprocess;
  char                *CMD;

  char                *jinja2_path = (char *)which_path("jinja2", getenv("PATH"));
  char                *env_path    = (char *)which_path("env", getenv("PATH"));
  char                *sh_path     = (char *)which_path("sh", getenv("PATH"));

  if (CFG->template_file == NULL) {
    asprintf(&CFG->template_file, "%s/.jinja2-template-%lld.txt", gettempdir(), timestamp());
  }
  if (CFG->input_json_file == NULL) {
    asprintf(&CFG->input_json_file, "%s/.jinja2-input-vars-%lld.json", gettempdir(), timestamp());
  }
  if (CFG->input_json_file != NULL && CFG->input_json_string != NULL) {
    fsio_write_text_file(CFG->input_json_file, CFG->input_json_string);
  }
  if (CFG->output_file == NULL) {
    asprintf(&CFG->output_file, "%s/.jinja2-output-%lld.txt", gettempdir(), timestamp());
  }
  if (CFG->template_file != NULL && CFG->template_s != NULL) {
    fsio_write_text_file(CFG->template_file, CFG->template_s);
  }
  asprintf(&CMD,
           "%s"
           " --format=json"
           " --strict"
           " --outfile='%s'"
           " '%s'"
           " '%s'",
           jinja2_path,
           CFG->output_file,
           CFG->template_file,
           CFG->input_json_file
           );
  if (CFG->debug_mode == true) {
    fprintf(stdout, "%s\n", CFG->input_json_file);
    fprintf(stdout, "%s\n", CMD);
  }
  const char           *exec_cmd[] = {
    env_path, sh_path, "--norc", "--noprofile", "-c", CMD, NULL
  };
  char                 stdout_buffer[STDOUT_READ_BUFFER_SIZE] = { 0 };
  struct  StringBuffer *SB                                    = stringbuffer_new_with_options(STDOUT_READ_BUFFER_SIZE, true);
  size_t               bytes_read                             = 0,
                       index                                  = 0;

  result = subprocess_create(exec_cmd, 0, &subprocess);
  assert(result == 0);

  do {
    bytes_read = subprocess_read_stdout(&subprocess, stdout_buffer, STDOUT_READ_BUFFER_SIZE - 1);
    stringbuffer_append_string(SB, stdout_buffer);
    index += bytes_read;
  } while (bytes_read != 0);
  index = 0;
  do {
    bytes_read = subprocess_read_stderr(&subprocess, stdout_buffer, STDOUT_READ_BUFFER_SIZE - 1);
    stringbuffer_append_string(SB, stdout_buffer);
    index += bytes_read;
  } while (bytes_read != 0);
  if (CFG->debug_mode == true) {
    fprintf(stdout, "%s\n", stringbuffer_to_string(SB));
  }

  result = subprocess_join(&subprocess, &exited);
  assert(result == 0);
  assert(exited == 0);

  CFG->output_s = fsio_read_text_file(CFG->output_file);
  READ_STDOUT   = stringbuffer_to_string(SB);
  CFG->success  = true;
  stringbuffer_release(SB);
  if (CFG->debug_mode == true) {
    fprintf(stderr, "stdout:  %s", READ_STDOUT);
  }

  return(EXIT_SUCCESS);
} /* jinja2_render_template */


int jinja2_release_config(struct jinja2_render_template_t *CFG){
  if (CFG) {
    free(CFG);
  }
  return(EXIT_SUCCESS);
}
