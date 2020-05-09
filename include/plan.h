#ifndef PLAN_H
#define PLAN_H

#include <stdlib.h>

#define cpu_t unsigned long long
#define DEFAULT_CPU 500ULL   // 500 milissegundos

#define DEFAULT_PLAN_Q_SIZE 10
#define MAX_PROGRAM 50

typedef struct {
    char program[MAX_PROGRAM];
    cpu_t time;
} PLAN;
// typedef int PLAN;  // for debugging purposes

typedef struct {
    PLAN *list;
    size_t head;
    size_t capacity;
    size_t last;
} plan_q;

typedef char CONTROL;


/* === Queue === */
plan_q *plan_new(size_t);
void plan_push(plan_q*, char*, cpu_t);
PLAN plan_peek(plan_q*);
PLAN plan_pop(plan_q*);
int plan_empty(plan_q*);
int plan_length(plan_q*);
void plan_free(plan_q*);
/* ============= */

plan_q *plan_read_from_file(const char *);


#endif