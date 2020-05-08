#include"processor.h"

// main file for the processor


void processorFunction(instruction * instruction, process * p) //find better variable name
{
    if(instruction->ins == 'M')
        changeValue(p, instruction->n);
    else if(instruction->ins == 'A')
        addValue(p, instruction->n);
    else if(instruction->ins == 'S')
        subtractValue(p, instruction->n);
    else if(instruction->ins == 'B')
        blockProcess(p);
    else if(instruction->ins == 'T')
        terminateProcess(p);
    else if(instruction->ins == 'C')
        process new_p = createNewProcess(p, instruction->n); // what to do with new_p?
    else if(instruction->ins == 'L')
        cleanProgram(instruction->nome);
    return;
}