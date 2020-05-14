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

void run(MEMORY *mem, process *p) {
    instruction *i = &(mem->cells[p->counter]);

    switch (i->ins) {
        case INSTRUCTION_CHANGE:
            changeValue(p, i->n);
            break;

        case INSTRUCTION_ADD:
            addValue(p, i->n);
            break;

        case INSTRUCTION_SUBTRACT:
            subtractValue(p, i->n);
            break;

        case INSTRUCTION_BLOCK:
            blockProcess(p);
            break;

        case INSTRUCTION_TERMINATE:
            terminateProcess(p);
            return;

        case INSTRUCTION_FORK:
            forkProcess(mem, p);
            p->counter += i->n; // jump n instructions
            return;

        case INSTRUCTION_CLEAR:
            cleanProgram(mem, p, i->name);
            return;

        default:
            fprintf(stderr, "ERROR: Unknown instruction \"%c\". ABORTING!\n", i->ins);
            exit(-1);
            break;
    }

    p->counter += 1;
}

int switchState(int oldstate, int newstate) {
    switch (oldstate) {
        case STATUS_NEW:
            return (newstate == STATUS_READY) ? newstate : oldstate;

        case STATUS_READY:
            return (newstate == STATUS_RUNNING) ? newstate : oldstate;

        case STATUS_RUNNING:
            return (
                    newstate == STATUS_TERMINATED ||
                    newstate == STATUS_BLOCKED ||
                    newstate == STATUS_READY
                ) ? newstate : oldstate;

        case STATUS_BLOCKED:
            return (newstate == STATUS_READY) ? newstate : oldstate;

        case STATUS_TERMINATED:
        default:
            return oldstate;
    }
}
