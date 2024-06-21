#include "rogue.h"

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

int checkPosition(int newY, int newX, Player* user)
{
    int space;
    // mvinch returns the character in the position given
    switch (mvinch(newY, newX))
    {
        // if the next block is a free space, move
        case '.':
        case '+':
        case '#':
            playerMove(newY, newX, user);
            break;
        default:
            // move the cursor back, as the cursor would otherwise move to the
            // new position
            move(user->position.y, user->position.x);
            break;
    }
}

int playerMove(int y, int x, Player* user)
{
    mvprintw(user->position.y, user->position.x, ".");

    user->position.x = x;
    user->position.y = y;

    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x);
}
