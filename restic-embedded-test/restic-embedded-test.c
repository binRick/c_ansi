////////////////////////////////////////////
#define INCBIN_SILENCE_BITCODE_WARNING
#define INCBIN_STYLE     INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX    inc_
////////////////////////////////////////////
#include "incbin/incbin.h"
INCBIN(ResticBinary, "restic");
#define EMBEDDED_RESTIC_BINARY_FILE_NAME    "embedded-restic"
#include "restic-embedded-test/restic-embedded-test.h"
////////////////////////////////////////////
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "subprocess.h/subprocess.h"
#include "tempdir.c/tempdir.h"
#include "timestamp/timestamp.h"
#include "uuid4/src/uuid4.h"
////////////////////////////////////////////
static const char *restic_embedded_file_path;
#define STDOUT_READ_BUFFER_SIZE    1024 * 16
static char       *msg;

//////////////////////////////////////////////
TEST t_restic_embedded_test_create_repo(){
  long unsigned       started = timestamp(), dur = 0;
  struct subprocess_s subprocess;
  int                 result, exited;
  bool                new_repo_exists = false;
  char                *RESTIC_REPOSITORY, *RESTIC_PASSWORD, *test_repo_path, restic_password[UUID4_LEN];

  asprintf(&test_repo_path, "%stest-repo-%lu.repo", gettempdir(), (size_t)timestamp());
  uuid4_generate(restic_password);
  asprintf(&RESTIC_REPOSITORY, "%s=%s", "RESTIC_REPOSITORY", test_repo_path);
  asprintf(&RESTIC_PASSWORD, "%s=%s", "RESTIC_PASSWORD", restic_password);
  ASSERT_NEQ(test_repo_path, NULL);
  ASSERT_NEQ(restic_password, NULL);
  ASSERT_NEQ(RESTIC_REPOSITORY, NULL);
  ASSERT_NEQ(RESTIC_PASSWORD, NULL);
  log_info("Creating new repo at path %s with password %s|env vars: %s, %s|restic path: %s",
           test_repo_path, restic_password, RESTIC_PASSWORD, RESTIC_REPOSITORY, restic_embedded_file_path);
  const char *command_line[] = { restic_embedded_file_path, "init", NULL, };
  const char *environment[]  = { RESTIC_PASSWORD, RESTIC_REPOSITORY, NULL, };

  ASSERT_NEQ(environment, NULL);
  ASSERT_NEQ(command_line, NULL);
  result = subprocess_create_ex(command_line, 0, environment, &subprocess);
  ASSERT_EQ(result, 0);
  result = subprocess_join(&subprocess, &exited);
  ASSERT_EQ(result, 0);
  ASSERT_EQ(exited, 0);
  dur             = timestamp() - started;
  new_repo_exists = fsio_dir_exists(test_repo_path);
  ASSERT_EQ(new_repo_exists, true);
  asprintf(&msg, "Created new repo at %s with password %s in %s", test_repo_path, restic_password,
           milliseconds_to_string(dur)
           );
  PASSm(msg);
}

TEST t_restic_embedded_test_deploy(){
  int                  exited, result;
  size_t               bytes_read = 0;
  char                 *restic_help_output = NULL, stdout_buffer[STDOUT_READ_BUFFER_SIZE] = { 0 };
  struct subprocess_s  subprocess             = { 0 };
  const char           *restic_help_command[] = { restic_embedded_file_path, "--help", NULL };
  struct  StringBuffer *SB                    = stringbuffer_new_with_options(STDOUT_READ_BUFFER_SIZE, true);

  result = subprocess_create(restic_help_command, 0, &subprocess);
  ASSERT_EQ(result, 0);
  do {
    bytes_read = subprocess_read_stdout(&subprocess, stdout_buffer, STDOUT_READ_BUFFER_SIZE - 1);
    stringbuffer_append_string(SB, stdout_buffer);
  } while (bytes_read != 0);
  result = subprocess_join(&subprocess, &exited);
  ASSERT_EQ(result, 0);
  ASSERT_EQ(exited, 0);
  restic_help_output = stringbuffer_to_string(SB);
  stringbuffer_release(SB);
  ASSERT_NEQ(restic_help_output, NULL);
  ASSERT_GTE(strlen(restic_help_output), 10);
  log_info(AC_YELLOW AC_ITALIC "%s" AC_RESETALL, restic_help_output);
  asprintf(&msg, "Validated %lu byte Restic Help Stdout Content", strlen(restic_help_output));
  PASSm(msg);
}

TEST t_restic_embedded_test_incbin(){
  size_t file_size;

  ASSERT_GTE(inc_ResticBinary_size, 1024);
  file_size = fsio_file_size(restic_embedded_file_path);
  ASSERT_EQ(inc_ResticBinary_size, file_size);
  asprintf(&msg, "Validated %lu byte incbin embedded data matches original", (size_t)inc_ResticBinary_size);
  PASSm(msg);
}

TEST t_restic_embedded_deploy(){
  bool exists; size_t file_size;

  ASSERT_NEQ(restic_embedded_file_path, NULL);
  fsio_write_binary_file(restic_embedded_file_path, inc_ResticBinary_data, inc_ResticBinary_size);
  fsio_chmod_recursive(restic_embedded_file_path, 0700);
  exists = fsio_file_exists(restic_embedded_file_path);
  if (exists == true) {
    fsio_remove(restic_embedded_file_path);
    exists = fsio_file_exists(restic_embedded_file_path);
  }
  ASSERT_EQ(exists, false);
  fsio_write_binary_file(restic_embedded_file_path, inc_ResticBinary_data, inc_ResticBinary_size);
  fsio_chmod_recursive(restic_embedded_file_path, 0700);
  exists = fsio_file_exists(restic_embedded_file_path);
  ASSERT_EQ(exists, true);
  file_size = fsio_file_size(restic_embedded_file_path);
  ASSERT_EQ(file_size, inc_ResticBinary_size);
  asprintf(&msg, "Deployed %lu byte binary to %s", file_size, restic_embedded_file_path);
  PASSm(msg);
}

SUITE(s_restic_test_incbin) {
  RUN_TEST(t_restic_embedded_test_incbin);
}
SUITE(s_restic_embedded_test_deploy) {
  RUN_TEST(t_restic_embedded_test_deploy);
}
SUITE(s_restic_embedded_deploy) {
  RUN_TEST(t_restic_embedded_deploy);
}
SUITE(s_restic_embedded_test_create_repo) {
  RUN_TEST(t_restic_embedded_test_create_repo);
}

GREATEST_MAIN_DEFS();

int main(const int argc, const char **argv) {
  uuid4_init();
  asprintf(&restic_embedded_file_path, "%s/%s", gettempdir(), EMBEDDED_RESTIC_BINARY_FILE_NAME);
  fsio_write_binary_file(restic_embedded_file_path, inc_ResticBinary_data, inc_ResticBinary_size);
  fsio_chmod_recursive(restic_embedded_file_path, 0700);
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_restic_test_incbin);
  RUN_SUITE(s_restic_embedded_deploy);
  RUN_SUITE(s_restic_embedded_test_deploy);
  RUN_SUITE(s_restic_embedded_test_create_repo);
  if (fsio_file_exists(restic_embedded_file_path) == true) {
    fsio_remove(restic_embedded_file_path);
  }
  GREATEST_MAIN_END();
}
