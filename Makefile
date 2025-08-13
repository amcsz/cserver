INCLDIRS = -I./include
SRC = $(wildcard src/*.c) 
OBJDIR = obj
OBJS = $(patsubst src/%,$(OBJDIR)/%,$(SRC:.c=.o))
EXEC = server

CFLAGS ?= -O2 -Wall -Wextra
CC := gcc 

all: dirs $(EXEC) 

$(EXEC): $(OBJS)
	$(CC) -o $@ $^

dirs:
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(EXEC)

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLDIRS) -c -o $@ $<
