#include"simulator.h"

typedef struct{
    int id;         // identificador do processo
    int state;      //estado do processo
    int counter;    // contador do programa
    int pid;        //identificador do processo progenitor
    int priority;   //prioridade do processo
    int time_limit; //prazo temporal do processo
    // add whatever else is needed
} process;