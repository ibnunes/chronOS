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
//    tui.h
//
// DESCRIPTION:
// -----------
// Text user interface.
//------------------------------------------------------------------------------


#include "tui.h"
#include "types.h"
#include "heapmgr.h"
#include <stdio.h>

const char *state2str(int state) {
    switch (state) {
        case STATUS_NULL:
            return "Null";
        case STATUS_NEW:
            return "New";
        case STATUS_READY:
            return "Ready";
        case STATUS_RUNNING:
            return "Running";
        case STATUS_BLOCKED:
            return "Blocked";
        case STATUS_TERMINATED:
            return "Terminated";
        default:
            return "Unknown";
    }
}

void pcbreport(PCB *pcb) {
    printf("======== Report =========\n\n");
    printf("Current time: %ld\n\n", cputime);

    process *p;
    printf("+-------------------------------------------------------+-----+---------+--------------------+\n");
    printf("|                       PROCESS                         | MEM |         |        TIME        |\n");
    printf("|       Name       | PID | PPID | Priority |   Status   | ind | Context | Init | Used | End  |\n");
    printf("+------------------+-----+------+----------+------------+-----+---------+------+------+------+\n");
    for (size_t i = 0; i < pcb->size; i++) {
        p = &(pcb->proc[i]);
        if (p->pid != -1) {
            printf(
                "| %16s | %3d | %4d | %8d | %10s | %3ld | %7d | %4ld | %4ld | %4ld |\n",
                p->name, p->pid, p->ppid, p->priority, state2str(p->state),
                p->start,
                p->context,
                p->timeinit, p->timeused, p->timeend
            );
        }
    }
    printf("+------------------+-----+------+----------+------------+-----+---------+------+------+------+\n\n");
    
    printf("===== End of report =====\n\n");
}


void heapreport(HEAP *first, HEAP *next, HEAP *best, HEAP *worst) {
    struct heapstat {
        int   frag;     // Número de fragmentos externos
        float time;     // Tempo médio de alocação
        float neg;      // Percentagem de vezes que uma alocação foi negada
    } f, n, b, w;

    f.frag = heapfragcount(first);
    f.time = first->time / first->crossed;
    f.neg  = (float) first->negated / first->calls * 100;

    n.frag = heapfragcount(next);
    n.time = next->time / next->crossed;
    n.neg  = (float) next->negated / next->calls * 100.;

    b.frag = heapfragcount(best);
    b.time = best->time / best->crossed;
    b.neg  = (float) best->negated / best->calls * 100.;

    w.frag = heapfragcount(worst);
    w.time = worst->time / worst->crossed;
    w.neg  = (float) worst->negated / worst->calls * 100.;
    
    printf("====== Heap memory ======\n\n");
    printf("+-----------+----------------+----------------+----------------+\n");
    printf("| Algorithm |   # fragments  | Alloc avg time |  Perc no-alloc |\n");
    printf("+-----------+----------------+----------------+----------------+\n");
    printf("| First-fit | %14d | %14.3f | %14.3f |\n", f.frag, f.time, f.neg);
    printf("|  Next-fit | %14d | %14.3f | %14.3f |\n", n.frag, n.time, n.neg);
    printf("|  Best-fit | %14d | %14.3f | %14.3f |\n", b.frag, b.time, b.neg);
    printf("| Worst-fit | %14d | %14.3f | %14.3f |\n", w.frag, w.time, w.neg);
    printf("+-----------+----------------+----------------+----------------+\n");
    printf("=== End of heap memory ==\n\n");
}


#ifndef NDEBUG

void memreport(MEMORY *mem) {
    printf("======== Memory =========\n\n");
    printf("+------+-----+-----+------------------+\n");
    printf("| Cell | Ins |  n  |       name       |\n");
    printf("+------+-----+-----+------------------+\n");
    for (size_t i = 0; i < mem->capacity; i++) {
        if (mem->cells[i].ins != INSTRUCTION_VOID) {
            printf(
                "| %4ld | %3c | %3d | %16s |\n",
                i, mem->cells[i].ins, mem->cells[i].n, mem->cells[i].name
            );
        }
    }
    printf("+------+-----+-----+------------------+\n");
    printf("===== End of memory =====\n\n");
}

#endif
