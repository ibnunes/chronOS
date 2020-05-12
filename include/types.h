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

/* ======================================== *
 * processor.h                              *
 * ======================================== */

/* Struct: process
 * ---------------
 * Represents a process.
 * 
 *  int id: identifies the process with a unique integer value.
 *  int context: represents the mutable value which will be altered by the processor.
 *  int * counter: points towards the current instruction that process is at.
 *  int pid: identifies the parent process.
 *  int priority: defines the priority of execution of the process.
 *  int time_limit: ???how to define this???
 *  char state: represents which state of execution the process is at.
 *  int PCBposition: represents index in which process is stored in PCB.
 */
typedef struct {
    int  id;         
    int  context;    
    int *counter;    
    int  pid;        
    int  priority;   
    int  time_limit; 
    char state;      
    int  PCBposition;
    // add whatever else is needed
} process;

#define STATUS_NEW 0            // Estado do processo: new
#define STATUS_READY 1          // Estado do processo: ready
#define STATUS_RUNNING 2        // Estado do processo: running
#define STATUS_BLOCKED 3        // Estado do processo: blocked
#define STATUS_TERMINATED 4     // Estado do processo: terminated


/* ======================================== *
 * pcbmgr.h                                 *
 * ======================================== */

#define MAX_PCB 100             // Nº de entradas da tabela PCB

/* Struct:  PCB
 * ------------
 * Represents Process Control Block.
 * TODO!
 * 
 * 
 */
typedef struct{
    char name;
    int  start;
    process *p;
} PCB;


/* ======================================== *
 * memmgr.h                                 *
 * ======================================== */

#define MAX_MEM 1000            // Nº de células de memória
#define MAX_NAME 15             // Nº máximo de caracteres de um programa
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