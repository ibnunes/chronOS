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
        // add more as necessary...
    }
    return pcb;
}

void pcbfree(PCB *pcb) {    
    free(pcb);
}

int getPCBIndex(PCB *pcb, int PID) {
    int counter = 0;

    while(pcb[counter].p->id != PID) {
        counter++;
    }
    return counter;
}

int getEndCounter(PCB *pcb, int PID)
{
    //rewrite whole function to get the following process's start value.
    int counter = getPCBIndex(pcb, PID);
    // nao deve haver razao de verificar se o processo esta ou nao na tabela se o seu id chegou a este ponto.
    for(int i = counter + 1 ; i <= MAX_PCB; i++) {
        pcb[i-1] = pcb[i];
    }
    return pcb[counter].start;
}