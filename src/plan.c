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


#include "plan.h"
#include "debug.h"
#include "tui.h"
#include <string.h>


plan_q *plan_new(size_t nmemb) {
    expects(nmemb > 0);
    plan_q *p = malloc(sizeof(*p));
    p->list = malloc(nmemb * sizeof(*p->list));
    p->head = p->last = 0;
    p->capacity = nmemb;
    return p;
}

void plan_push(plan_q *p, char *str, clock_t t, int prior) {
    if (p->last >= p->capacity) {
        p->capacity *= 2;
        p->list = realloc(p->list, p->capacity * sizeof(*p->list));
    }
    p->list[p->last].time = t;
    strcpy(p->list[p->last].program, str);
    p->list[p->last].priority = prior;
    p->last++;
}

PLAN plan_peek(plan_q *p) {
    return p->list[p->head];
}

PLAN plan_pop(plan_q *p) {
    return p->list[(p->head)++];
}

int plan_empty(plan_q *p) {
    return (p->head == p->last);
}

int plan_length(plan_q *p) {
    return (p->last - p->head);
}

void plan_free(plan_q *p) {
    free(p->list);
    free(p);
}


plan_q *plan_read_from_file(const char *fname) {
    plan_q *plan = plan_new(DEFAULT_PLAN_Q_SIZE);
    FILE *f = fopen(fname, "r");
    expects(f != NULL);
    char prgm[MAX_PROGRAM];
    clock_t time;
    int prior;
    int read;
    while (!feof(f)) {
        if ((read = fscanf(f, "%s %ld %d", prgm, &time, &prior)) == 3) {
            debug("Pushing (%s, %ld, %d) to plan queue...\n", prgm, time, prior);
            plan_push(plan, prgm, time, prior);
        } else if (read == 2) {
            debug("Pushing (%s, %ld, 3) to plan queue...\n", prgm, time);
            plan_push(plan, prgm, time, PRIORITY_NORMAL);
        } else {
            fprintf(stderr, "ERROR: only %d out of 2 items were corretly read (%s).\n", read, fname);
        }
    }
    fclose(f);
    return plan;
}
