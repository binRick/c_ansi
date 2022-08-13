#include <stdbool.h>
///////////////////////////////////////////////
///        TYPES                            ///
///////////////////////////////////////////////
enum cell_t { DEAD,
              ALIVE };
typedef struct board_t_ {
  int  width;
  int  height;
  char *cells;
} board_t;
board_t board;
typedef struct CURSOR_PROFILE {
  int  x;
  int  y;
  bool visible, blink;
  int  style;
} cursor_profile_t;
typedef struct event_ {
  int           type;
  int           modifier;
  const char    *string;
  struct event_ *next;
} event;
