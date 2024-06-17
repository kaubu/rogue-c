#include <ncurses.h>

int screenSetup();

int main()
{
    screenSetup();

    // wait for user input
    // get char
    getch();

    // ends ncurses
    endwin();

    return 0;
}

int screenSetup()
{
    // starts up ncurses
    initscr();
    // ncurses print function
    printw("Hello World!");
    // stops users from seeing what they type
    noecho();
    refresh();

    return 0;
}