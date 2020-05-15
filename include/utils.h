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

#ifndef UTILS_H
#define UTILS_H

/* Function:  strendswith
 * ----------------------
 * Checks if a string ends with a given substring.
 * 
 *  str: the string to check.
 *  suffix: the string to search for.
 * 
 *  return: 1 if str ends with suffix, 0 otherwise.
 * 
 * Based on: https://stackoverflow.com/a/744822
 */
int strendswith(const char *str, const char *suffix);

/* Function:  strendswith
 * ----------------------
 * Checks if a string ends with PROG_EXTENSION.
 * 
 *  str: the string to check.
 * 
 *  return: 1 if str ends with PROG_EXTENSION, 0 otherwise.
 * 
 * Based on: https://stackoverflow.com/a/744822
 */
int strendswithprg(const char *str);

#endif