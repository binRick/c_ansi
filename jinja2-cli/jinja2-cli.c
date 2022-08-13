#define STDOUT_READ_BUFFER_SIZE        1024 * 8
#define JINJA2_CLI_BINARY_FILE_NAME    "jinja2"
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
static int32_t jinja2_cli_utils_random_int32(uint8_t *out, size_t outlen);

///////////////////////////////////////////////////////
#include "jinja2-cli/jinja2-cli-inc.c"
#include "jinja2-cli/jinja2-cli.h"
///////////////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
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
  char *cp = getenv("PATH");

  if (cp != NULL && strlen(cp) > 0) {
    unsetenv("PATH");
  }
  bool                WROTE_TEMP_J2_BINARY = false;
  char                *READ_STDOUT;
  int                 exited, result;
  struct subprocess_s subprocess;
  char                *jinja2_path = NULL;
  unsigned long       ul;
  char                *temp_incbin_jinja2_binary;
  size_t              rand_int32 = jinja2_cli_utils_random_int32(&ul, 16);
  bool                j2_exists  = false;
  char                *temp_dir  = gettempdir();

  if (temp_dir == NULL || (false == fsio_file_exists(temp_dir))) {
    temp_dir = "/tmp/";
  }
  asprintf(&temp_incbin_jinja2_binary, "%s/%lu-%d-%llu-%s", temp_dir, ul, getpid(), timestamp(), JINJA2_CLI_BINARY_FILE_NAME);
  fsio_write_binary_file(temp_incbin_jinja2_binary, inc_binary_jinja2_cli_data, inc_binary_jinja2_cli_size);
  fsio_chmod_recursive(temp_incbin_jinja2_binary, FSIO_MODE_ALL);
  assert(fsio_file_exists(temp_incbin_jinja2_binary) == true);
  assert(fsio_file_size(temp_incbin_jinja2_binary) == inc_binary_jinja2_cli_size);
  jinja2_path          = temp_incbin_jinja2_binary;
  WROTE_TEMP_J2_BINARY = true;
  assert(fsio_file_exists(jinja2_path) == true);
  assert(fsio_file_size(jinja2_path) > 0);
  asprintf(&CFG->template_file, "%s.jinja2-template-%lld-%lu-%d.txt", temp_dir, timestamp(), ul, getpid());
  asprintf(&CFG->output_file, "%s.jinja2-output-file-%lld-%lu-%d.json", temp_dir, timestamp(), ul, getpid());
  asprintf(&CFG->input_json_file, "%s.jinja2-input-vars-%lld-%lu-%d.json", temp_dir, timestamp(), ul, getpid());
  if (CFG->debug_mode == true) {
    fprintf(stdout, AC_RESETALL AC_YELLOW "CFG->input_json_file: %s" AC_RESETALL "\n", CFG->input_json_file);
  }
  {
    assert(CFG->template_file != NULL);
    assert(CFG->output_file != NULL);
    assert(CFG->input_json_file != NULL);
    assert(jinja2_path != NULL);
  }
  fsio_write_text_file(CFG->input_json_file, CFG->input_json_string);
  fsio_write_text_file(CFG->template_file, CFG->template_s);
  {
    assert(fsio_file_exists(jinja2_path) == true);
    assert(fsio_file_exists(CFG->input_json_file) == true);
    assert(fsio_file_exists(CFG->template_file) == true);
  }
  if (CFG->debug_mode) {
    fprintf(stderr, ">PATH:     %s\n", getenv("PATH"));
    fprintf(stderr, ">jinja2_path:     %s\n", jinja2_path);
    fprintf(stderr, ">output_file:     %s\n", CFG->output_file);
    fprintf(stderr, ">template_file:     %s\n", CFG->template_file);
    fprintf(stderr, ">input_json_file:     %s\n", CFG->input_json_file);
  }
  const char           *exec_cmd[] = {
    jinja2_path, "--strict", "--format=json", "--outfile", CFG->output_file, CFG->template_file, CFG->input_json_file, NULL,
  };
  char                 stdout_buffer[STDOUT_READ_BUFFER_SIZE] = { 0 };
  struct  StringBuffer *SB = stringbuffer_new_with_options(STDOUT_READ_BUFFER_SIZE, true);
  size_t               bytes_read = 0,
                       index = 0;
  size_t               retries = 0, max_retries = 5;

  while (retries < max_retries) {
    result = subprocess_create(exec_cmd, 0, &subprocess);
    if (result == 0) {
      break;
    }
    sleep(1);
    retries++;
  }
  if (result != 0) {
    fprintf(stderr, "result: %d\n", result);
  }
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
    fprintf(stdout, AC_RESETALL AC_RED  "%s" AC_RESETALL "\n", stringbuffer_to_string(SB));
  }

  result = subprocess_join(&subprocess, &exited);
  if (result != 0 || exited != 0) {
    fprintf(stderr, "Jinja Subprocess Failed! exited:%d|result:%d\n", exited, result);
    return(EXIT_FAILURE);
  }
  CFG->output_s = fsio_read_text_file(CFG->output_file);
  fsio_remove(CFG->output_file);
  fsio_remove(CFG->input_json_file);
  fsio_remove(CFG->template_file);
  if (WROTE_TEMP_J2_BINARY == true) {
    fsio_remove(jinja2_path);
  }
  READ_STDOUT = stringbuffer_to_string(SB);
  stringbuffer_release(SB);
  if (CFG->debug_mode == true) {
    fprintf(stderr, AC_RESETALL AC_CYAN "stdout:  "  "%s" AC_RESETALL "\n", READ_STDOUT);
  }
  if (exited != 0 || strlen(CFG->output_s) < 1) {
    fprintf(stderr, "Exit code: %d\n", exited);
    fprintf(stderr, "stdout:  %s", READ_STDOUT);
    return(EXIT_FAILURE);
  }
  CFG->success = true;

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

int32_t jinja2_cli_utils_random_int32(uint8_t *out, size_t outlen){
  FILE *fpurandom = fopen("/dev/urandom", "r");

  if (!fpurandom) {
    return(-1);
  }
  int32_t bread = fread(out, 1, outlen, fpurandom);

  fclose(fpurandom);
  return(bread < outlen ? -1 : bread);
}
