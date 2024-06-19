#include <stdlib.h>
#include <ncurses.h>

#include <time.h>   // Random numbers

typedef struct Position
{
    int x;
    int y;
    // TILE_TYPE tile;
} Position;

typedef struct Room
{
    // x and y point to the top left
    Position position;

    int height;
    int width;

    // Position doors[4];
    Position** doors;

    // Monster** monsters;
    // Item ** items;
} Room;

typedef struct Player
{
    Position position;
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

    return rooms;
}

Room* createRoom(int x, int y, int h, int w)
{
    Room* newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = h;
    newRoom->width = w;

    newRoom->doors = malloc(sizeof(Position)*4);

    // top door
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = rand() % (w - 2) + newRoom->position.x + 1;
    newRoom->doors[0]->y = newRoom->position.y;    // or newRoom->position.y

    // bottom door
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->x = rand() % (w - 2) + newRoom->position.x + 1;
    newRoom->doors[1]->y = newRoom->position.y + newRoom->height - 1;

    // left door
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->x = newRoom->position.x;
    newRoom->doors[2]->y = rand() % (h - 2) + newRoom->position.y + 1;

    // right door
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->x = newRoom->position.x + newRoom->width - 1;
    newRoom->doors[3]->y = rand() % (h - 2) + newRoom->position.y + 1;

    return newRoom;
}

int drawRoom(Room* room)
{
    int x;
    int y;

    // draw top and bottom
    for (x = room->position.x; x < room->position.x + room->width; x++)
    {
        // mvprintw: moves the cursor then prints
        // args: y coord, x coord, string
        mvprintw(room->position.y, x, "-");  // top
        mvprintw(room->position.y + room->height - 1, x, "-");  // bottom
    }

    // draw the floors and side walls
    for
    (
        y = room->position.y + 1;
        y < room->position.y + room->height - 1;
        y++
    )
    {
        // draw side walls
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");

        // draw the floors
        for
        (
            x = room->position.x + 1;
            x < room->position.x + room->width - 1;
            x++
        )
        {
            mvprintw(y, x, ".");
        }
    }

    // draw doors
    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");  // top
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");  // bottom
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");  // left
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");  // right

    // returns 1 on success
    return 1;
}

Player* playerSetup()
{
    Player* newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;

    playerMove(newPlayer->position.y, newPlayer->position.x, newPlayer);

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
            newY = user->position.y - 1;
            newX = user->position.x;
            break;
        
        // move down
        case 's':
        case 'S':
            newY = user->position.y + 1;
            newX = user->position.x;
            break;

        // move left
        case 'a':
        case 'A':
            newY = user->position.y;
            newX = user->position.x - 1;
            break;
        
        // move right
        case 'd':
        case 'D':
            newY = user->position.y;
            newX = user->position.x + 1;
            break;

        default:
            break;
    }

    checkPosition(newY, newX, user);

    return 0;
}

int playerMove(int y, int x, Player* user)
{
    mvprintw(user->position.y, user->position.x, ".");

    user->position.x = x;
    user->position.y = y;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x);
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
            move(user->position.y, user->position.x);
            break;
    }
}