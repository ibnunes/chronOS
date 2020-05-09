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
    p->counter += 1;
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
            break;

        case 'C':
            // TODO: a adicionar ao gestor de processos
            createNewProcess(p, i->n);
            break;

        case 'L':
            // ???
            cleanProgram(i->name);
            break;

        default:
            fprintf(stderr, "ERROR: Unknown instruction \"%c\". ABORTING!\n", i->ins);
            exit(-1);
            break;
    }
}