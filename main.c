#include <stdlib.h>
#include <ncurses.h>

typedef struct Room
{
    // x and y point to the top left
    int xPosition;
    int yPosition;

    int height;
    int width;

    // Monster** monsters;
    // Item ** items;
} Room;

typedef struct Player
{
    int xPosition;
    int yPosition;
    int health;
    // Room* room;
} Player;

// function declarations

int screenSetup();
Room** mapSetup();
Player* playerSetup();
int handleInput(int input, Player* user);
int playerMove(int y, int x, Player* user);
int checkPosition(int newY, int newX, Player* user);

// room functions
Room* createRoom(int x, int y, int h, int w);
int drawRoom(Room* room);

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

    return rooms;
}

Room* createRoom(int x, int y, int h, int w)
{
    Room* newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->xPosition = x;
    newRoom->yPosition = y;
    newRoom->height = h;
    newRoom->width = w;

    return newRoom;
}

int drawRoom(Room* room)
{
    int x;
    int y;

    // draw top and bottom
    for (x = room->xPosition; x < room->xPosition + room->width; x++)
    {
        // mvprintw: moves the cursor then prints
        // args: y coord, x coord, string
        mvprintw(room->yPosition, x, "-");  // top
        mvprintw(room->yPosition + room->height - 1, x, "-");  // bottom
    }

    // draw the floors and side walls
    for (y = room->yPosition + 1; y < room->yPosition + room->height - 1; y++)
    {
        // draw side walls
        mvprintw(y, room->xPosition, "|");
        mvprintw(y, room->xPosition + room->width - 1, "|");

        // draw the floors
        for
        (
            x = room->xPosition + 1;
            x < room->xPosition + room->width - 1;
            x++
        )
        {
            mvprintw(y, x, ".");
        }
    }

    // returns 1 on success
    return 1;
}

Player* playerSetup()
{
    Player* newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    newPlayer->health = 20;

    playerMove(newPlayer->yPosition, newPlayer->xPosition, newPlayer);

    return newPlayer;
}

int handleInput(int input, Player* user)
{
    int newY;
    int newX;

    switch (input)
    {
        // move up
        case 'w':
        case 'W':
            newY = user->yPosition - 1;
            newX = user->xPosition;
            break;
        
        // move down
        case 's':
        case 'S':
            newY = user->yPosition + 1;
            newX = user->xPosition;
            break;

        // move left
        case 'a':
        case 'A':
            newY = user->yPosition;
            newX = user->xPosition - 1;
            break;
        
        // move right
        case 'd':
        case 'D':
            newY = user->yPosition;
            newX = user->xPosition + 1;
            break;

        default:
            break;
    }

    checkPosition(newY, newX, user);

    return 0;
}

int playerMove(int y, int x, Player* user)
{
    mvprintw(user->yPosition, user->xPosition, ".");

    user->xPosition = x;
    user->yPosition = y;

    mvprintw(user->yPosition, user->xPosition, "@");
    move(user->yPosition, user->xPosition);
}

int checkPosition(int newY, int newX, Player* user)
{
    int space;
    // mvinch returns the character in the position given
    switch (mvinch(newY, newX))
    {
        // if the next block is a free space, move
        case '.':
            playerMove(newY, newX, user);
            break;
        default:
            // move the cursor back, as the cursor would otherwise move to the
            // new position
            move(user->yPosition, user->xPosition);
            break;
    }
}