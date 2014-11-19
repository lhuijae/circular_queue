#include <stdio.h>
#include <string.h>
#include "circular_queue.h"

int main(int argc,char*argv[])
{
	p_circular_queue p_cq = cq_init(10);
	char buffer[10] = {0};
	cq_write(p_cq,"1234567",strlen("1234567"));
	cq_read(p_cq,buffer,5);
	cq_print(p_cq);
	cq_read(p_cq,buffer,5);
	cq_print(p_cq);
	printf("buffer:%s\n",buffer);
	if(cq_is_empty(p_cq))
		printf("circular queue is empty! \n");
	cq_write(p_cq,buffer,5);
	cq_print(p_cq);
	cq_write(p_cq,buffer,5);
	cq_print(p_cq);
	if(cq_is_full(p_cq))
		printf("circular queue is full! \n");
	cq_reset_max_length(&p_cq,5);
	cq_print(p_cq);
	cq_reset_max_length(&p_cq,15);
	cq_print(p_cq);
	cq_destory(p_cq);
}
