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
#include "tui.h"
#include <time.h>


int main(int argc, char const *argv[]) {
    /* TODO:
     *  [OK] -> Alocar memória
     *  [  ] -> Inicializar gestor de processos
     *  [OK] -> Inicializar gestor de memória
     *  [OK] -> Ler plan.txt
     *  [  ] -> Ler control.txt ou stdin
     *  [  ] -> Passar controlo ao gestor de processos
     */

    int __running = 1;
    cputime = 0;

    // 1. Alocar células de memória 
    debug("Allocating %d cells of memory\n", MAX_MEM);
    memory = memcreate(MAX_MEM);

    // 2. Inicializar tabela PCB
    debug("Allocating %d lines of PCB table\n", MAX_PCB);
    pcb = pcballoc(MAX_PCB);

    // 3. Inicializar queue de plano com o ficheiro plan.txt
    debug("Reading plan queue from %s:\n", FILE_PLAN);
    plan = plan_read_from_file(FILE_PLAN);
    debug("Got %d elements in queue.\n", plan_length(plan));


    clock_t clock_start, clock_end;
    float seconds;

    /* Ciclo principal do programa */
    while (__running) {
        if (plan_peek(plan).time <= cputime) {
            debug("cputime = %ld; plan_peek.time = %ld\n", cputime, plan_peek(plan).time);
            create_new_process(pcb, plan_pop(plan).program);

            /*
            size_t n;
            PLAN p = plan_pop(plan);
            instruction *i = program_read_from_file(p.program, &n);
            int address = memalloc(memory, i, n);
            free(i);
            debug("%ld instructions from %s allocated to address %d.\n", n, p.program, address);
            */
        }


        // chamar função de processamento, p.e. fcfs


        clock_start = clock();
        while (1) {
            clock_end = clock();
            seconds = (float)(clock_end - clock_start) / CLOCKS_PER_SEC;
            if (seconds >= DEFAULT_TIME_QUANTUM) {
                cputime++;
                break;
            }
        }

        // TODO: verificar se o simulador deve terminar
        if (plan_empty(plan))  // faltam condições
            __running = 0;
    }

    pcbreport(pcb);

    // -3. Libertar queue de plano
    debug("Freeing plan queue\n");
    plan_free(plan);

    // -2. Libertar memória
    debug("Freeing memory\n");
    memdestroy(memory);

    // -1. Libertar tabela PCB
    debug("Freeing PCB table\n");
    pcbfree(pcb);

    return 0;
}
