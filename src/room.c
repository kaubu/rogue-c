#include "rogue.h"

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

    // left door
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->x = newRoom->position.x;
    newRoom->doors[1]->y = rand() % (h - 2) + newRoom->position.y + 1;

    // bottom door
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->x = rand() % (w - 2) + newRoom->position.x + 1;
    newRoom->doors[2]->y = newRoom->position.y + newRoom->height - 1;

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

int connectDoors(Position* doorOne, Position* doorTwo)
{
    Position temp;
    Position previous;

    int count = 0;

    temp.x = doorOne->x;
    temp.y = doorOne->y;

    previous = temp;

    while (1)   // always be true and looping
    {
        // move in a random direction
        // ask if it moves closer to the destination
        // if so, ask it if the space is empty

        // step left
        if
        (
            abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)
            && (mvinch(temp.y, temp.x - 1) == ' ')
        )
        {
            // mvprintw(temp.y, temp.x - 1, "#");
            previous.x = temp.x;
            temp.x -= 1;
        }
        else if // step right
        (
            abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)
            && (mvinch(temp.y, temp.x + 1) == ' ')
        )
        {
            // mvprintw(temp.y, temp.x + 1, "#");
            previous.x = temp.x;
            temp.x += 1;
        }
        else if // step down
        (
            abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)
            && (mvinch(temp.y + 1, temp.x) == ' ')
        )
        {
            // mvprintw(temp.y + 1, temp.x, "#");
            previous.y = temp.y;
            temp.y += 1;
        }
        else if // step up
        (
            abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)
            && (mvinch(temp.y - 1, temp.x) == ' ')
        )
        {
            // mvprintw(temp.y - 1, temp.x, "#");
            previous.y = temp.y;
            temp.y -= 1;
        }
        else // if we get stuck
        {
            if (count == 0)
            {
                temp = previous;
                count++;
                continue;
            }

            return 0;
        }

        mvprintw(temp.y, temp.x, "#");

        // getch();    // go step by step through the linking process
    }

    return 1;   // on success
}
