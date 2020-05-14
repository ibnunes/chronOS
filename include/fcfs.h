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

/* Function: int_new
 * -----------------
 * Allocates heap memory to a new queue for ints. 
 * 
 *  nmemb: number of new elements in the queue.
 * 
 *  returns: pointer to a queue.
 */
int_q *int_new(size_t nmemb);

/* Funtion: int_push
 * ----------------- 
 * Inserts a new int element to the queue. 
 * 
 *  q: queue.
 *  n: new element.
 * 
 *  returns: nothing.
 */
void int_push(int_q *q, int n);

/* Function: int_peek
 * ------------------
 * Peeks the head of the queue without popping it. 
 * 
 *  q: queue.
 *  
 *  returns: int value of the head of the queue.
 */
int int_peek(int_q *q);

/* Function: int_pop
 * ------------------
 * Pops the head element of the queue.
 * 
 *  q: queue.
 *  
 *  returns: int value of the head of the queue.
 */
int int_pop(int_q *q);

/* Function: int_empty
 * -------------------
 * Checks if the queue is empty.
 * 
 *  q: queue.
 * 
 *  returns: (int) bool.
 */
int int_empty(int_q *q);

/* Function: int_length
 * --------------------
 * Returns the number of elements currently present on the queue.
 * 
 *  q: queue.
 * 
 *  returns: length of the queue.
 */
int int_length(int_q *q);

/* Function: int_free
 * ------------------
 * Frees all resources from the queue.
 * 
 *  q: queue.
 * 
 *  returns: nothing.
 */
void int_free(int_q *q);

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