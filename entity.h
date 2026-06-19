/**
 * \file entity.h
 *
 * Az Entity osztaly definialasa
 * Mivel minden fuggvenye csak egy soros
 * ezert nincs kulonszedve .h es .cpp fajlokra
 *
 * A játékos és a doboz objektumok közös őse,
 * lehetőve teszi a heterogén kollekciójuk tárolását.
 *
 */
#ifndef ENTITY_H
#define ENTITY_H

#include "coordinate.h"
#include "memtrace.h"

enum entityType {none, player, box};

class Entity{
    Coordinate position;
public:
    Entity(Coordinate pos) : position(pos) {};
    /**
     * \brief Atallitja az entitas poziciojat
     * \param dir A mozgatas vektora, ezt hozzaadja a jelenlegi poziciojahoz
     */
    void move(Coordinate dir){
        position = position + dir;
    }
    /**
     * \return Az Entity tipusa
     */
    virtual entityType type() {return none; };
    virtual ~Entity() {};
};

class Player : public Entity{
public:
    Player(Coordinate pos) : Entity(pos) {};
    entityType type() {return player; }
};

class Box : public Entity{
public:
    Box(Coordinate pos) : Entity(pos) {};
    entityType type() {return box; }
};


#endif // ENTITY_H
