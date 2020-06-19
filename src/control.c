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
//    control.h
//
// DESCRIPTION:
// -----------
// Control management.
//------------------------------------------------------------------------------


#include "simulator.h"
#include "tui.h"
#include <string.h>

control_q *control_new(size_t nmemb) {
    expects(nmemb > 0);
    control_q *c = malloc(sizeof(*c));
    c->operation = malloc(nmemb * sizeof(*c->operation));
    c->head = c->last = 0;
    c->capacity = nmemb;
    return c;
}

void control_push(control_q *c, char oper) {
    if (c->last >= c->capacity) {
        c->capacity *= 2;
        c->operation = realloc(c->operation, c->capacity * sizeof(*c->operation));
    }
    c->operation[c->last] = oper;
    c->last++;
}

char control_peek(control_q *c) {
    return c->operation[c->head];
}

char control_pop(control_q *c) {
    return c->operation[(c->head)++];
}

int control_empty(control_q *c) {
    return (c->head == c->last);
}

int control_length(control_q *c) {
    return (c->last - c->head);
}

void control_free(control_q *c) {
    free(c->operation);
    free(c);
}

control_q *control_read_from_file(const char *fname) {
    FILE *f = fopen(fname, "r");
    if (f == NULL) return NULL;
    
    control_q *control = control_new(DEFAULT_CONTROL_Q_SIZE);
    char oper;
    int read;
    while(!feof(f)) {
        if ((read = fscanf(f, " %c", &oper)) == 1) {
            debug("Pushing %c to control queue...\n", oper);
            control_push(control, oper);
        } else {
            fprintf(stderr, "ERROR: got %d item when only 1 was expected (%s).\n", read, fname);
        }
    }
    
    fclose(f);
    return control;
}


int execcontrol(char operation, PCB *pcb, int pcbindex) {
    switch (operation) {
        case CONTROL_EXECUTE:
            w.control.quantum_curr++;
            if (w.control.quantum_curr > w.control.quantum_limit) {
                w.control.quantum_curr = 0;
            } else {
                return 0;
            }
            break;
        
        case CONTROL_BLOCK:
            schedblock(pcb, pcbindex);
            break;

        case CONTROL_LTSCHED:
            ltsched(pcb);
            break;

        case CONTROL_REPORT:
            pcbreport(pcb);
            break;

        case CONTROL_QUIT:
            w.flag.__running = 0;
            break;

        default:
            fprintf(stderr, "ERROR: Unknown control instruction. ABORTING!\n");
            exit(EXIT_FAILURE);
    }

    return 1;
}

char control_scan(void) {
    char oper;
    while (1) {
        fprintf(stdout, "Control? ");
        oper = getchar();
        int read = fscanf(stdin, " %c", &oper);

        if (read != 1) {
            fprintf(stderr, "ERROR: Didn't get a valid operation. Trying again.\n");
            continue;
        }

        switch (oper) {
            case 'e':
            case 'E': return CONTROL_EXECUTE;
            case 'i':
            case 'I': return CONTROL_BLOCK;
            case 'd':
            case 'D': return CONTROL_LTSCHED;
            case 'r':
            case 'R': return CONTROL_REPORT;
            case 't':
            case 'T': return CONTROL_QUIT;
            default:
                fprintf(stderr, "ERROR: Unknown control instruction. ABORTING!\n");
                break;
        }
    }
}
