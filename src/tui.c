#include "tui.h"
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>


/* === Principal método, sensível ao OS === */
void tui_output(char const* message, char const* fallback, ...) {
    va_list args;
    va_start(args, fallback);
#ifdef _POSIX_C_SOURCE
    if (isatty(fileno(stdout)))
        vfprintf(stdout, message, args);
    else
#endif
    vfprintf(stdout, fallback, args);
    va_end(args);
}


/* Métodos para apresentar mensagens de diferentes categorias */
// Erro (vermelho vivo)
void tui_write_error(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    tui_output("\x1b[91%s\x1b[0m", "%s", fmt, args);
    va_end(args);
}

// Aviso (amarelo vivo)
void tui_write_warning(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    tui_output("\x1b[93m%s\x1b[0m", "%s", fmt, args);
    va_end(args);
}

// Informação (ciano)
void tui_write_info(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    tui_output("\x1b[36m%s\x1b[0m", "%s", fmt, args);
    va_end(args);
}

/* Alerta (fundo vermelho) - faz parágrafo final */
void tui_writeln_alert(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    tui_output("\x1b[97;101m %s \x1b[0m\n", " %s ", fmt, args);
    va_end(args);
}

// Branco
void tui_writeb(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    tui_output("\x1b[97m%s\x1b[0m", "%s", fmt, args);
    va_end(args);
}

// Normal
void tui_write(char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    tui_output(fmt, fmt, args);
    va_end(args);
}


/* Coloca parágrafos no stdout. */
void println(void) {
    printf("\n");
}

void printlnn(unsigned n) {
    for (; n > 0; n--)
        println();
}