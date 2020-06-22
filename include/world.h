#ifndef WORLD_H
#define WORLD_H

#include "types.h"
#include <limits.h>

#define APP_NAME    "chronOS"
#define APP_VERSION "1.3.1"

void halt(int e, char const *msg);

void startworld(struct world *world);
void loadargs(struct world *world, int argc, char const *argv[]);

#endif