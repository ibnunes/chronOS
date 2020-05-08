#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_NAME 15

// Lista de extensões válidas ???
// const char *FNAME_EXTENSION = ".prg";

typedef struct {
    char ins;
    int  n;
    char name[MAX_NAME]
} instruction;
