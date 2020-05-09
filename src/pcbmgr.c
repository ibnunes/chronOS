#include "pcbmgr.h"

PCB *pcballoc(size_t nmemb) {
    PCB *pcb = malloc(nmemb * sizeof(PCB));
    for (size_t i = 0; i < nmemb; i++) {
        // strcpy(pcb[i].name, NULL);
        pcb[i].start = 0;
        // add more as necessary...
    }
    return pcb;
}


void pcbfree(PCB *pcb) {
    free(pcb);
}