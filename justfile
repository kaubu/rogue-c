## Variables
# C compiler
CC := "gcc"
SRCDIR := "./src/"
IDIR := "./include/"
SOURCES := SRCDIR + "*.c"
CFLAGS := "-lncurses -I" + IDIR
OUTPUT := "./rogue"

## Targets
# build then run
br: build run

# build man
build:
    {{CC}} {{SOURCES}} {{CFLAGS}} -o {{OUTPUT}}

# run executable
run:
    {{OUTPUT}}
