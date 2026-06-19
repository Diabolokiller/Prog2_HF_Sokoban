/**
 * \file menu.h
 *
 * A Menu osztaly es tagfuggvenyeinek deklaralasa, a getterek definialasa
 *
 * Ez az osztaly tarolja el a betoltott palyakat es lehetove teszi
 * a palyak kozotti valtasokat
 *
 */
#ifndef MENU_H
#define MENU_H

#include "level.h"
#include <fstream>
#include <cstdio>
#ifndef CPORTA
#include <filesystem>
#endif // CPORTA
#include "memtrace.h"



class Menu{
    int levelCount;
    int currentLevel;
    Level** levels;
public:
    Menu(const char* dir = ".");
    Level* getCurrentLevel();
    /**
     * \return Visszaadja a jelelneg aktualis palya sorszamat
     */
    int getCurrentLevelInt() { return currentLevel; }
    /**
     * \return Visszaadja a tarolt palyak szamat
     */
    int getLevelCount() { return levelCount; }
    bool loadLevel(const char*);
    void goToLevel(int);
    ~Menu();
};

#endif // MENU_H
