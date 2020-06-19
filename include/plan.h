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
//    plan.h
//
// DESCRIPTION:
// -----------
// Plan management.
//------------------------------------------------------------------------------


#ifndef PLAN_H
#define PLAN_H

#include "types.h"

/* Allocates heap memory to a new queue with data about the plan. */
plan_q *plan_new(size_t);

/* Inserts a new plan element to the queue. */
void plan_push(plan_q*, char*, clock_t, int);

/* Peeks the head of the queue without popping it. */
PLAN plan_peek(plan_q*);

/* Pops the head element of the queue. */
PLAN plan_pop(plan_q*);

/* Checks if the queue is empty. */
int plan_empty(plan_q*);

/* Returns the number of elements currently present on the queue. */
int plan_length(plan_q*);

/* Frees all resources from the queue. */
void plan_free(plan_q*);

/* Reads a plan from a file and returns a new queue with its contents. */
plan_q *plan_read_from_file(const char *);

#endif