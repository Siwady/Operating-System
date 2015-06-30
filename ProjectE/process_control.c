#include "process_control.h"
struct PCB process_queue[8];
struct PCB *currentProcess=0;

void Initialize()
{
	int i;
	int segment=0x2000;
	for(i=0;i<8;i++)
	{
		process_queue[i].status=4;
		process_queue[i].sp=0xff0;
		process_queue[i].segment=segment;
		segment+=4096;
	}	
	currentProcess=0;
}

int getFreeSegment()
{
	int i;
	
	for(i=0; i<8; i++) {
		if(process_queue[i].status==4) {
			process_queue[i].status=1;
			return process_queue[i].segment;
		}
	}
	return -1;
}

void killProcess(int index)
{
	if(index>1 && index<=8){
		process_queue[index-1].status=4;
	}
}

struct PCB* getProcess(int index)
{
	return process_queue[index];
}

void setStatusToReady(int index)
{
	process_queue[index].status=1;
} 

void setStatusToWaiting(int index)
{
	process_queue[index].status=2;
}

void setStatusToRunning(int index)
{
	process_queue[index].status=3;
}

void setStatusToDead(int index)
{
	process_queue[index].status=4;
}  

void setCurrentProcess(struct PCB* p)
{
	currentProcess=p;
}

struct PCB* getCurrentProcess()
{
	return currentProcess;
}


