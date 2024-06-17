
build:
    gcc main.c -lncurses -o main

run:
    just build
    ./main