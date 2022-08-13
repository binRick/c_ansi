#pragma once
#define INCBIN_SILENCE_BITCODE_WARNING
#define INCBIN_STYLE              INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX             inc_binary_
#define JINJA2_CLI_BINARY_NAME    "inc_binary_jinja2_cli"

#include "incbin/incbin.h"

INCBIN(jinja2_cli, "bin/jinja2-cli");
INCBIN(meson, "bin/meson");
