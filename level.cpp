/**
 * \file level.cpp
 *
 * A Level osztaly es tagfuggvenyeinek definialasa
 * A fajl beolvasashoz hasznalt fuggvenyek definialasa
 *
 *
 */
#include "level.h"
#include "memtrace.h"

#define undoGridSize 50

/**
 * \brief Level osztaly konstruktora
 * \param siz A palya merete
 * \param lvl A palya, char matrix formatumban
 */
Level::Level(const Coordinate siz, char** lvl) : siz(siz), undoGrid(new UndoGrid[undoGridSize]), moveCount(0), savedMoves(0), prevMoveIndex(-1) {
    for(int i = 0; i < undoGridSize; i++){
        undoGrid[i].entityGrid = new Entity**[siz.x];
    }
    tileGrid = new Tile**[siz.x];
    entityGrid = new Entity**[siz.x];
    for(int x = 0; x < siz.x; x++){
        tileGrid[x] = new Tile*[siz.y];
        entityGrid[x] = new Entity*[siz.y];
        for(int i = 0; i < undoGridSize; i++){
            undoGrid[i].entityGrid[x] = new Entity*[siz.y];
            for(int y = 0; y < siz.y; y++)
                undoGrid[i].entityGrid[x][y] = nullptr;
        }
    }
    for(int y = 0; y < siz.y; y++){
        for(int x = 0; x < siz.x; x++){
            switch(lvl[x][y]){
                case '#': tileGrid[x][y] = new Wall(Coordinate(x, y)); break;
                case '*': tileGrid[x][y] = new Finish(Coordinate(x, y)); break;
                case '.': tileGrid[x][y] = new Finish(Coordinate(x, y)); break;
                case '+': tileGrid[x][y] = new Finish(Coordinate(x, y)); break;
                default: tileGrid[x][y] = new Floor(Coordinate(x, y)); break;
            }
            switch(lvl[x][y]){
                case '@': entityGrid[x][y] = new Player(Coordinate(x, y)); playerPosition = Coordinate(x, y); break;
                case '+': entityGrid[x][y] = new Player(Coordinate(x, y)); playerPosition = Coordinate(x, y); break;
                case '$': entityGrid[x][y] = new Box(Coordinate(x, y)); break;
                case '*': entityGrid[x][y] = new Box(Coordinate(x, y)); break;
                default: entityGrid[x][y] = new Entity(Coordinate(x, y)); break;
            }
        }
    }
}

