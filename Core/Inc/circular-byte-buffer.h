#ifndef _CIRC_BBUF_H_
#define _CIRC_BBUF_H_

#include <stdint.h>

typedef struct {
    uint8_t * const buffer;
    int head;
    int tail;
    const int maxlen;
} circ_bbuf_t;

#if 1
#define CIRC_BBUF_DEF(x, y)               \
    uint8_t x##_data_space[y];            \
    circ_bbuf_t x = {                     \
        .buffer = x##_data_space,         \
        .head = 0,                        \
        .tail = 0,                        \
        .maxlen = y                       \
    }
#else
#define CIRC_BBUF_DEF(x, y)     \
    uint8_t x##_data_space[y];  \
    circ_bbuf_t x = {           \
        x##_data_space,         \
        0,                      \
        0,                      \
        y                       \
    }
#endif

int circ_bbuf_is_buffer_empty(circ_bbuf_t *c);
int circ_bbuf_is_buffer_full(circ_bbuf_t *c);
int circ_bbuf_push(circ_bbuf_t *c, uint8_t data);
int circ_bbuf_pop(circ_bbuf_t *c, uint8_t *data);
void circ_bbuf_reset(circ_bbuf_t *c);

#endif
