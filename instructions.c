#include "processor.h"

// file to do the 7 types of intructions

void changeValue (process * p, int n)
{
    p->id = n;
}

void addValue(process * p, int n)
{
    p->id += n;
}

void subtractValue(process * p, int n)
{
    p->id -= n;
}

void blockProcess(process * p)
{
    return; // ???
}

void terminateProcess(process * p)
{
    return; // ???
}

process createNewProcess(process * p, int n)
{
    process new_p = (process *) malloc (sizeof process);
    new_p->id = p->id+1; //find better scheme to number child processes
    new_p->state = p->state;
    new_p->counter = p->counter;
    new_p->pid =p->id;
    new_p->priority = p->priority;
    new_p->time_limit = p->time_limit;
    //add whatever else is added in the data sctructure

    return new_p;
}

void cleanProgram(char * filename)
{
    return;
}
