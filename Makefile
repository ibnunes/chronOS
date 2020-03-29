CC := gcc

CFLAGS := -std=c99
CFLAGS += -Wpedantic -pedantic-errors
CFLAGS += -Wall -Wextra
CFLAGS += -Werror=main
CFLAGS += -Werror=write-strings
CFLAGS += -Werror=strict-prototypes
CFLAGS += -Werror=missing-prototypes
CFLAGS += -Werror=missing-declarations
CFLAGS += -Werror=implicit-int -Werror=implicit-function-declaration
CFLAGS += -Werror=format-security
ifneq ($(OS), 'Windows_NT')
    CFLAGS += -D_POSIX_C_SOURCE
endif

LIBS :=
LDFLAGS :=
SANITIZERFLAGS := -fsanitize=address -fsanitize=undefined

SRCDIR := src
OBJDIR := obj
BINDIR := bin
INCDIR := include
DEPDIR := deps

TARGET := app

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

debug: CFLAGS += -Og -g3 -fno-omit-frame-pointer $(SANITIZERFLAGS)
debug: LDFLAGS += $(SANITIZERFLAGS)
debug: $(BINDIR)/$(TARGET)

release: CFLAGS += -O3 -g0 -DNDEBUG
release: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS) | $(BINDIR)
	@$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	@$(CC) -I$(INCDIR) -c $(CFLAGS) -o $@ \
	    -MT $@ -MMD -MP \
	    -MF $(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $@) \
	    $<

$(BINDIR) $(OBJDIR) $(DEPDIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJDIR) $(DEPDIR) $(BINDIR)/$(TARGET)

.PHONY: debug release clean

-include $(patsubst $(SRCDIR)/%.c, $(DEPDIR)/%.d, $(SOURCES))
