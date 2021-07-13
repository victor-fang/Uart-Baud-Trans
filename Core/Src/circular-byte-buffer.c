#include "circular-byte-buffer.h"

int circ_bbuf_is_buffer_empty(circ_bbuf_t *c) {
	return (c->head == c->tail);
}

int circ_bbuf_is_buffer_full(circ_bbuf_t *c) {
	return ((c->head + 1) % c->maxlen == c->tail);
}

int circ_bbuf_push(circ_bbuf_t *c, uint8_t data)
{
    int next;

    next = c->head + 1;  // next is where head will point to after this write.
    if (next >= c->maxlen)
        next = 0;

    if (next == c->tail)  // if the head + 1 == tail, circular buffer is full
        return -1;

    c->buffer[c->head] = data;  // Load data and then move
    c->head = next;             // head to next data offset.
    return 0;  // return success to indicate successful push.
}

int circ_bbuf_pop(circ_bbuf_t *c, uint8_t *data)
{
    int next;

    if (c->head == c->tail)  // if the head == tail, we don't have any data
        return -1;

    next = c->tail + 1;  // next is where tail will point to after this read.
    if(next >= c->maxlen)
        next = 0;

    *data = c->buffer[c->tail];  // Read data and then move
    c->tail = next;              // tail to next offset.
    return 0;  // return success to indicate successful pop.
}

void circ_bbuf_reset(circ_bbuf_t *c)
{
	c->head = 0;
	c->tail = 0;
}

