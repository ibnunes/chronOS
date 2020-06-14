//------------------------------------------------------------------------------
//
// chronOS - A scheduling simulator
//
//    Copyright (C) 2020 Igor Cordeiro Bordalo Nunes (www.igornunes.com)
//    Copyright (C) 2020 Jorge Miguel Louro Pissarra
//    Copyright (C) 2020 Diogo Castanheira Simões
//    Copyright (C) 2020 Universidade da Beira Interior (www.ubi.pt)
//
//  	This program is free software: you can redistribute it and/or modify
//  	it under the terms of the GNU General Public License as published by
//  	the Free Software Foundation, either version 3 of the License, or
//  	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//	Contacts:
//			Igor Nunes     <igor.bordalo.nunes@ubi.pt>
//			Jorge Pissarra <jorge.pissarra@ubi.pt>
//          Diogo Simões   <diogo.c.simoes@ubi.pt>
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DESCRIPTION:
// -----------
// This program is an operating system scheduling simulator. It is built around
// two main components:
//     * A process simulator;
//     * A memory manager.
// It is able to use different algorithms to schedule processes.
// The processes consist of changing an unique integer variable.
// The memory manager uses a first-fit algorithm.
//
// SYNOPSIS:
// --------
// 	chronos [< control.txt]
//
// where:
//     'control.txt' is an optional text file to manipulate the process manager.
//
// FILE FORMAT:
// -----------
// Described at 'plan.h'
//
// LANGUAGE AND CURRENT VERSION:
// ----------------------------
// English, no release version yet
//------------------------------------------------------------------------------


#include "simulator.h"
#include "fcfs.h"
#include "tui.h"
#include <time.h>


int main(int argc, char const *argv[]) {
    printf("===== chronOS 1.2.0 =====\n\n");

    int __running = 1;
    cputime = 0;

    write("Initializing...\n");

    // 1.1. Alocar células de memória 
    debug("Allocating %d cells of memory\n", MAX_MEM);
    memory = memcreate(MAX_MEM);

    // 1.2. Alocar memória heap
    debug("Allocating %d KB of heap memory for 4 algorithms\n", HEAP_CAPACITY * BLOCK_SIZE);
    heap_first = makeheap(HEAP_CAPACITY);
    heap_next  = makeheap(HEAP_CAPACITY);
    heap_best  = makeheap(HEAP_CAPACITY);
    heap_worst = makeheap(HEAP_CAPACITY);

    // 2. Inicializar tabela PCB
    debug("Allocating %d lines of PCB table\n", MAX_PCB);
    pcb = pcballoc(MAX_PCB);

    // 3. Inicializar queue de plano com o ficheiro plan.txt
    debug("Reading plan queue from %s:\n", FILE_PLAN);
    plan = plan_read_from_file(FILE_PLAN);
    debug("Got %d elements in queue.\n", plan_length(plan));
    write("Got %d elements in queue.\n", plan_length(plan));

    clock_t clock_start, clock_end;
    float seconds;
    
    int __mustexit = 0;
    int pcbindex = 0;

    time_t t;
    heaprequest_start((unsigned) time(&t));


    int schedualer_timer = 0;

    /* Ciclo principal do programa */
    while (__running) {
        if (!plan_empty(plan)) {
            if (plan_peek(plan).time <= cputime) {
                debug("cputime = %ld; plan_peek.time = %ld\n", cputime, plan_peek(plan).time);
                write("Creating new process from \"%s\" at CPU time %ld\n", plan_peek(plan).program, cputime);
                create_new_process(pcb, plan_pop(plan).program);
                __mustexit = 0;
            }
        }
        
        /* Gestão de processos */
        if (!__mustexit) {
            if (heaprequest()) {
                int size = heaprequest_size();
                int ret = heapalloc(PID_CHRONOS, size);
                debug("Random request from chronOS of %d blocks of heap memory (return code = %d)\n", size, ret);
                write("Random request from chronOS of %d blocks of heap memory (return code = %d)\n", size, ret);
            }
            switch (schedualing_algorithm)
            {
                case FCFS:
                    pcbindex = fcfs(pcb, memory, pcbindex);
                    break;
                case SJF:
                    pcbindex = sjf(pcb, memory, pcbindex);
                    break;
                case RR:
                    pcbindex = rrobin(pcb, memory, pcbindex, schedualer_timer);
                    break;
                default:
                    pcbindex = fcfs(pcb, memory, pcbindex); //leaving fcfs as default for now, change later if needed
                    break;
            }
            if (pcbindex == FCFS_END) {
                debug("Reached FCFS_END.\n");
                write("Reached end of FCFS plan.\n");
                __mustexit = 1;
            }
        }
        
        /* Clock do processador */
        clock_start = clock();
        while (1) {
            clock_end = clock();
            seconds = (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
            if (seconds >= DEFAULT_TIME_QUANTUM) {
                cputime++;
                schedualer_timer++;
                break;
            }
        }

        // Verificar condições nas quais o simulador deve terminar
        if (plan_empty(plan) && __mustexit)
            __running = 0;
    }

    debug("Deallocating heap memory requested by chronOS...\n");
    write("Deallocating heap memory requested by chronOS...\n");
    heapfree(PID_CHRONOS);  // para evitar memory leaks na heap memory por parte do chronOS

    write("Reached end of execution. Printing final reports...\n\n");

    pcbreport(pcb);
    memreport(memory);
    heapreport(heap_first, heap_next, heap_best, heap_worst);
    heapdump(heap_first, "first-fit");
    heapdump(heap_next,  "next-fit");
    heapdump(heap_best,  "best-fit");
    heapdump(heap_worst, "worst-fit");

    write("Finalizing...\n");

    // -3. Libertar queue de plano
    debug("Freeing plan queue\n");
    plan_free(plan);

    // -2.1 Libertar memória
    debug("Freeing memory\n");
    memdestroy(memory);

    // -2.2 Libertar memória heap
    debug("Freeing heap memory (4 components)\n");
    destroyheap(heap_first);
    destroyheap(heap_next);
    destroyheap(heap_best);
    destroyheap(heap_worst);

    // -1. Libertar tabela PCB
    debug("Freeing PCB table\n");
    pcbfree(pcb);

    return 0;
}
