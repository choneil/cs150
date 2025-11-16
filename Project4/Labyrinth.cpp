#include "Labyrinth.h"
#include <iostream>
#include <string>
bool isPathToFreedom(MazeCell* start, const std::string& moves) {
    //can escape if the path is legal: no prohibited steps, picks up the spellbook, wand, and potion
    //assume you begin in a valid cell
   
    MazeCell* currPos = start;
    char moveDir;
    int inventory_sz = 3;
    Item* inventory = new Item[inventory_sz];
    
    for (int i = 0; i < inventory_sz; i++){
        inventory[i] = Item::NOTHING;
    }

    int j = 0;
    addToInventory(inventory, inventory_sz, currPos);
    while (moves[j]) {
        
        moveDir = moves[j];
        currPos = moveTo(currPos, moveDir);
        addToInventory(inventory, inventory_sz, currPos);
        j++;
    }
    int check = checkInventory(inventory, inventory_sz);
    if (check == 1)
        return true;
    return false;
}

MazeCell* moveTo(MazeCell* curr, char direction) {
    MazeCell* nextDir = nullptr;
    
    switch(direction){
    case 'N':
        nextDir = curr->north;
        break;
    case 'S':
        nextDir = curr->south;
        break;
    case 'E':
        nextDir = curr->east;
        break;
    case 'W':
        nextDir = curr->west;
        break;
    }
    if (nextDir != nullptr) {
        return nextDir;
    }
}

void addToInventory(Item* inv, int sz, MazeCell* curr) {
    if (curr->whatsHere == Item::NOTHING)
        return;
    Item* currinv = inv;

    while (*currinv != Item::NOTHING) {
        currinv = currinv + 1;
    }
    *currinv = curr->whatsHere;
    return;
}

int checkInventory(Item* inv, int sz) {
    int i = 0;
    int checkAll = 1;
    Item* currItem = inv;
    while (i < sz) {
        currItem = currItem + i;
        if (*currItem == Item::NOTHING) {
            checkAll = 0;
        }
        return checkAll;
    }
}

void mapCurr(MazeCell* curr, MapMazeCell* caller) {
    if (curr->aqui) {
        return;
    }
    MapMazeCell* mapCell = curr->aqui;
    if (curr != nullptr) {
        if (curr->whatsHere == Item::SPELLBOOK) {
            std::cout << "Curr: " << curr << std::endl << "Item: " << "spellbook" << std::endl;
        }
        if (curr->whatsHere == Item::WAND) {
            std::cout << "Curr: " << curr << std::endl << "Item: " << "wand" << std::endl;
        }
        if (curr->whatsHere == Item::POTION) {
            std::cout << "Curr: " << curr << std::endl << "Item: " << "potion" << std::endl;
        }
    }
    std::cout << "Caller: " << caller << std::endl<<"Curr: " << curr << std::endl << "North: " << curr->north << std::endl << "East: " << curr->east << std::endl << "South: " << curr->south << std::endl << "West: " << curr->west << std::endl;
    std::cout << std::endl << "Aqui: " << curr->aqui << std::endl;

    if (caller != nullptr) {

       

        if (mapCell == nullptr) {
            mapCell = new MapMazeCell;
            curr->aqui = mapCell;
        }

        //check for nulls in maze space
        if (curr->north == nullptr) {
            mapCell->mnorth = nullptr;
        }
        if (curr->south == nullptr) {
            mapCell->msouth = nullptr;
        }
        if (curr->east == nullptr) {
            mapCell->meast = nullptr;
        }
        if (curr->west == nullptr) {
            mapCell->mwest = nullptr;
        }

        //check for caller
        if (curr->north) {

            if(curr->north->aqui == caller) {
                curr->north->aqui->msouth = mapCell;
                curr->aqui->mnorth = caller;
            }
        }
        if (curr->east)
        {
            if (curr->east->aqui == caller) {
                curr->east->aqui->mwest = mapCell;
                curr->aqui->meast = caller;
            }
        }
        if (curr->south)
        {

            if (curr->south->aqui == caller) {
                curr->south->aqui->mnorth = mapCell;
                curr->aqui->msouth = caller;
            }
        }
        if (curr->west)
        {

            if (curr->west->aqui == caller) {
                curr->west->aqui->meast = mapCell;
                curr->aqui->meast = caller;
            }
        }

        //recurse
        if (curr->north != nullptr && curr->aqui->mnorth != caller) {
            mapCurr(curr->north, mapCell);
        }
        if (curr->east != nullptr && curr->aqui->meast != caller) {
            mapCurr(curr->east, mapCell);
        }
        if (curr->south != nullptr && curr->aqui->msouth != caller) {
            mapCurr(curr->south, mapCell);
        }
        if (curr->west != nullptr && curr->aqui->mwest != caller) {
            mapCurr(curr->west, mapCell);
        }
    }
    else {

        if (mapCell == nullptr) {
            
            mapCell = new MapMazeCell;
            curr->aqui = mapCell;
        }

        if (curr->north == nullptr) {
            mapCell->mnorth = nullptr;
        }
        if (curr->south == nullptr) {
            mapCell->msouth = nullptr;
        }
        if (curr->east == nullptr) {
            mapCell->meast = nullptr;
        }
        if (curr->west == nullptr) {
            mapCell->mwest = nullptr;
        }

        //recurse
        if (curr->north != nullptr && curr->aqui->mnorth != caller) {
            mapCurr(curr->north, mapCell);
        }
        if (curr->east != nullptr && curr->aqui->meast != caller) {
            mapCurr(curr->east, mapCell);
        }
        if (curr->south != nullptr && curr->aqui->msouth != caller) {
            mapCurr(curr->south, mapCell);
        }
        if (curr->west != nullptr && curr->aqui->mwest != caller) {
            mapCurr(curr->west, mapCell);
        }

    }
}

//int moveCount = 0;
//int turns = 0;
//void traverseMaze(MazeCell* start, int moveCount) {
//    MazeCell* curr = start;
//    int inventory_sz = 3;
//    Item* inventory = new Item[inventory_sz];
//    for (int i = 0; i < inventory_sz; i++) {
//        inventory[i] = Item::NOTHING;
//    }
//    int found = checkInventory(inventory, 3);
//    addToInventory(inventory, 3, curr);
//    for (int i = 0; i < 100; i++) {
//        std::cout << turns[i];
//    }
//    std::cout << std::endl;
//    if (found == 1)
//        return;
//
//    if (curr->north != nullptr)
//    {   
//        
//        turns[moveCount] = 'N';
//        moveCount++;
//        traverseMaze(start->north);
//
//    }
//
//    if (curr->east != nullptr)
//    {
//        turns[moveCount] = 'E';
//        moveCount++;
//        traverseMaze(start->east);
//    }
//
//    if (curr->west != nullptr)
//    {
//        turns[moveCount] = 'W';
//        moveCount++;
//        traverseMaze(start->west);
//
//    }
//
//    if (curr->south != nullptr)
//    {
//        turns[moveCount] = 'S';
//        moveCount++;
//        traverseMaze(start->south);
//    }
//    
//    
//}