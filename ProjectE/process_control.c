#include "process_control.h"

struct PCB process_queue[8];
struct PCB *currentProcess;

void Initialize()
{
	int i;
	for(i=0;i<8;i++)
	{
		process_queue[i].status=4;
		process_queue[i].sp=0xff00;
	}
	process_queue[0].segment=0x2000;
	process_queue[1].segment=0x3000;
	process_queue[2].segment=0x4000;
	process_queue[3].segment=0x5000;
	process_queue[4].segment=0x6000;
	process_queue[5].segment=0x7000;
	process_queue[6].segment=0x8000;
	process_queue[7].segment=0x9000;
	
	currentProcess=0;
}

int getFreeSegment()
{
	int i;
	
	for(i=0; i<8; i++) {
		if(process_queue[i].status==4) {
			process_queue[i].status==1;
			return process_queue[i].segment;
		}
	}
	return -1;
}


