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
        pcb[i].start = 0;
        // pcb[i].name  = "";
        // add more as necessary...
    }
    return pcb;
}

void pcbfree(PCB *pcb) {    
    free(pcb);
}

/*int getPCBIndex(PCB *pcb, int PID) { //decidir depois se ainda e precisa esta funçao mas por agora fica comentada
    int counter = 0;

    while(pcb[counter].p->id != PID) {
        counter++;
    }
    return counter;
}*/
