#ifndef ROGUE_H
#define ROGUE_H

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
int connectDoors(Position* doorOne, Position* doorTwo);

#endif