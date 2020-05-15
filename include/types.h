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
//    types.h
//
// DESCRIPTION:
// -----------
// Data types for the whole program.
//------------------------------------------------------------------------------


#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <time.h>

/* Strings úteis ao programa */
#define PROG_EXTENSION ".prg"           // Extensão de um programa que corre no simulador
#define FILE_PLAN      "plan.txt"       // Ficheiro com o plano de execução
#define FILE_CONTROL   "control.txt"    // Ficheiro com os comandos de controlo

/* ======================================== *
 * processor.h                              *
 * ======================================== */

#define MAX_NAME 15             // Nº máximo de caracteres de um programa

/* Struct: process
 * ---------------
 * Represents a process.
 * 
 *  char *name: name of the file containing the program.
 *  int start: index of the first instruction
 *  int pid: identifies the process with a unique integer value.
 *  int context: represents the mutable value which will be altered by the processor.
 *  int counter: points towards the current instruction that process is at.
 *  int ppid: identifies the parent process.
 *  int priority: defines the priority of execution of the process.
 *  int timelimit: burst time of the process
 *  int state: represents which state of execution the process is at.
 *  int instsize: number of instructions associated with this process.
 *  clock_t timeinit: time at which it started.
 *  clock_t timeused: time used at CPU while processing.
 *  clock_t timeend: time at which the process terminated.
 */
typedef struct {
    char    name[MAX_NAME];
    size_t  start;
    int     pid;         
    int     context;    
    int     counter;    
    int     ppid;        
    int     priority;   
    clock_t timelimit; 
    int     state;
    size_t  instsize;
    clock_t timeinit;
    clock_t timeused;
    clock_t timeend;
    // add whatever else is needed
} process;

#define STATUS_NULL 0               // Processo não existe: null
#define STATUS_NEW 1                // Estado do processo: new
#define STATUS_READY 2              // Estado do processo: ready
#define STATUS_RUNNING 3            // Estado do processo: running
#define STATUS_BLOCKED 4            // Estado do processo: blocked
#define STATUS_TERMINATED 5         // Estado do processo: terminated

#define PRIORITY_NULL 0             // Prioridade: nula
#define PRIORITY_MIN 1              // Prioridade: mínima
#define PRIORITY_MAX 5              // Prioridade: máxima

#define INSTRUCTION_CHANGE 'M'      // M n
#define INSTRUCTION_ADD 'A'         // A n
#define INSTRUCTION_SUBTRACT 'S'    // S n
#define INSTRUCTION_BLOCK 'B'       // B
#define INSTRUCTION_TERMINATE 'T'   // T
#define INSTRUCTION_FORK 'C'        // C n
#define INSTRUCTION_CLEAR 'L'       // L filename


/* ======================================== *
 * pcbmgr.h                                 *
 * ======================================== */

#define MAX_PCB 100             // Nº de entradas da tabela PCB
#define MEMPCB_ALLOC_NOAVAIL -2 // Erro: não há espaço na tabela PCB
#define PID_NULL -1             // PID nulo: não há processo nesta linha da tabela

/* Struct:  PCB
 * ------------
 * Represents Process Control Block.
 * 
 *  proc: list of processes
 *  size: size of the list
 *  top: the top index from which we can add new processes
 */
typedef struct {
    process *proc;
    size_t  size;
    size_t  top;
} PCB;        // workaround for the meantime

#define MAX_TIMELIMIT 100   // (temporário) burst time de um processo


/* ======================================== *
 * memmgr.h                                 *
 * ======================================== */

#define MAX_MEM 1000            // Nº de células de memória
#define MAX_INSTRUCTION 30      // Nº máximo de caracteres de uma instrução num ficheiro
#define INSTRUCTION_VOID '\0'   // Instrução void: indica célula de memória livre
#define MEMERR_ALLOC_NOAVAIL -1 // Erro: não há memória imediatamente disponível

/* Struct:  instruction
 * --------------------
 * Represents an instruction, which is a char followed by a number or a string.
 * 
 *  char ins: the instruction.
 *  int n: the variable increment.
 *  char *name: the name of the child process.
 */
typedef struct {
    char ins;               // Instrução
    int  n;                 // Incremento ou decremento da variável
    char name[MAX_NAME];    // Nome do processo filho
} instruction;

/* Struct:  MEMORY
 * ---------------
 * It is a memory structure that contains cells with instructions from programs.
 * 
 *  instruction *cells: the cells containing instructions
 *  size_t capacity: capacity of memory
 */
typedef struct {
    instruction *cells;     // Células de memória
    size_t capacity;        // Capacidade total de memória
} MEMORY;


/* ======================================== *
 * plan.h                                   *
 * ======================================== */

// #define cpu_t unsigned long long    // Tempo da CPU em milissegundos

#define DEFAULT_PLAN_Q_SIZE 8       // Tamanho por defeito de uma queue
#define MAX_PROGRAM 50              // Tamanho máximo do nome de um programa

typedef struct {
    char    program[MAX_PROGRAM];
    clock_t time;
} PLAN;

typedef struct {
    PLAN *list;
    size_t head;
    size_t capacity;
    size_t last;
} plan_q;

#endif