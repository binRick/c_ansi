#pragma once
#include "../ansi-codes/ansi-codes.h"
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define X_STR(STR)                        #STR
#define X_FXN(STR)                        X_STR(STR)
#define DO_ANSI_FXN(TITLE, FXN, COLOR)    { do{                                  \
                                              printf(COLOR);                     \
                                              printf(TITLE);                     \
                                              printf(">");                       \
                                              printf(AC_RESETALL);               \
                                              printf("\t");                      \
                                              printf(AC_YELLOW_BLACK AC_ITALIC); \
                                              printf(X_STR(FXN));                \
                                              printf(AC_RESETALL);               \
                                              printf(":");                       \
                                              printf(AC_RESETALL);               \
                                              printf("\t");                      \
                                              printf("\"");                      \
                                              FXN;                               \
                                              printf(AC_RESETALL);               \
                                              printf("\"\n");                    \
                                            }while (0); }
#define ANSI_FXN(S, FXN, COLOR)           { do{                                                        \
                                              if ((argc >= 2) && (strcmp(argv[1], X_STR(--S)) == 0)) { \
                                                return(0);                                             \
                                              }                                                        \
                                            }while (0); }
#define ANSI_ARG(S, M, C)                 { do{                                                        \
                                              if ((argc >= 2) && (strcmp(argv[1], X_STR(--S)) == 0)) { \
                                                printf(acsl(AC_RESETALL AC_YELLOW C M));               \
                                                return(0);                                             \
                                              }                                                        \
                                            }while (0); }

#include "ansi-test-cases.h"

