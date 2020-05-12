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
//    simulator.h
//
// DESCRIPTION:
// -----------
// Simulation management.
// The main header file that aggregates everything.
//------------------------------------------------------------------------------


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
#include "plan.h"
// #include "data.h"
// #include "types.h"

/* Strings úteis ao programa */
const char *PROG_EXTENSION = ".prg";        // Extensão de um programa que corre no simulador
const char *FILE_PLAN      = "plan.txt";    // Ficheiro com o plano de execução
const char *FILE_CONTROL   = "control.txt"; // Ficheiro com os comandos de controlo

#define DEFAULT_TIME_QUANTUM 0.500F         // 500 milissegundos


#endif