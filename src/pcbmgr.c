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
    PCB *pcb = malloc(nmemb * sizeof(PCB));
    for (size_t i = 0; i < nmemb; i++) {
        // pcb[i].name = "";
        pcb[i].start = 0;
        pcb[i].id = 0;
        pcb[i].context = 0;
        pcb[i].counter = 0;
        pcb[i].pid = 0;
        pcb[i].priority = 0;
        pcb[i].time_limit = MAX_TIMELIMIT;
        pcb[i].state = STATUS_NULL;
        pcb[i].insNum = 0;
        // add more as necessary...
    }
    return pcb;
}

void pcbfree(PCB *pcb) {    
    free(pcb);
}

long pcb_index_of_pid(int PID, PCB *pcb, size_t size) {
    for (size_t i = 0; i < size; i++)
        if (pcb[i].id == PID)
            return i;
    return (-1);
}
