#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "circular_queue.h"

struct _circular_queue {
	size_t rear;
	size_t font;
	size_t max_length;
	size_t cur_length;
	char* data;
};

p_circular_queue cq_init(size_t max_length)
{
	p_circular_queue cq = NULL;
	cq = (p_circular_queue)malloc(sizeof(circular_queue)+(max_length+1));
	assert(cq != NULL);
	cq->cur_length = 0;
	cq->font = 0;
	cq->rear = 0;
	cq->max_length = max_length;
	cq->data = (char*)(cq+sizeof(circular_queue));

	return cq;
}

void cq_clear(p_circular_queue cq){
	assert (cq->data != NULL);
	cq->cur_length = 0;
	cq->font = cq->rear = 0;
}

void cq_destory(p_circular_queue cq){
	if (cq == NULL)
		return;

	cq->cur_length = 0;
	cq->font = 0;
	cq->rear = 0;
	cq->max_length = 0;
	free(cq);
}

size_t cq_write(p_circular_queue cq ,const char* buffer , size_t buffer_length){
	assert(cq->data != NULL);
	assert(buffer != NULL && buffer_length != 0 );

	size_t written_length = buffer_length < cq->max_length - cq->cur_length ? buffer_length : cq->max_length - cq->cur_length;
	if(written_length == 0)
		return 0;
	size_t rear_available_length = cq->max_length+1 - cq->rear;
	if(rear_available_length >= written_length)
	{
		memcpy(cq->data + cq->rear , buffer ,written_length);
		cq->rear += written_length;
	}
	else
	{
		memcpy(cq->data + cq->rear, buffer ,rear_available_length);
		memcpy(cq->data , buffer + rear_available_length ,written_length -  rear_available_length);
		cq->rear = written_length -  rear_available_length;
	}
	cq->cur_length += written_length;

	return written_length;
}

size_t cq_read(const p_circular_queue cq,char* buffer , size_t buffer_length){
	assert(cq->data != NULL);
	assert(buffer != NULL && buffer_length > 0);

	size_t read_length = buffer_length < cq->cur_length ? buffer_length :  cq->cur_length;
	if(0 == read_length)
		return 0;
	size_t part_font_length = cq->max_length + 1 - cq->font;
	if (part_font_length >= read_length)
	{
		memcpy(buffer,cq->data+cq->font,read_length);
		cq->font += read_length;
	} 
	else
	{
		memcpy(buffer,cq->data+cq->font,part_font_length);
		memcpy(buffer+part_font_length,cq->data,read_length - part_font_length);
		cq->font = read_length - part_font_length;
	}

	cq->cur_length -= read_length;

	return read_length;
}


size_t cq_cur_length(const p_circular_queue cq)
{
	assert(cq != NULL);
	return cq->cur_length;
}

size_t cq_max_length(const p_circular_queue cq){
	assert(cq != NULL);
	return cq->max_length;
}

int cq_reset_max_length(p_circular_queue *cq,int new_max_length){
	assert((*cq)->data != NULL);
	if(new_max_length < (*cq)->cur_length)
		return -1;

	int temp_buffer_length = (*cq)->cur_length;
	char* temp_buffer = (char*)malloc(temp_buffer_length);
	cq_read((*cq),temp_buffer,temp_buffer_length);
	cq_destory((*cq));
	(*cq) = cq_init(new_max_length);
	cq_write((*cq),temp_buffer,temp_buffer_length);
	free(temp_buffer);

	return 0;
}

int cq_is_empty(const p_circular_queue cq)
{
	assert(cq != NULL);
	return cq->font == cq->rear;
}

int cq_is_full(const p_circular_queue cq)
{
	assert(cq != NULL);
	return (cq->rear + 1)%(cq->max_length+1) == cq->font;
}

void cq_print(const p_circular_queue cq)
{
	if(cq_is_empty(cq))
		return;
	size_t i = cq->font;
	do{
		i = i % (cq->max_length+1);
		printf("%c",(cq->data)[i]);
	}while( (++i)%(cq->max_length+1) != cq->rear );

	printf(";rear:%d;font:%d;cur_len:%d;max_len:%d\n",cq->rear,cq->font,cq->cur_length,cq->max_length);
}
