/**
 * \file menu.cpp
 *
 * A Menu osztaly es tagfuggvenyeinek definialasa
 *
 */
#include "menu.h"
#include "memtrace.h"


#ifndef CPORTA
/**
* \brief Menu osztaly konstruktora, betolti az osszes palyat a megadott katalogusbol
* \param dir a beolvasando palyak txt fajlainak helye
*/
Menu::Menu(const char* dir){
    levelCount = 0;
    currentLevel = 0;
    levels = nullptr;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(dir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                loadLevel(entry.path().string().c_str());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    if(levelCount == 0) {
        std::cout <<    "No levels found in: " << std::filesystem::current_path().string() << '\n';
        exit(-1);
    }
}
#else
Menu::Menu(const char* dir){
    levelCount = 0;
    currentLevel = 0;
    levels = nullptr;
    loadLevel("soko001.txt");
    if(levelCount == 0) {
        std::cout <<    "No levels found";
        exit(-1);
    }
}
#endif

/**
 * \brief Betolti az adott filebol a palyat es eltarolja
 * \param filaName a betoltendo txt fajl neve
 * \return Igaz ha sikerult betolteni, hamis ha nem
 */
bool Menu::loadLevel(const char* fileName){
    Coordinate siz = getFileSize(fileName);
    if(siz == Coordinate(0, 0)) return false;
    char** lvl = fileToCharMatrix(fileName, siz);
    if(lvl == nullptr) return false;
    Level* l = new Level(siz, lvl);
    for(int x = 0; x < siz.x; x++){
        delete[] lvl[x];
    }
    delete[] lvl;
    Level** p = new Level*[++levelCount];
    for(int i = 0; i < levelCount - 1; i++){
        p[i] = levels[i];
    }
    p[levelCount - 1] = l;
    delete[] levels;
    levels = p;
    return true;
}

/**
* \return Visszaadja a jelelneg aktualis palya pointeret
*/
Level* Menu::getCurrentLevel(){
    return levels[currentLevel];
}

/**
 * \brief A megadott sorszamu palyat allitja az aktualis palyara
 * \param i A palya sorszama
 */
void Menu::goToLevel(int i){
    if(i >= levelCount){
        std::cout << "There are only " << levelCount << " levels\n";
        return;
    }
    currentLevel = i;
}

Menu::~Menu(){
    for(int i = 0; i < levelCount; i++){
        delete levels[i];
    }
    delete[] levels;
}
