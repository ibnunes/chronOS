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
//    debug.h
//
// DESCRIPTION:
// -----------
// Debugging macros only available with 'make debug'.
//------------------------------------------------------------------------------

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>

#ifndef NDEBUG

#define debug(...)                                                      \
   do {                                                                 \
      fprintf(stderr, "%s:%d: %s(): ", __FILE__, __LINE__, __func__);   \
      fprintf(stderr, __VA_ARGS__);                                     \
   } while(0)

#define expects(X)                        \
   do {                                   \
      if (!(X)) {                         \
         debug("Expected '%s'.\n", #X);   \
         exit(1);                         \
      }                                   \
   } while(0)

#define ensures(X) expects(X)

#else

#define debug(...) 
#define expects(...)
#define ensures(...)

#endif  // NDEBUG

#endif  // INCLUDE_DEBUG_H