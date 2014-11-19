
#ifndef _CIRCULAR_QUEUE_H

#define _CIRCULAR_QUEUE_H

#include <stdlib.h>

struct _circular_queue;
typedef struct _circular_queue  circular_queue ,* p_circular_queue;

p_circular_queue cq_init(size_t max_length);

void cq_clear(p_circular_queue cq);

void cq_destory(p_circular_queue cq);

size_t cq_write(p_circular_queue cq ,const char* buffer , size_t buffer_length);

size_t cq_read(const p_circular_queue cq,char* buffer , size_t buffer_length);

size_t cq_cur_length(const p_circular_queue cq);

size_t cq_max_length(const p_circular_queue cq);

int cq_reset_max_length(p_circular_queue* cq,int new_max_length);

int cq_is_empty(const p_circular_queue cq);

int cq_is_full(const p_circular_queue cq);

void cq_print(const p_circular_queue cq);

#endif //_CIRCULAR_QUEUE_H
