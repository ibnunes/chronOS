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
//    utils.h
//
// DESCRIPTION:
// -----------
// Miscellaneous utilities.
//------------------------------------------------------------------------------

#include "utils.h"
#include "types.h"
#include <string.h>

int strendswith(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr    = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int strendswithprg(const char *str) {
    return strendswith(str, PROG_EXTENSION);
}