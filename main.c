#include <stdlib.h>
#include <ncurses.h>

typedef struct Player
{
    int xPosition;
    int yPosition;
    int health;
} Player;

// function declarations

int screenSetup();
int mapSetup();
Player* playerSetup();
int handleInput(int input, Player* user);

// main function

int main()
{
    Player* user;
    int ch;
    screenSetup();

    // set up the map
    mapSetup();

    user = playerSetup();

    // gain loop
    while ((ch = getch()) != 'q')
    {
        handleInput(ch, user);
    }

    // ends ncurses
    endwin();

    return 0;
}

// function definitions

int screenSetup()
{
    // starts up ncurses
    initscr();
    // ncurses print function
    printw("Hello World!");
    // stops users from seeing what they type
    noecho();
    refresh();

    // tutorial dude says that 1 is good, 0 is error
    return 1;
}

int mapSetup()
{
    // moves the cursor then prints
    // args: y coord, x coord, string
    mvprintw(13, 13, "--------");
    mvprintw(14, 13, "|......|");
    mvprintw(15, 13, "|......|");
    mvprintw(16, 13, "|......|");
    mvprintw(17, 13, "|......|");
    mvprintw(18, 13, "--------");

    mvprintw(2, 40, "--------");
    mvprintw(3, 40, "|......|");
    mvprintw(4, 40, "|......|");
    mvprintw(5, 40, "|......|");
    mvprintw(6, 40, "|......|");
    mvprintw(7, 40, "--------");

    mvprintw(10, 40, "------------");
    mvprintw(11, 40, "|..........|");
    mvprintw(12, 40, "|..........|");
    mvprintw(13, 40, "|..........|");
    mvprintw(14, 40, "|..........|");
    mvprintw(15, 40, "------------");

    return 0;
}

Player* playerSetup()
{
    Player* newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->yPosition, newPlayer->xPosition, "@");
    move(newPlayer->yPosition, newPlayer->xPosition);

    return newPlayer;
}

int handleInput(int input, Player* user)
{
    switch (input)
    {
        // move up
        case 'w':
        case 'W':
            break;
        
        // move down
        case 's':
        case 'S':
            break;

        // move left
        case 'a':
        case 'A':
            break;
        
        // move right
        case 'd':
        case 'D':
            break;
    }

    return 0;
}