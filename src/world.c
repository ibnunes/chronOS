#include "world.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <libgen.h>
#include <errno.h>
#include "debug.h"

void halt(int e, char const *msg) {
    if (e != 0) errno = e;
    perror(msg);
    exit(EXIT_FAILURE);
}

void startworld(struct world *world) {
    // Informação da aplicação
    strcpy(world->app.name, APP_NAME);
    strcpy(world->app.version, APP_VERSION);

    // Variáveis do ciclo principal de execução do chronOS
    world->pid         = PID_CHRONOS;
    world->cputime     = 0;
    world->timequantum = DEFAULT_TIME_QUANTUM;

    // Flags de controlo do fluxo do programa
    world->flag.__running  = 1;
    world->flag.__mustexit = 0;

    // Memória heap
    time_t t;
    world->heap.capacity      = HEAP_CAPACITY;
    world->heap.blocksize     = BLOCK_SIZE;
    world->heap.shouldrequest = HEAP_REQUEST_ACTIVE;
    world->heap.requestseed   = (unsigned) time(&t);

    // Memória estática
    world->memory.capacity = MAX_MEM;

    // Process Control Table
    world->pcb.size      = MAX_PCB;
    world->pcb.index     = 0;
    world->pcb.algorithm = SCHEDULING_FCFS;
    world->pcb.rr_time   = 0;

    // Ficheiro de planeamento de execução
    strcpy(world->fileplan, FILE_PLAN);

    world->control.controller = CONTROLLER_AUTO;
    strcpy(world->control.file, FILE_CONTROL);
    world->control.quantum_limit = DEFAULT_CONTROL_QUANTUM;
    world->control.quantum_curr = 0;
    world->control.currentoperation = CONTROL_EXECUTE;
    world->control.fetch = 1;
}


void loadargs(struct world *world, int argc, char const *argv[]) {
    char bin[PATH_MAX + 1];
    char temp[PATH_MAX + 1];
    char zero[PATH_MAX + 1];

    strcpy(zero, argv[0]);
    if (zero[0] == '.')
        memmove(&zero[0], &zero[0 + 1], strlen(zero) - 0);
    if (getcwd(bin, sizeof(bin)) == NULL)
        halt(0, "Could not retrieve current directory");
    strcat(bin, dirname(zero));
    strcat(bin, "/");

    strcpy(temp, bin);
    strcpy(world->pwd, temp);
    strcat(temp, world->fileplan);
    strcpy(world->fileplan, temp);

    strcpy(temp, bin);
    strcat(temp, world->control.file);
    strcpy(world->control.file, temp);

    int i = 0;
    while (i + 1 < argc) {
        i++;

        if (strcmp(argv[i], "--control") == 0 || strcmp(argv[i], "-c") == 0) {
            i++;
            if (i >= argc) halt(EINVAL, "Insuficient arguments for control");
            if (strcmp(argv[i], "auto") == 0) {
                world->control.controller = CONTROLLER_AUTO;
                debug("Control set to automatic.\n");
                write("Control set to automatic.\n");

            } else if (strcmp(argv[i], "stdin") == 0) {
                world->control.controller = CONTROLLER_STDIN;
                debug("Control set to be read from stdin.\n");
                write("Control set to be read from stdin.\n");

            } else if (strcmp(argv[i], "file") == 0) {
                world->control.controller = CONTROLLER_FILE;
                debug("Control set to be read from file.\n");
                write("Control set to be read from file.\n");

            } else {
                halt(EINVAL, "Unknown control source");
            }
            
            continue;
        }

        if (strcmp(argv[i], "--no-heap-request") == 0 || strcmp(argv[i], "-n") == 0) {
            world->heap.shouldrequest = HEAP_REQUEST_INACTIVE;
            debug("Random heap request turned off.\n");
            write("Random heap request turned off.\n");
            continue;
        }

        if (strcmp(argv[i], "--seed") == 0 || strcmp(argv[i], "-s") == 0) {
            i++;
            if (i >= argc) halt(EINVAL, "Insuficient arguments for seed");
            world->heap.requestseed = atoi(argv[i]);
            debug("Heap request seed defined as %d\n", world->heap.requestseed);
            write("Heap request seed defined as %d\n", world->heap.requestseed);
            continue;
        }

        if (strcmp(argv[i], "--fcfs") == 0) {
            world->pcb.algorithm = SCHEDULING_FCFS;
            debug("Scheduling algorithm defined as FCFS\n");
            write("Scheduling algorithm defined as FCFS\n");
            continue;
        }

        if (strcmp(argv[i], "--sjf") == 0) {
            world->pcb.algorithm = SCHEDULING_SJF;
            debug("Scheduling algorithm defined as SJF\n");
            write("Scheduling algorithm defined as SJF\n");
            continue;
        }

        if (strcmp(argv[i], "--rr") == 0 || strcmp(argv[i], "--robin") == 0 || strcmp(argv[i], "--round-robin") == 0) {
            world->pcb.algorithm = SCHEDULING_RROBIN;
            debug("Scheduling algorithm defined as round-robin\n");
            write("Scheduling algorithm defined as round-robin\n");
            continue;
        }

        if (strcmp(argv[i], "--psa") == 0) {
            world->pcb.algorithm = SCHEDULING_PSA;
            debug("Scheduling algorithm defined as PSA\n");
            write("Scheduling algorithm defined as PSA\n");
            continue;
        }
    }
}
