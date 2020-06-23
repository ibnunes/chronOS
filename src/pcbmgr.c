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
//    pcbmgr.h
//
// DESCRIPTION:
// -----------
// Process Control Block management.
//------------------------------------------------------------------------------


#include "pcbmgr.h"
#include "data.h"
#include <string.h>

PCB *pcballoc(size_t nmemb) {
    PCB *pcb  = malloc(sizeof(PCB));
    pcb->proc = malloc(nmemb * sizeof(process));
    pcb->size = nmemb;
    pcb->top  = 0;

    for (size_t i = 0; i < pcb->size; i++) {
        pcb->proc[i].start     = 0;
        pcb->proc[i].pid       = -1;
        pcb->proc[i].context   = 0;
        pcb->proc[i].counter   = 0;
        pcb->proc[i].ppid      = -1;
        pcb->proc[i].priority  = PRIORITY_NULL;
        pcb->proc[i].timelimit = MAX_TIMELIMIT;
        pcb->proc[i].state     = STATUS_NULL;
        pcb->proc[i].instsize  = 0;
        pcb->proc[i].timeinit  = 0;
        pcb->proc[i].timeused  = 0;
        pcb->proc[i].timeend   = 0;
    }
    return pcb;
}

int maxpid(PCB *pcb) {
    int max = 0;
    for (size_t i = 0; i < pcb->size; i++)
        if (pcb->proc[i].pid > max)
            max = pcb->proc[i].pid;
    return max;
}

int processalloc(PCB *pcb, int ppid, char* name, size_t memlocal, size_t instsize, int priority) {
    if (pcb->top >= pcb->size)
        return MEMPCB_ALLOC_NOAVAIL;        // Não há espaço!

    int i  = pcb->top;                      // shortcut to PCB top index
    int ip = pcb_index_of_pid(ppid, pcb);   // shortcut to parent process index
    process *p = &(pcb->proc[i]);           // shortcut to current new process
    process *parent = (ip == -1) ? NULL : &(pcb->proc[ip]); // shortcut to parent process

    strcpy(p->name, name);
    p->start     = memlocal;
    p->ppid      = ppid;
    p->pid       = maxpid(pcb) + 1;
    p->context   = (parent != NULL) ? parent->context : 0;
    p->counter   = memlocal;
    p->priority  = (parent != NULL) ? parent->priority : priority;
    p->timelimit = (parent != NULL) ? parent->timelimit : MAX_TIMELIMIT;
    p->state     = STATUS_NEW;
    p->instsize  = instsize;
    p->timeinit  = w.cputime;         // TO CHECK: will it work properly?
    p->timeused  = 0;
    p->timeend   = 0;

    pcb->top++;

    return i;   // retorna o índice onde foi colocado na tabela PCB
}

void pcbfree(PCB *pcb) {
    free(pcb->proc);
    free(pcb);
}

long pcb_index_of_pid(int PID, PCB *pcb) {
    for (size_t i = 0; i < pcb->size; i++)
        if (pcb->proc[i].pid == PID)
            return i;
    return (-1);
}
