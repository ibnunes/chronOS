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