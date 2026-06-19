/**
 * \file level.h
 *
 * A Level es UndoGrid osztaly es tagfuggvenyeinek deklaralasa, a getterek definialasa
 * A fajl beolvasashoz hasznalt fuggvenyek definialasa
 *
 * A Level osztaly valositja meg a jatek menetet, itt van eltarolva a palya helyzete
 * es a jatekhoz hasznalt fuggvenyek lenyeges resze
 *
 * Az UndoGrid osztaly a lepesek visszavonasat teszi lehetove az elozo poziciok eltarolasaval
 *
 */
#ifndef LEVEL_H
#define LEVEL_H

#include "entity.h"
#include "tile.h"
#include "coordinate.h"
#include <iostream>
#include <fstream>

#ifndef CPORTA

#include "graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#endif

#include "memtrace.h"

Coordinate getFileSize(const char*);
char** fileToCharMatrix(const char*, Coordinate);

struct UndoGrid{
    Coordinate playerPosition;
    Entity*** entityGrid;
};

class Level {
    Tile*** tileGrid;
    Coordinate playerPosition;
    Entity*** entityGrid;
    const Coordinate siz;
    UndoGrid* undoGrid;
    int moveCount;
    int savedMoves;
    int prevMoveIndex;
public:
    Level(const Coordinate, char**);
    bool isComplete() const;
    /**
     * \return Palya merete
     */
    const Coordinate getSize() const { return siz; }
    /**
     * \return A jatekos jelenlegi pozicioja
     */
    Coordinate getPlayerPos() const {return playerPosition; };
    bool movePlayer(Coordinate);
    bool undo();
    #ifdef CPORTA
    void render() const;
    #else // CPORTA
    void render(SDL_Renderer* renderer) const;
    #endif // CPORTA
    void saveScore(int, int) const;
    void savePosition();
    ~Level();
};

#endif // LEVEL_H
