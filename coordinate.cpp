/**
 * \file coordinate.cpp
 *
 * A Coordinate osztaly tagfuggvenyeinek definialasa
 *
 */

#include "coordinate.h"
#include "memtrace.h"

Coordinate Coordinate::operator+(Coordinate rhs) const {
    return Coordinate (x+rhs.x, y+rhs.y);
}

Coordinate Coordinate::operator-(Coordinate rhs) const{
    return Coordinate (x-rhs.x, y-rhs.y);
}

bool Coordinate::operator==(Coordinate rhs) const {
    return (x == rhs.x && y == rhs.y);
}

bool Coordinate::operator!=(Coordinate rhs) const {
    return !operator==(rhs);
}

bool Coordinate::operator<(Coordinate rhs) const {
    return (x < rhs.x || y < rhs.y);
}

bool Coordinate::operator>(Coordinate rhs) const {
    return (x > rhs.x || y > rhs.y);
}

std::ostream& operator<<(std::ostream& os, Coordinate rhs){
    os << "(" << rhs.x << "," << rhs.y << ")";
    return os;
}
