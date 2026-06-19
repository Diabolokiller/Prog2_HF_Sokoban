/**
 * \file inputHandler.h
 *
 * A getInput fuggveny deklaralasa es az input enum definialasa
 *
 */
#include "memtrace.h"
#ifndef CPORTA
#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "coordinate.h"

enum input {up, down, left, right, quit, next, prev, undo, nothing, enter};

input getInput(const SDL_Event&  ev);

#endif // INPUTHANDLER_H_INCLUDED
#endif
