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


#include "debug.h"
#include "tui.h"
#include "simulator.h"

/* Variáveis globais */
// MEMORY *memory;         // Memória
// PCB    *pcb;            // Tabela PCB (Process Control Block)
// cpu_t  cputime;         // Tempo atual do processador
// plan_q *plan;           // Plano: lista de processos e tempos de entrada


int main(int argc, char const *argv[]) {
    /* TODO:
     *  [OK] -> Alocar memória
     *  [  ] -> Inicializar gestor de processos
     *  [  ] -> Inicializar gestor de memória
     *  [OK] -> Ler plan.txt
     *  [  ] -> Ler control.txt ou stdin
     *  [  ] -> Passar controlo ao gestor de processos
     */

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



    /* Ciclo principal do programa */
    


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


