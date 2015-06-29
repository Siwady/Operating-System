#ifndef PROCESS_CONTROL_H
#define PROCESS_CONTROL_H

struct PCB {
	unsigned int status;   //Process status
	unsigned int sp;	   //Stack pointer
	unsigned int segment;  //Process segment
	struct PCB *waiter;    //Process waiting on this process
};

struct regs {
	unsigned int es;
	unsigned int ds;
	unsigned int ax;
	unsigned int bp;
	unsigned int di;
	unsigned int si;
	unsigned int dx;
	unsigned int cx;
	unsigned int bx;
	unsigned int ip;
	unsigned int cs;
	unsigned int flags;
};


void Initialize();
int getFreeSegment();
void killProcess(int index);
struct PCB* getProcess(int index);
void setStatusToReady(int index); 
void setStatusToWaiting(int index);
void setStatusToDead(int index);  
void setStatusToRunning(int index);
void setCurrentProcess(struct PCB* p);
struct PCB* getCurrentProcess();

#endif
