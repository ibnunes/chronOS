#ifndef PCBMGR_H
#define PCBMGR_H

#include <stdlib.h>
// #include <string.h>

typedef struct{
    char name;
    int  start;
    // add whatever else is needed
} PCB;


PCB *pcballoc(size_t nmemb);
void pcbfree(PCB *pcb);

#endif