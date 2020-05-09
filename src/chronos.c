#include "debug.h"
#include "tui.h"
#include "simulator.h"

#define MAX_MEM 1000
#define MAX_PCB 100

/* Variáveis globais */
MEMORY *memory;      // Memória
PCB *pcb;           // Process Control Block
cpu_t cputime;      // Tempo atual do processador
plan_q *plan;       // Plano: lista de processos e tempos de entrada


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


