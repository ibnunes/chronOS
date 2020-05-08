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