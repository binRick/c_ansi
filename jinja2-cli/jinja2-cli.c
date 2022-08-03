#define STDOUT_READ_BUFFER_SIZE        1024 * 8
#define JINJA2_CLI_BINARY_FILE_NAME    "jinja2-cli"
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
#include "jinja2-cli/jinja2-cli-inc.c"
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
  char                *jinja2_path = (char *)which_path(JINJA2_CLI_BINARY_FILE_NAME, getenv("PATH"));
  char                *env_path    = (char *)which_path("env", getenv("PATH"));
  char                *sh_path     = (char *)which_path("sh", getenv("PATH"));

  if (!fsio_file_exists(jinja2_path)) {
    char *temp_incbin_jinja2_binary;
    asprintf(&temp_incbin_jinja2_binary, "%s%s", gettempdir(), JINJA2_CLI_BINARY_FILE_NAME);
    fsio_write_binary_file(temp_incbin_jinja2_binary, inc_binary_jinja2_cli_data, inc_binary_jinja2_cli_size);
    fsio_chmod_recursive(temp_incbin_jinja2_binary, FSIO_MODE_ALL);
    assert(fsio_file_exists(temp_incbin_jinja2_binary) == true);
    assert(fsio_file_size(temp_incbin_jinja2_binary) == inc_binary_jinja2_cli_size);
    jinja2_path = temp_incbin_jinja2_binary;
  }
  assert(fsio_file_exists(jinja2_path) == true);
  assert(fsio_file_size(jinja2_path) > 0);
  if (CFG->template_file == NULL) {
    asprintf(&CFG->template_file, "%s.jinja2-template-%lld-%d.txt", gettempdir(), timestamp(), getpid());
  }
  asprintf(&CFG->output_file, "%s.jinja2-output-file-%lld-%d.json", gettempdir(), timestamp(), getpid());

  if (CFG->input_json_file == NULL) {
    asprintf(&CFG->input_json_file, "%s.jinja2-input-vars-%lld-%d.json", gettempdir(), timestamp(), getpid());
  }
  if (CFG->input_json_file != NULL && CFG->input_json_string != NULL) {
    fsio_write_text_file(CFG->input_json_file, CFG->input_json_string);
  }
  if (CFG->template_file != NULL && CFG->template_s != NULL) {
    fsio_write_text_file(CFG->template_file, CFG->template_s);
  }
  assert(CFG->template_file != NULL);
  assert(CFG->output_file != NULL);
  assert(CFG->input_json_file != NULL);
  assert(jinja2_path != NULL);
  assert(fsio_file_exists(jinja2_path) == true);
  char *CMD;

  asprintf(&CMD,
           "%s"
           " --strict"
           " --format=json"
           " --outfile='%s'"
           " '%s'"
           " '%s'",
           jinja2_path,
           CFG->output_file,
           CFG->template_file,
           CFG->input_json_file
           );
  if (CFG->debug_mode == true) {
    fprintf(stdout, "%s\n", CMD);
  }
  const char           *exec_cmd[] = {
    sh_path, "--norc", "--noprofile", "-c", CMD, NULL,
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
  if (result != 0 || exited != 0) {
    fprintf(stderr, "Jinja Subprocess Failed! exited:%d|result:%d\n", exited, result);
  }
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


static void __attribute__((constructor)) __jinja2_cli_constructor(void){
  if (getenv("DEBUG_MODE") != NULL) {
    printf("     Loading jinja2-cli binary........%s\n", JINJA2_CLI_BINARY_NAME);
    printf("             size: %d\n", inc_binary_jinja2_cli_size);
  }
}
static void __attribute__((destructor)) __jinja2_cli_destructor(void){
}

