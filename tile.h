/**
 * \file tile.h
 *
 * Az Entity osztaly definialasa
 * Mivel minden fuggvenye csak egy soros
 * ezert nincs kulonszedve .h es .cpp fajlokra
 *
 * Ez az osztály a talaj, a fal és a cél objektumok
 * közös őse, és lehetőve teszi a heterogén kollekciójuk tárolását.
 *
 */
#ifndef TILE_H
#define TILE_H

#include "coordinate.h"
#include "memtrace.h"

enum tileType {finish, wall, ground};

class Tile{
    const Coordinate position;
public:
    Tile(Coordinate pos) : position(pos) {};
    /**
     * \return Igaz ha ra lehet lepni
     */
    virtual bool isWalkable() const = 0;
    /**
     * \return A Tile tipusat adja vissza
     */
    virtual tileType type() const = 0;
    virtual ~Tile() {};
};

class Floor : public Tile{
public:
    Floor(Coordinate pos) : Tile(pos) {};
    bool isWalkable() const { return true; }
    tileType type() const { return ground; }
};

class Wall : public Tile{
public:
    Wall(Coordinate pos) : Tile(pos) {};
    bool isWalkable() const { return false; }
    tileType type() const { return wall; }
};

class Finish : public Tile{
public:
    Finish(Coordinate pos) : Tile(pos) {};
    bool isWalkable() const { return true; }
    tileType type() const { return finish; }
};

#endif // TILE_H
