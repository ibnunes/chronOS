#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

typedef struct{
    char ins;
    int n;
    char nome[15]
}instruction;

typedef struct{
    int id;         // identificador do processo
    int context;      //estado do processo
    int counter;    // contador do programa
    int pid;        //identificador do processo progenitor
    int priority;   //prioridade do processo
    int time_limit; //prazo temporal do processo
    char state;      //estado bloquado, terminado, ready, etc.
    // add whatever else is needed
} process;

// 5 states:
// 'N' -> New
// 'r' -> Ready
// 'R' -> Running
// 'B' -> Blocked
// 'T' -> Terminated