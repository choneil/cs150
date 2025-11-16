#pragma once
#include <string>
#include "Labyrinth.h"



struct MapMazeCells {
    Item whatsHere; // Which item, if any, is present.

    MazeCell* north;
    MazeCell* south;
    MazeCell* east;
    MazeCell* west;
    int posX;
    int posY;
};



/**
 * Given a location in a maze, returns whether the given sequence of
 * steps will let you escape the maze.
 *
 * To escape the maze, you need to find the Potion, the Spellbook, and
 * the Wand. You can only take steps in the four cardinal directions,
 * and you can't move in directions that don't exist in the maze.
 */
//bool isPathToFreedom(MazeCell* start, const std::string& moves);
//MazeCell* moveTo(MazeCell* curr, char direction);
//void addToInventory(Item* inv, int sz, MazeCell* curr);
//int checkInventory(Item* inv, int sz);

