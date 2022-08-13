///////////////////////////////////////////////
#define DEBUG_MSG(_MSG)    { do {                                                                                 \
                               termpaint_attr *P = termpaint_attr_new(0, TERMPAINT_RGB_COLOR(10, 20, 30));        \
                               termpaint_surface_write_with_attr(surface, 0, 31, _MSG, P);                        \
                               termpaint_surface_write_with_colors(surface,                                       \
                                                                   0, 30,                                         \
                                                                   _MSG,                                          \
                                                                   TERMPAINT_COLOR_GREEN, TERMPAINT_COLOR_BLACK); \
                               termpaint_terminal_flush(terminal, false);                                         \
                             } while (0); }

#define HANDLE_EVENTS()    { do {                                                                     \
                               if (evt->type == TERMPAINT_EV_CHAR && strcmp(evt->string, "q") == 0) { \
                                 quit = true;                                                         \
                               }                                                                      \
                             } while (0); }
///////////////////////////////////////////
