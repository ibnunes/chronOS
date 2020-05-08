#include "simulator.h"

void changeValue (process * p, int n);

void addValue(process * p, int n);

void subtractValue(process * p, int n);

void blockProcess(process * p);

void terminateProcess(process * p);

process *createNewProcess(process * p, int n);

void cleanProgram(char * filename);
