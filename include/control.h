#ifndef CONTROL_H
#define CONTROL_H

#include "types.h"

control_q *control_new(size_t);

void control_push(control_q*, char);

char control_peek(control_q*);

char control_pop(control_q*);

int control_empty(control_q*);

int control_length(control_q*);

void control_free(control_q*);

control_q *control_read_from_file(const char *);

int execcontrol(char operation, PCB *pcb, int pcbindex);

char control_scan(void);

#endif