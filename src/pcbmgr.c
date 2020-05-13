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

PCB *pcballoc(size_t nmemb) {
    PCB *pcb  = malloc(sizeof(PCB));
    pcb->proc = malloc(nmemb * sizeof(process));
    pcb->size = nmemb;
    pcb->top  = 0;

    for (size_t i = 0; i < pcb->size; i++) {
        // pcb->proc[i].name = "";
        pcb->proc[i].start      = 0;
        pcb->proc[i].id         = 0;
        pcb->proc[i].context    = 0;
        pcb->proc[i].counter    = 0;
        pcb->proc[i].pid        = 0;
        pcb->proc[i].priority   = 0;
        pcb->proc[i].time_limit = MAX_TIMELIMIT;
        pcb->proc[i].state      = STATUS_NULL;
        pcb->proc[i].insNum     = 0;
        // add more as necessary...
    }
    return pcb;
}

void pcbfree(PCB *pcb) {
    free(pcb->proc);
    free(pcb);
}

long pcb_index_of_pid(int PID, PCB *pcb) {
    for (size_t i = 0; i < pcb->size; i++)
        if (pcb->proc[i].id == PID)
            return i;
    return (-1);
}
