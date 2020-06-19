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
//    scheduling.h
//
// DESCRIPTION:
// -----------
// Scheduling algorithms.
//------------------------------------------------------------------------------

#include "scheduling.h"
#include "processor.h"
#include "debug.h"
#include <stdio.h>


/* TODO: - Refactor code to get rid of repetetive code;
 *       - Check if SJF is working;
 *       - Add a limit of instructions to execute for the scheduling algorithms (Round Robin in this case);
 */

int fcfs(PCB *pcb, MEMORY *mem, int pcbindex) {
    /* Chegou ao fim da tabela PCB, não há mais processos em fila */
    debug("Working on PCB index %d.\n", pcbindex);
    if ((size_t) pcbindex >= pcb->top)
        return SCHEDULER_END;
    
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

int sorted(process *p, size_t size) {
    for (size_t i = 1; i < size; i++) {
        if (p[i-1].timelimit > p[i].timelimit)
            return 0;
    }
    return 1;
}

int comparebt(const void *v1, const void *v2) { // compara o Burst time dos processos
    const process *p1 = (process *)v1;
    const process *p2 = (process *)v2;

    if (p1->timelimit == p2->timelimit) return 0;
    else if (p1->timelimit < p2->timelimit)
        return -1;
    else return 1;
}

int sjf(PCB *pcb, MEMORY *mem, int pcbindex) {
    debug("Working on PCB index %d.\n", pcbindex);
    
    // Reorganizar o PCB por Burst Time
    if (!sorted(pcb->proc, pcb->size)) {
        qsort(pcb->proc, pcb->size, sizeof(process), comparebt);
        pcbindex = 0;
    }

    // Chegou ao fim da tabela PCB, não há mais processos em fila
    if ((size_t) pcbindex >= pcb->top)
        return SCHEDULER_END;

    process *p = &(pcb->proc[pcbindex]);
    switch (p->state)
    {
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
            pcbindex = sjf(pcb, mem, ++pcbindex);
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




int checkPCBStatus(PCB *pcb) {
    for (size_t i = 0; i < pcb->top; i++) {
        if (pcb->proc[i].state != STATUS_TERMINATED && pcb->proc[i].state != STATUS_BLOCKED)
            return 0;
    }
    return 1;
}

int rrobin(PCB *pcb, MEMORY *mem, int pcbindex) {
    debug("Working on PCB index %d.\n", pcbindex);
    // if ((size_t) pcbindex >= pcb->top)
    if (checkPCBStatus(pcb))
        return SCHEDULER_END;

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
            if (w.pcb.rr_time == SCHEDULING_COUNTER) {
                p->state = switchState(p->state, STATUS_READY);
                if ((size_t) pcbindex + 1 >= pcb->top)
                    pcbindex = -1;
                pcbindex++;
                w.pcb.rr_time = 0;
            }
            break;
        
        case STATUS_TERMINATED:
            debug("Process with PID %d is TERMINATED.\n", p->pid);
            if ((size_t) pcbindex + 1 >= pcb->top)
                pcbindex = -1;
            pcbindex++;
            break;

        case STATUS_BLOCKED:
            debug("Process with PID %d is BLOCKED.\n", p->pid);
            if ((size_t) pcbindex + 1 >= pcb->top)
                pcbindex = -1;
            pcbindex++;
            break;
        
        default:
            fprintf(stderr, "ERROR: Unknown process state. ABORTING!\n");
            exit(-1);
            break;
    }

    return pcbindex;
}