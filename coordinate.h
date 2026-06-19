/**
 * \file coordinate.h
 *
 * A Coordinate osztaly es tagfuggvenyeinek deklaralasa
 *
 * Sok osztály használ két koordinátát pozíciók és méretek
 * tárolására, ez az osztály lehetőve teszi a koordináták
 * kényelmes tárolását és kezelését.
 */

#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include "memtrace.h"

struct Coordinate{
    int x;
    int y;

    /**
    * @brief Coordinate osztaly konstruktora, parameter nelkul is meghivhato, ilyenkor 0,0-ra allitja
    * @param x Az x erteket erre allitja
    * @param y Az y erteket erre allitja
    */
    Coordinate(int x = 0, int y = 0) :x(x), y(y) {}

    /**
    * @brief Ket koordinata megfelelo ertekeit osszeadja, x-t x-el, y-t y-al
    * @param rhs az operandus jobb oldala
    * @return Az osszeadas eredmenye
    */
    Coordinate operator+(Coordinate rhs) const;
    /**
    * @brief Ket koordinata megfelelo ertekeit kivonja, x-t x-el, y-t y-al
    * @param rhs az operandus jobb oldala
    * @return A kivonas eredmenye
    */
    Coordinate operator-(Coordinate rhs) const;
    /**
    * @brief Egyenloseg operator
    * @param rhs az operandus jobb oldala
    * @return Igaz erteket ad ha az x es az y koordinatak is megegyeznek
    */
    bool operator==(Coordinate rhs) const;
    /**
    * @brief Nem egyenlo operator
    * @param rhs az operandus jobb oldala
    * @return Igaz erteket ad ha az x vagy az y koordinatak nem egyeznek meg
    */
    bool operator!=(Coordinate rhs) const;
    /**
    * @brief Kisebb mint operator
    * @param rhs az operandus jobb oldala
    * @return Igaz erteket ad ha az x es az y kisebb mint a jobb oldal x es y erteke
    */
    bool operator<(Coordinate rhs) const;
    /**
    * @brief Nagyobb mint operator
    * @param rhs az operandus jobb oldala
    * @return Igaz erteket ad ha az x es az y nagyobb mint a jobb oldal x es y erteke
    */
    bool operator>(Coordinate rhs) const;
};

/**
* @brief Inserter operator, kiirja a koordinatat a kovetkezo formatumban: (x, y)
* @param os a kiiras helyenek referenciaja
* @param rhs A kiirando koordinata
* @return A kiirashoz hasznalt ostream referenciaja
*/
std::ostream& operator<<(std::ostream& os, Coordinate rhs);

#endif // COORDINATE_H
