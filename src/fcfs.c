//------------------------------------------------------------------------------
//
// chronOS - A scheduling simulator
//
//    Copyright (C) 2020 Igor Cordeiro Bordalo Nunes (www.igornunes.com)
//    Copyright (C) 2020 Jorge Miguel Louro Pissarra
//    Copyright (C) 2020 Diogo Castanheira Simões
//    Copyright (C) 2020 Universidade da Beira Interior (www.ubi.pt)
//
// RUNTIME LIBRARIES PACKAGE
//    fcfs.h
//
// DESCRIPTION:
// -----------
// First Come First Serve algorithm.
//------------------------------------------------------------------------------

#include "fcfs.h"
#include "processor.h"
#include "debug.h"
#include <stdio.h>


int fcfs(PCB *pcb, MEMORY *mem, int pcbindex) {
    /* Chegou ao fim da tabela PCB, não há mais processos em fila */
    debug("Working on PCB index %d.\n", pcbindex);
    if ((size_t) pcbindex >= pcb->top)
        return FCFS_END;
    
    process *p = &(pcb->proc[pcbindex]);
    switch (p->state) {
        case STATUS_NEW:
            debug("Switching PID %d state to READY.\n", p->pid);
            p->state = switchState(p->state, STATUS_READY);
            break;
        
        case STATUS_READY:
            debug("Switching PID %d state to RUNNING.\n", p->pid);
            p->state = switchState(p->state, STATUS_RUNNING);
            p->timeinit = cputime;
            break;
        
        case STATUS_RUNNING:
            debug("Running PID %d, instruction at PC=%d...\n", p->pid, p->counter);
            p->timeused++;
            run(mem, p);
            break;
        
        case STATUS_TERMINATED:
            debug("Process with PID %d is TERMINATED.\n", p->pid);
            pcbindex++;
            break;

        case STATUS_BLOCKED:
            debug("Process with PID %d is BLOCKED.\n", p->pid);
            pcbindex++;
            break;
        
        default:
            fprintf(stderr, "ERROR: Unknown process state. ABORTING!\n");
            exit(-1);
            break;
    }

    return pcbindex;
}

int findsj(PCB *pcb) // TODO: clean up funtion 
{
    int tempPCBCounter = 0;
    int shortestJobIndex = MAX_TIMELIMIT;
    while(tempPCBCounter < pcb->size)
    {
        if(pcb->proc[tempPCBCounter].state != STATUS_READY) // not sure if ready status is the right one for the processes to be in
            continue;
        if(pcb->proc[tempPCBCounter].timelimit < shortestJobIndex)
        shortestJobIndex = tempPCBCounter;
        tempPCBCounter++;
    }
    return shortestJobIndex;
}

int sjf(PCB *pcb, MEMORY *mem, int pcbindex)
{
    debug("Working on PCB index %d.\n", pcbindex);
    if ((size_t) pcbindex >= pcb->top)
        return FCFS_END;

    process *p = &(pcb->proc[pcbindex]);
    switch (p->state) {
        case STATUS_NEW:
            debug("Switching PID %d state to READY.\n", p->pid);
            p->state = switchState(p->state, STATUS_READY);
            break;
        
        case STATUS_READY:
            debug("Switching PID %d state to RUNNING.\n", p->pid);
            p->state = switchState(p->state, STATUS_RUNNING);
            p->timeinit = cputime;
            break;
        
        case STATUS_RUNNING:
            debug("Running PID %d, instruction at PC=%d...\n", p->pid, p->counter);
            p->timeused++;
            run(mem, p);
            break;
        
        case STATUS_TERMINATED:
            debug("Process with PID %d is TERMINATED.\n", p->pid);
            pcbindex = findsj(pcb);
            break;

        case STATUS_BLOCKED:
            debug("Process with PID %d is BLOCKED.\n", p->pid);
            pcbindex = findsj(pcb);
            break;
        
        default:
            fprintf(stderr, "ERROR: Unknown process state. ABORTING!\n");
            exit(-1);
            break;
    }

    return pcbindex;
}

int rrobin(PCB *pcb, MEMORY *mem, int pcbindex)
{
    debug("Working on PCB index %d.\n", pcbindex);
    if ((size_t) pcbindex >= pcb->top)
        return FCFS_END;

    process *p = &(pcb->proc[pcbindex]);
    switch (p->state) {
        case STATUS_NEW:
            debug("Switching PID %d state to READY.\n", p->pid);
            p->state = switchState(p->state, STATUS_READY);
            break;
        
        case STATUS_READY:
            debug("Switching PID %d state to RUNNING.\n", p->pid);
            p->state = switchState(p->state, STATUS_RUNNING);
            p->timeinit = cputime;
            break;
        
        case STATUS_RUNNING:
            debug("Running PID %d, instruction at PC=%d...\n", p->pid, p->counter);
            p->timeused++;
            run(mem, p);
            break;
        
        case STATUS_TERMINATED:
            debug("Process with PID %d is TERMINATED.\n", p->pid);
            // move to next job or if last go back to first job
            break;

        case STATUS_BLOCKED:
            debug("Process with PID %d is BLOCKED.\n", p->pid);
            // move to next job or if last go back to first job
            break;
        
        default:
            fprintf(stderr, "ERROR: Unknown process state. ABORTING!\n");
            exit(-1);
            break;
    }

    return pcbindex;
}