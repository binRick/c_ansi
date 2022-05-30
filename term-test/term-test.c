#include "term-test.h"
#include "../term-utils/term-utils.h"
args_t args = {
  DEFAULT_MODE,
  DEFAULT_VERBOSE,
  DEFAULT_COUNT,
  DEFAULT_PRETTY,
  DEFAULT_COLOR,
  DEFAULT_PALETTE_NAME,
  DEFAULT_PALETTE_FILE,
};


int debug_args(){
  fprintf(stderr,
          acs(AC_BRIGHT_BLUE_BLACK AC_ITALIC  "Verbose: %d")
          ", "
          ansistr(AC_RESETALL AC_BRIGHT_GREEN_BLACK "Mode: %s")
          ", "
          ansistr(AC_RESETALL AC_UNDERLINE "Count: %d")
          "\n"
          ansistr(AC_RESETALL AC_UNDERLINE "Pretty Mode: %d")
          "\n"
          ansistr(AC_RESETALL AC_UNDERLINE "Color Mode: %d")
          "\n"
          ansistr(AC_RESETALL AC_UNDERLINE "Palette: %s")
          "\n"
          ansistr(AC_RESETALL AC_UNDERLINE "File: %s")
          "\n",
          args.verbose, args.mode, args.count,
          args.pretty, args.color,
          args.palette, args.file
          );
  return(EXIT_SUCCESS);
}


int parse_args(int argc, char *argv[]){
  char               identifier;
  const char         *value;
  cag_option_context context;

  cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);
  while (cag_option_fetch(&context)) {
    identifier = cag_option_get(&context);
    switch (identifier) {
    case 'm':
      value     = cag_option_get_value(&context);
      args.mode = value;
      break;
    case 'f':
      value     = cag_option_get_value(&context);
      args.file = value;
      break;
    case 'p':
      value        = cag_option_get_value(&context);
      args.palette = value;
      break;
    case 'P':
      args.pretty = true;
      break;
    case 'x':
      args.color = true;
      break;
    case 'v':
      args.verbose = true;
      break;
    case 'c':
      value      = cag_option_get_value(&context);
      args.count = atoi(value);
      break;
    case 'h':
      printf(AC_RESETALL AC_YELLOW AC_BOLD "Usage: cargsdemo [OPTION]...\n" AC_RESETALL);
      printf("Demonstrates the cargs library.\n\n");
      cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
      printf("\nNote that all formatting is done by cargs.\n");
      return(EXIT_SUCCESS);
    }
  }


  return(EXIT_SUCCESS);
} /* parse_args */


int main(int argc, char **argv) {
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf("Test OK\n"); return(0);
  }

  return(term_utils_main(argc, argv));

  printf(AC_RESETALL AC_RED "No mode selected: %s\n" AC_RESETALL, args.mode);
  return(1);

  return(EXIT_SUCCESS);
}
