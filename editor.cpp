#include "editor.h"

using namespace ME;
using namespace std;

editor * editor::getInstance(){
    static editor *mEditor = new editor();
    return mEditor;
}

editor::editor()
{
    Index = 0;
}

void editor::insertTile(Tile &tile){
    strcpy(mTiles[Index].eventScript,"none");
    mTiles[Index].id = Index;
    mTiles[Index].layer =1;
    mTiles[Index].pos.x = tile.pos.x;
    mTiles[Index].pos.y = tile.pos.y;
    mTiles[Index].size.width = tile.size.width;
    mTiles[Index].size.height = tile.size.height;
    strcpy(mTiles[Index].textureName,"assets/tile.png");
    mTiles[Index].type =  NORMAL;
    Index++;
    cout << "Tile inserido na posicao " << tile.pos.x << " " << tile.pos.y << endl;
}


void editor::create(const std::string &name){

    MapFile map;
    map.numberTile = Index;
    strcpy(map.mapName,"TesteMapa");
    for (int i =0;i < 10*10;i++)
        map.tiles[i] = mTiles[i];

    ofstream file;
    file.open(name.c_str(),ios::binary);
    if ( file.is_open()){
        file.write(reinterpret_cast<char*>(&map),sizeof(MapFile));
        file.close();
    }else{
        cout << "Erro ao criar o mapa" << endl;

    }

}


MapFile *editor::open(const std::string &name){


    ifstream file;
    file.open(name.c_str(),ios::binary);
    if ( file.is_open()){
        file.read(reinterpret_cast<char*>(&mMap),sizeof(MapFile));
        file.close();
        cout << "Mapa aberto" << endl;
        cout << "numero de tiles :" << mMap.numberTile << endl;
    }else{
        cout << "Erro ao abir o mapa" << endl;

    }

    std::cout << mMap.mapName << std::endl;

    return &mMap;
}

void editor::render(sf::RenderWindow &mWindow){

}
