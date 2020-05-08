#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#include "memmgr.h"
#include "pcbmgr.h"
#include "processor.h"

/* Strings úteis ao programa */
const char *PROG_EXTENSION = ".prg";
const char *FILE_PLAN      = "plan.txt";
const char *FILE_CONTROL   = "control.txt";


#endif