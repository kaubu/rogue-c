#include "rogue.h"

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

    // seeds the random number generator with the current time
    srand(time(NULL));

    // tutorial dude says that 1 is good, 0 is error
    return 1;
}

Room** mapSetup()
{
    Room** rooms;
    rooms = malloc(sizeof(Room) * 6);

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    rooms[1] = createRoom(40, 2, 6, 8);
    drawRoom(rooms[1]);

    rooms[2] = createRoom(40, 10, 6, 12);
    drawRoom(rooms[2]);

    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
    connectDoors(rooms[1]->doors[2], rooms[0]->doors[0]);

    return rooms;
}
