#include"processor.h"

// main file for the processor


void processorFunction(instruction * instruction, process * p) //find better variable name
{
    if(instruction->ins == 'M')
        void changeValue(p, instruction->n);
    else if(instruction->ins == 'A')
        void addValue(p, instruction->n);
    else if(instruction->ins == 'S')
        void subtractValue(p, instruction->n);
    else if(instruction->ins == 'B')
        void blockProcess(p);
    else if(instruction->ins == 'T')
        void terminateProcess(p);
    else if(instruction->ins == 'C')
        process createNewProcess(p, instruction->n);
    else if(instruction->ins == 'L')
        void cleanProgram(instruction->nome);
    return;
}