#ifdef CPORTA
void Level::render() const {
    system("cls");
    for(int y = 0; y < siz.y; y++){
        for(int x = 0; x < siz.x; x++){
            switch(tileGrid[x][y]->type()){
                case ground:
                    switch(entityGrid[x][y]->type()){
                        case player : std::cout << '@'; break;
                        case box : std::cout << '$'; break;
                        default : std::cout << ' '; break;
                    } break;
                case finish :
                    switch(entityGrid[x][y]->type()){
                        case player : std::cout << '+'; break;
                        case box : std::cout << '*'; break;
                        default : std::cout << '.'; break;
                    } break;
                case wall : std::cout << '#'; break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << playerPosition << "\nundoGridSize: " << undoGridSize << "\nsavedMoves: " << savedMoves << "\nprevMoveIndex: " << prevMoveIndex << '\n';

}
#else // CPORTA

/**
 * \brief Kirajzolja a palya jelenlegi allapotat
 * \param renderer SDL altal hasznalt renderer
 */

void Level::render(SDL_Renderer* renderer) const{
    for(int y = 0; y < siz.y; y++){
        for(int x = 0; x < siz.x; x++){
            switch(tileGrid[x][y]->type()){
                case ground:
                    switch(entityGrid[x][y]->type()){
                        case player :   drawGround(renderer, x, y);
                                        drawPlayer(renderer, x, y);
                                        break;
                        case box :      drawGround(renderer, x, y);
                                        drawBox(renderer, x, y);
                                        break;
                        default :       drawGround(renderer, x, y);
                                        break;
                    } break;
                case finish :
                    switch(entityGrid[x][y]->type()){
                        case player :   drawFinish(renderer, x, y);
                                        drawPlayer(renderer, x, y);
                                        break;
                        case box :      drawFinish(renderer, x, y);
                                        drawBox(renderer, x, y);
                                        break;
                        default :       drawFinish(renderer, x, y);
                                        break;
                    } break;
                case wall : drawWall(renderer, x, y); break;
            }
        }
    }
}

#endif // CPORTA

/**
 * \brief Elmozgatja a jatekost es a dobozokat amit esetleg tol
 * \param dir Az a vektor amivel a jatekos es a dobozok pozicioja meg lesz valtoztatva
 * \return Igaz, ha a jatekos el tudott mozdulni, hamis, ha nem (pl falba utkozott)
 */

bool Level::movePlayer(Coordinate dir){
    if(dir == Coordinate(0, 0)) return false;
    Coordinate newpos = playerPosition;
    do {
        newpos = newpos + dir;
        if(newpos > (siz - Coordinate(1, 1)) || newpos < Coordinate(0, 0)) return false;
        if(!tileGrid[newpos.x][newpos.y]->isWalkable()) return false;
    }while(entityGrid[newpos.x][newpos.y]->type() != none);

    savePosition();

    Coordinate prevpos = newpos;

    while(prevpos != playerPosition) {
        prevpos = prevpos - dir;

        entityGrid[prevpos.x][prevpos.y]->move(dir);
        entityGrid[newpos.x][newpos.y]->move(Coordinate(0, 0) - dir);

        Entity* temp = entityGrid[newpos.x][newpos.y];
        entityGrid[newpos.x][newpos.y] = entityGrid[prevpos.x][prevpos.y];
        entityGrid[prevpos.x][prevpos.y] = temp;

        newpos = prevpos;
    }
    playerPosition = playerPosition + dir;
    moveCount++;
    return true;
}
/**
 * \brief Ellenorzi, hogy kesz van a palya
 * \return Igaz, ha vege a palyanak
 */

bool Level::isComplete() const {
    for(int x = 0; x < siz.x; x++)
        for(int y = 0; y < siz.y; y++)
            if(entityGrid[x][y]->type() != box)
                if(tileGrid[x][y]->type() == finish) return false;
    return true;
}

/**
 * \brief Eltarolja a jelenlegi poziciot
 */
void Level::savePosition(){
    for(int x = 0; x < siz.x; x++){
        for(int y = 0; y < siz.y; y++){
            Entity* temp = nullptr;
            Coordinate pos(x,y);
            switch(entityGrid[x][y]->type()){
                case player: temp = new Player(pos); break;
                case box: temp = new Box(pos); break;
                default: temp = new Entity(pos); break;
            }
            delete undoGrid[(prevMoveIndex + 1) % undoGridSize].entityGrid[x][y];
            undoGrid[(prevMoveIndex + 1) % undoGridSize].entityGrid[x][y] = temp;
        }
    }
    undoGrid[(prevMoveIndex + 1) % undoGridSize].playerPosition = playerPosition;
    savedMoves = (savedMoves < undoGridSize) ? savedMoves + 1 : savedMoves;
    prevMoveIndex = (prevMoveIndex + 1) % undoGridSize;
}

Level::~Level(){
    for(int x = 0; x < siz.x; x++){
        for(int y = 0; y < siz.y; y++){
            delete entityGrid[x][y];
            delete tileGrid[x][y];
            for(int i = 0; i < undoGridSize; i++)
                delete undoGrid[i].entityGrid[x][y];
        }
        delete[] entityGrid[x];
        delete[] tileGrid[x];
        for(int i = 0; i < undoGridSize; i++)
            delete[] undoGrid[i].entityGrid[x];
    }
    delete[] entityGrid;
    delete[] tileGrid;
    for(int i = 0; i < undoGridSize; i++)
        delete[] undoGrid[i].entityGrid;
    delete[] undoGrid;
}

/**
 * \brief visszaallitja az eggyel ezelotti poziciot
 * \return Hamis, ha nincs tobb elmentett pozicio
 */
bool Level::undo(){
    if(savedMoves == 0) return false;
    for(int x = 0; x < siz.x; x++){
        for(int y = 0; y < siz.y; y++){
            delete entityGrid[x][y];
        }
    }
    for(int x = 0; x < siz.x; x++){
        for(int y = 0; y < siz.y; y++){
            Entity* temp = nullptr;
            Coordinate pos(x,y);
            switch(undoGrid[prevMoveIndex].entityGrid[x][y]->type()){
                case player: temp = new Player(pos); break;
                case box: temp = new Box(pos); break;
                default: temp = new Entity(pos); break;
            }
            entityGrid[x][y] = temp;
            delete undoGrid[prevMoveIndex].entityGrid[x][y];
            undoGrid[prevMoveIndex].entityGrid[x][y] = nullptr;
        }
    }
    playerPosition = undoGrid[prevMoveIndex].playerPosition;
    savedMoves--;
    moveCount--;
    prevMoveIndex = (prevMoveIndex == 0)? undoGridSize - 1 : prevMoveIndex - 1;
    return true;
}

/**
 * \brief A megadott txt fajlbol kiolvassa, hogy megkora a benne levo palya merete, a palya utan mindent ignoral
 * \param fileName a beolvasando fajl neve
 * \return A palya merete
 */

Coordinate getFileSize(const char* fileName){
    std::ifstream file(fileName);
    if(!file.is_open()) return Coordinate(0,0);
    Coordinate siz;
    char buf = file.get();
    while(buf != EOF){
        int tempX = 0;
        while(buf != '\n' && buf != EOF){
            tempX++;
            buf = file.get();
            if(buf == '\r')
                buf = file.get();
        }
        siz.x = (tempX > siz.x) ? tempX : siz.x;
        siz.y++;
        buf = file.get();
        if(buf != ' ' && buf != '#' && buf != '@' && buf != '$' && buf != '.' && buf != '*' && buf != '+'){
            file.close();
            return siz;
        }
    }
    file.close();
    return siz;
}

/**
 * \brief A megadott txt fajlbol kiolvassa a palyat
 * \param fileName a beolvasando fajl neve
 * \param siz A palya merete
 * \return A beolvasott palya dinamikusan foglalt char matrixa, ezt a fuggveny nem szabaditja fel
 */
char** fileToCharMatrix(const char* fileName, Coordinate siz){
    std::ifstream file(fileName);
    if(!file.is_open()) return nullptr;
    char** out = new char* [siz.x];
    for(int x = 0; x < siz.x; x++)
        out[x] = new char[siz.y];
    char buf = file.get();
    int y = 0;
    while(buf != EOF && y < siz.y){
        int x = 0;
        while(buf != '\n' && buf != EOF && x < siz.x){
            out[x][y] = buf;
            x++;
            buf = file.get();
            if(buf == '\r')
                buf = file.get();
        }
        for(int i = x; i < siz.x; i++)
            out[i][y] = ' ';
        y++;
        buf = file.get();
    }
    file.close();
    return out;
}

/**
 * \brief lementi a lepesszamot, ha az jobb mint az eddig lementett lepesszam
 * \param lvl A palya sorszsma
 * \param all Az osszes palya szama
 */

void Level::saveScore(int lvl, int all) const {
    #ifdef CPORTA
    const char* highscore = "CPORTAhighscore.txt";
    #else
    const char* highscore = "highscore.txt";
    #endif // CPORTA

    int* scores = new int[all];
    for(int i = 0; i < all; i++) scores[i] = 0;

    std::ifstream file(highscore);
    int buf;
    for(int i = 0; file >> buf >> scores[i] && i < 50; i++){}
    file.close();
    std::ofstream hFile(highscore);
    if(scores[lvl] > moveCount || scores[lvl] == 0){
        for(int i = 0; i < all; i++){
            hFile << i + 1 << ' ';
            if(i == lvl) hFile << moveCount << '\n';
            else hFile << scores[i] << '\n';
        }
    }
    delete[] scores;
}
