#pragma once
#ifndef CHAN_UTILS_H
#define CHAN_UTILS_H
//////////////////////////////////////
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "chan/src/chan.h"
#include "chan/src/queue.h"
#include "hash/hash.h"
#include "module/require.h"
#include "module/module.h"
#include "module/def.h"
#include "c_vector/vector/vector.h"
#include "c_workqueue/include/workqueue.h"
#include "chan-utils/chan-utils-types.h"
#include "ansi-codes/ansi-codes.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"
void cu_chans_receive(void *RECV);
void cu_chans_start(void *REQ);
void cu_chans_send(void *REQ);
void cu_chan_wait(void *RECV);
void cu_chans_wait(void *REQ);
void work_fn(void *);


#endif
