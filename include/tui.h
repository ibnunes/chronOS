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
//    tui.h
//
// DESCRIPTION:
// -----------
// Text user interface.
//------------------------------------------------------------------------------


#ifndef TUI_H
#define TUI_H

void tui_write_error(const char*, ...);
void tui_write_warning(const char*, ...);
void tui_write_info(const char*, ...);
void tui_writeln_alert(const char*, ...);
void tui_writeb(const char*, ...);

void tui_output(char const*, char const*, ...);
void tui_write(char const*, ...);

void println(void);
void printlnn(unsigned);

#endif