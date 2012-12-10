#ifndef EDITOR_H
#define EDITOR_H
#include "engine_config.h"


namespace ME{

class editor
{
public:
    static editor *getInstance();
    void create(const std::string &name);
    void insertTile(Tile &tile);
    MapFile *open(const std::string &name);
    void render(sf::RenderWindow &mWindow);
protected:
    editor();
    Tile mTiles[10*10];
    int Index;
    MapFile mMap;
};


}
#endif // EDITOR_H
