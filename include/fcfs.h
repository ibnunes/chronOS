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
//    fcfs.h
//
// DESCRIPTION:
// -----------
// First Come First Serve algorithm.
//------------------------------------------------------------------------------

#ifndef FCFS_H
#define FCFS_H

#include "types.h"

/* Struct:  int_q
 * --------------
 * Queue of integers
 * 
 *  int *list: the list of ints themselves
 *  size_t head: head of the queue (first to be popped)
 *  size_t capacity: capacity of the queue
 *  size_t last: last element of the queue
 * 
 *  return: 
 */
typedef struct {
    int    *list;
    size_t head;
    size_t capacity;
    size_t last;
} int_q;

/* Allocates heap memory to a new queue for ints. */
int_q *int_new(size_t);

/* Inserts a new int element to the queue. */
void int_push(int_q*, int);

/* Peeks the head of the queue without popping it. */
int int_peek(int_q*);

/* Pops the head element of the queue. */
int int_pop(int_q*);

/* Checks if the queue is empty. */
int int_empty(int_q*);

/* Returns the number of elements currently present on the queue. */
int int_length(int_q*);

/* Frees all resources from the queue. */
void int_free(int_q*);

/* Function:  fcfs
 * ---------------
 * (TODO)
 * 
 *  p:
 *  burst_time:
 * 
 *  return: 
 */
int fcfs(process p, int burst_time);

// void findWaitingTime(void);

#endif