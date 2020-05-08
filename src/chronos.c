#include "debug.h"
#include "tui.h"
#include "simulator.h"

#define MAX_MEM 1000
#define MAX_PCB 100

MEMORY memory;
PCB *pcb;


int main(int argc, char const *argv[]) {
    /* TODO:
     * 1. Alocar memória
     * 2. Inicializar gestor de processos
     * 3. Inicializar gestor de memória
     * 4. Ler plan.txt
     * 5. Ler control.txt ou stdin
     * 6. Passar controlo ao gestor de processos
     */

    // 1. Alocar células de memória 
    debug("Allocating %d cells of memory\n", MAX_MEM);
    memory.cells = memalloc(MAX_MEM);

    // 2. Inicializar tabela PCB
    debug("Allocating %d lines of PCB table\n", MAX_PCB);
    pcb = pcballoc(MAX_PCB);



    // -2. Libertar memória
    debug("Freeing memory\n");
    memfree(memory.cells);

    // -1. Libertar tabela PCB
    debug("Freeing PCB table\n");
    pcbfree(pcb);

    return 0;
}


