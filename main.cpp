#include <iostream>
#include "menu.h"
#include "entity.h"
#include "tile.h"
#include "coordinate.h"
#include "level.h"
#include "inputHandler.h"
#include "gameplay.h"
#include "gtest_lite.h"

//#define CPORTA

#ifdef CPORTA
void CPORTAtest();
#endif // CPORTA


#ifndef CPORTA
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#endif // CPORTA
#include "memtrace.h"

int main(int argc, char *argv[]) {
#ifndef CPORTA
    std::cout   << "controls:\n"
                << "move: w,a,s,d\n"
                << "undo: e, u\n"
                << "enter level: enter, space\n"
                << "quit: q, escape\n";
    while(mainMenu("./levels")){};
#else // CPORTA

    CPORTAtest();

    Menu menu(".");
    int moveCount = 0;
    int a = 0;
    char m = 0;
    menu.getCurrentLevel()->render();
    while(m != '0' && !menu.getCurrentLevel()->isComplete()){            //teszteléshez használt gameplay loop irányítás: wasd, 0-val ki lehet lépni, n-nel ki lehet választani, hogy hányadik pálya legyen látható a betöltött pályák közül (pl: n1)
        std::cin >> m;
        Coordinate dir;
        switch(m){
            case 'w': dir = Coordinate(0, -1); break;
            case 'a': dir = Coordinate(-1, 0); break;
            case 's': dir = Coordinate(0, 1); break;
            case 'd': dir = Coordinate(1, 0); break;
            case 'n': std::cin >> a; menu.goToLevel(a); break;
            case 'u': if(menu.getCurrentLevel()->undo()) moveCount--;           //még nem működik
                break;
            default: dir = Coordinate(0, 0); break;
        }
        if(menu.getCurrentLevel()->movePlayer(dir)) moveCount++;
        menu.getCurrentLevel()->render();
        std::cout << "moveCount: " << moveCount << '\n';
    }
    if(menu.getCurrentLevel()->isComplete()){
        std::cout << "\nFinished in " << moveCount << " steps\n";
        menu.getCurrentLevel()->saveScore(menu.getCurrentLevelInt(), menu.getLevelCount());
    }
#endif // CPORTA
    return 0;
}
#ifdef CPORTA

void CPORTAtest(){
    Menu menu(".");
    TEST(menu, loadlevel){
        menu.loadLevel("cportatest.txt");
        EXPECT_EQ(2, menu.getLevelCount());
        EXPECT_EQ(Coordinate(19, 6), menu.getCurrentLevel()->getSize());
    } ENDM
    TEST(menu, goToLevel){
        EXPECT_EQ(0, menu.getCurrentLevelInt());
        menu.goToLevel(1);
        EXPECT_EQ(1, menu.getCurrentLevelInt());
        EXPECT_EQ(Coordinate(13, 8), menu.getCurrentLevel()->getSize());
    } ENDM
    TEST(level, moving){
        Coordinate playerPos = menu.getCurrentLevel()->getPlayerPos();
        EXPECT_EQ(Coordinate(8, 3), playerPos);
        menu.getCurrentLevel()->movePlayer(Coordinate(-6, 0));
        playerPos = playerPos + Coordinate(-6, 0);
        EXPECT_EQ(playerPos, menu.getCurrentLevel()->getPlayerPos());
        menu.getCurrentLevel()->movePlayer(Coordinate(-1, 0));
        EXPECT_EQ(playerPos, menu.getCurrentLevel()->getPlayerPos());
        menu.getCurrentLevel()->movePlayer(Coordinate(0, 1));
        playerPos = playerPos + Coordinate(0, 1);
        EXPECT_EQ(playerPos, menu.getCurrentLevel()->getPlayerPos());
    }ENDM
    TEST(level, boxMoving){
        Coordinate playerPos = menu.getCurrentLevel()->getPlayerPos();
        menu.getCurrentLevel()->movePlayer(Coordinate(1, 0));
        playerPos = playerPos + Coordinate(1, 0);
        EXPECT_EQ(playerPos, menu.getCurrentLevel()->getPlayerPos());
    }ENDM
    TEST(level, undo){
        Coordinate playerPos = menu.getCurrentLevel()->getPlayerPos();
        menu.getCurrentLevel()->undo();
        playerPos = playerPos - Coordinate(1, 0);
        EXPECT_EQ(playerPos, menu.getCurrentLevel()->getPlayerPos());
    }ENDM
    system("pause");
}

#endif // CPORTA
