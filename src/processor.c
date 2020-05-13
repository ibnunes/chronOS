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
//    processor.h
//
// DESCRIPTION:
// -----------
// Process management.
//------------------------------------------------------------------------------


#include "processor.h"

// main file for the processor


void processorFunction(instruction *i, process *p) {
    p->state = STATUS_RUNNING;

    switch (i->ins) {
        case 'M':
            changeValue(p, i->n);
            break;

        case 'A':
            addValue(p, i->n);
            break;

        case 'S':
            subtractValue(p, i->n);
            break;

        case 'B':
            blockProcess(p);
            break;

        case 'T':
            terminateProcess(p);
            return;

        case 'C':
            createNewProcess(p);
            p->counter += i->n; // jump n instructions
            return;

        case 'L':
            cleanProgram(p, i->name);
            break;

        default:
            fprintf(stderr, "ERROR: Unknown instruction \"%c\". ABORTING!\n", i->ins);
            exit(-1);
            break;
    }
    p->counter += 1;
    p->state = STATUS_READY;
}

int switchState(int oldstate, int newstate) {
    switch (oldstate) {
        case STATUS_NEW:
            return (newstate == STATUS_READY) ? newstate : oldstate);
        case STATUS_READY:
            return ((newstate == STATUS_RUNNING) ? newstate : oldstate);
        case STATUS_RUNNING:
            return ((newstate == STATUS_TERMINATED || newstate == STATUS_BLOCKED || newstate == STATUS_READY) ? newstate : oldstate);
        case STATUS_BLOCKED:
            return ((newstate == STATUS_READY) ? newstate : oldstate);
        case STATUS_TERMINATED:
        default:
            return oldstate;
    }
}
