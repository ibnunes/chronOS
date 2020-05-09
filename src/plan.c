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

void plan_push(plan_q *p, /* PLAN n */ char *str, cpu_t t) {
    if (p->last >= p->capacity) {
        p->capacity *= 2;
        p->list = realloc(p->list, p->capacity * sizeof(p->list));
    }
    /* p->list[p->last] = n; */
    p->list[p->last].time = t;
    strcpy(p->list[p->last].program, str);
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
    cpu_t time;
    int read;
    while (!feof(f)) {
        if ((read = fscanf(f, "%s %llu", prgm, &time)) == 2) {
            debug("Pushing (%s, %llu) to plan queue...\n", prgm, time);
            plan_push(plan, prgm, time);
        } else {
            fprintf(stderr, "ERROR: only %d out of 2 items were corretly read (%s).\n", read, fname);
        }
        //fgets(prgm, 50, f);
        //printf("Got: \"%s\"\n", prgm);
    }
    fclose(f);
    return plan;
}
