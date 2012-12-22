#include "editor.h"

using namespace ME;
using namespace std;

Editor * Editor::getInstance(){
    static Editor *mEditor = new Editor();
    return mEditor;
}

Editor::Editor()
{
    Index = 0;
    mDebugger = Debugger::getInstance();
    mAssets = AssetsManager::getInstance();
    mRender = renderWindow::getInstance();
    mapOpen = false;
    editModeEnable = false;
    assetsLoaded = false;
    debugNotOpenMap =true;
    showBox = false;



    mAssets->loadAssetFont("GearedSlab","assets/fonts/GearedSlab.ttf");

    Text tmp("EDITOR");
    tmp.setFont(*mAssets->getAssetFont("GearedSlab"));
    tmp.setCharacterSize(30);
    tmp.setColor(sf::Color(255,255,255));
    tmp.setPosition(mRender->getWindowInformation().width/2-tmp.getLocalBounds().width,0);
    mAssets->loadAssetText("editor",tmp);

    tmp.setString("Map Name:");
    tmp.setCharacterSize(20);
    tmp.setPosition(0,tmp.getGlobalBounds().height);
    mAssets->loadAssetText("mapName",tmp);

    tmp.setString("Tiles Count:");
    tmp.setCharacterSize(20);
    tmp.setPosition(0,tmp.getGlobalBounds().height * 3);
    mAssets->loadAssetText("tileCount",tmp);

    tmp.setString("Layer:");
    tmp.setCharacterSize(20);
    tmp.setPosition(0,tmp.getGlobalBounds().height * 5);
    mAssets->loadAssetText("layer",tmp);

    tmp.setString("Coords:");
    tmp.setCharacterSize(20);
    tmp.setPosition(0,tmp.getGlobalBounds().height * 8);
    mAssets->loadAssetText("coords",tmp);

    tmp.setString("Rotate:");
    tmp.setCharacterSize(20);
    tmp.setPosition(0,tmp.getGlobalBounds().height * 9);
    mAssets->loadAssetText("rotate",tmp);

    tmp.setString("Scale:");
    tmp.setCharacterSize(20);
    tmp.setPosition(0,tmp.getGlobalBounds().height * 11);
    mAssets->loadAssetText("scale",tmp);
}



void Editor::createMap(const std::string &name,const std::string &fileName){

    MapFile map;
    map.numberTile = Index;
    strcpy(map.mapName,name.c_str());
    for (int i =0;i < 10000;i++)
        map.tiles[i] = mTiles[i];

    ofstream file;
    file.open(fileName.c_str(),ios::binary);

    if ( file.is_open()){
        file.write(reinterpret_cast<char*>(&map),sizeof(MapFile));
        file.close();
        std::string info;
        info += "#############";
        info += "\n# Criado o mapa:" + name + "("+fileName+ ") com sucesso";
        info += "\n# N tiles: " +ME::Converter::int_to_str(map.numberTile);
        info += "#############";
        mDebugger->log(WARNING,1,info.c_str());
    }else{
        mDebugger->log(WARNING,1,("Erro ao criar o mapa:"+name+"("+fileName+")").c_str());
    }
    return;
}


MapFile *Editor::openMap(const std::string &name){
    ifstream file;
    file.open(name.c_str(),ios::binary);
    if ( file.is_open()){
        file.read(reinterpret_cast<char*>(&mMap),sizeof(MapFile));
        file.close();
        string info;
        info = "##############";
        info += "\n# Mapa aberto: " + std::string(mMap.mapName);
        info += "\n# N tiles: " + ME::Converter::int_to_str(mMap.numberTile);
        info += "\n##############";
        mDebugger->log(WARNING,1,info.c_str());
    }else{
        mDebugger->log(WARNING,1,("Erro ao abrir o mapa:"+name).c_str());
    }
    mapOpen = true;
    return &mMap;
}

void Editor::setEditMode(const bool &mode){
    editModeEnable = mode;



    QDir dir;
    dir.setCurrent("assets/tiles");
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    path =  dir.absolutePath().toStdString() + "/";
    QFileInfoList list = dir.entryInfoList();

    for(int i = 0;i < list.size();i++){
        QDir actDir;
        actDir.cd(list.at(i).fileName()+"/");
        actDir.setFilter(QDir::Files| QDir::NoDotAndDotDot | QDir::NoSymLinks);
        QFileInfoList files = actDir.entryInfoList();


        for(int j = 0;j < files.size();j++){
            tilesNames[list.at(i).fileName().toStdString()+files.at(j).fileName().toStdString()] = (list.at(i).fileName().toStdString()+files.at(j).fileName().toStdString());
            mAssets->loadAssetTexture((list.at(i).fileName().toStdString()+files.at(j).fileName().toStdString()),path+list.at(i).fileName().toStdString()+"/"+files.at(j).fileName().toStdString());
            Sprite tmp;
            tmp.setTexture(*mAssets->getAssetTexture((list.at(i).fileName().toStdString()+files.at(j).fileName().toStdString())));
            tmp.setPosition(0.0f,0.0f);
            tmp.setOrigin(tmp.getGlobalBounds().width/2,tmp.getGlobalBounds().height/2);
            mAssets->loadAssetSprite((list.at(i).fileName().toStdString()+files.at(j).fileName().toStdString()),tmp);
        }

    }

    curentMouseTileEnable = tilesNames.begin()->second;
    curentCoordTileEnable.x =0;
    curentCoordTileEnable.y = 0;
    curentRotateEnable = 0.0f;
    curentScaleEnable = 1.0f;
    curentLayerEnable = 1;


}

void Editor::render(sf::RenderWindow &mWindow){
    if ( !mapOpen && !editModeEnable){
        if ( debugNotOpenMap ){
            mDebugger->log(WARNING,1,"Nenhum mapa aberto, impossivel renderizar algo.");
            debugNotOpenMap = false;
        }
        return;
    }
    if (  !assetsLoaded){
        for(int i=0;i < mMap.numberTile;i++){
            if ( editModeEnable ){
                mAssets->loadAssetTexture(mTiles[i].textureName,mTiles[i].textureName);
            }else
                mAssets->loadAssetTexture(mMap.tiles[i].textureName,mMap.tiles[i].textureName);
            Sprite tmp;
            if ( editModeEnable ){
                tmp.setTexture(*mAssets->getAssetTexture(mTiles[i].textureName));
                tmp.setRotation(mTiles[i].rotate);
                tmp.setPosition(mTiles[i].pos.x,mTiles[i].pos.y);
                tmp.setScale(mTiles[i].scale,mTiles[i].scale);
                tmp.setOrigin(tmp.getGlobalBounds().width/2,tmp.getGlobalBounds().height/2);
                mAssets->loadAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)),tmp);
            }else{
                tmp.setTexture(*mAssets->getAssetTexture(mMap.tiles[i].textureName));
                tmp.setRotation(mMap.tiles[i].rotate);
                tmp.setPosition(mMap.tiles[i].pos.x,mMap.tiles[i].pos.y);
                tmp.scale(mMap.tiles[i].scale,mMap.tiles[i].scale);
                tmp.setOrigin(tmp.getGlobalBounds().width/2,tmp.getGlobalBounds().height/2);
                mAssets->loadAssetSprite((mMap.tiles[i].textureName+ME::Converter::int_to_str(i)),tmp);
            }
            assetsLoaded = true;
        }
    }



    // render only what is need
    // there are a few bugs, 1.8 should be 2 , but its not working , so 1.8 should be fine for now
    for(int i=0;i < mMap.numberTile;i++){

        sf::Vector2f pos = mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->getPosition();
        Coord cameraPos = mRender->getCameraPosition("map");

                if ( pos.x >= (cameraPos.x-(mRender->getWindowInformation().width)+mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->getGlobalBounds().width*2.5)  && pos.x < (cameraPos.x+(mRender->getWindowInformation().width+mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->getGlobalBounds().width/2))  &&
                 pos.y >= (cameraPos.y-(mRender->getWindowInformation().height)+mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->getGlobalBounds().height)  && pos.y < (cameraPos.y+((mRender->getWindowInformation().height)+mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->getGlobalBounds().height/1.4)) ) {
                    mRender->setCamera((sf::View)*mRender->getCamera("map"));
                    if ( editModeEnable ){

                        mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->setRotation(mTiles[i].rotate);
                        mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->setPosition(mTiles[i].pos.x+(mTiles[i].scale-1),mTiles[i].pos.y+(mTiles[i].scale-1));
                        mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->setOrigin(mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->getGlobalBounds().width/2,mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->getGlobalBounds().height/2);
                        mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->setScale(mTiles[i].scale,mTiles[i].scale);
                        mWindow.draw(*mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i))));

                    }else{
                        // TODO: verify if this is working
                        mWindow.draw(*mAssets->getAssetSprite((mMap.tiles[i].textureName+ME::Converter::int_to_str(i))));
                    }
                }
    }

    if ( editModeEnable ){
        handleEvent(mWindow);
        mRender->setCamera((sf::View)*mRender->getCamera("fixed"));

        TextHandle::TextShadow("editor",mWindow,sf::Color(0,0,0,255),sf::Vector2f(2.0,2.0));
        TextHandle::TextShadow("mapName",mWindow,sf::Color(0,0,0,255),sf::Vector2f(2.0,2.0));
        TextHandle::TextShadow("tileCount",mWindow,sf::Color(0,0,0,255),sf::Vector2f(2.0,2.0));
        TextHandle::TextShadow("layer",mWindow,sf::Color(0,0,0,255),sf::Vector2f(2.0,2.0));
        TextHandle::TextShadow("coords",mWindow,sf::Color(0,0,0,255),sf::Vector2f(2.0,2.0));
        TextHandle::TextShadow("rotate",mWindow,sf::Color(0,0,0,255),sf::Vector2f(2.0,2.0));
        TextHandle::TextShadow("scale",mWindow,sf::Color(0,0,0,255),sf::Vector2f(2.0,2.0));

    }

}


void Editor::handleEvent(sf::RenderWindow &mWindow){
    if (  !showBox ){


        sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);
        mousePos.x =  mousePos.x + mRender->getCameraPosition("map").x;
        mousePos.y =  mousePos.y + mRender->getCameraPosition("map").y;




        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
            sf::Clock mClock;
            mClock.restart();

            while( mClock.getElapsedTime().asSeconds() < 0.1){}
            std::map<std::string,std::string>::iterator it =  tilesNames.find(curentMouseTileEnable);
            if ( it == --tilesNames.end() ){
               it = tilesNames.begin();
            }else{
               it++;
            }
           curentMouseTileEnable = it->second;
           std::cout << it->second << std::endl;

        }

        mAssets->getAssetSprite(curentMouseTileEnable)->setPosition(mousePos.x,mousePos.y);
        mAssets->getAssetSprite(curentMouseTileEnable)->setColor(sf::Color(mAssets->getAssetSprite(curentMouseTileEnable)->getColor().r,mAssets->getAssetSprite(curentMouseTileEnable)->getColor().g,mAssets->getAssetSprite(curentMouseTileEnable)->getColor().b,150));
        curentCoordTileEnable.x = mousePos.x;
        curentCoordTileEnable.y = mousePos.y;



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && mRender->hasFocus ){
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                curentRotateEnable -= 1.0f;
            else
                curentRotateEnable += 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && mRender->hasFocus){
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                curentScaleEnable -= 0.01f;
            else
                curentScaleEnable += 0.01f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && mRender->hasFocus)
            curentLayerEnable =1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && mRender->hasFocus)
            curentLayerEnable =2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && mRender->hasFocus)
            curentLayerEnable =3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && mRender->hasFocus)
            curentLayerEnable =4;



        if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) && mRender->hasFocus){
            Tile tmpTile;
            tmpTile.id = Index;
            strcpy(tmpTile.eventScript,"none");
            tmpTile.layer = curentLayerEnable;
            tmpTile.pos.x = curentCoordTileEnable.x;
            tmpTile.pos.y = curentCoordTileEnable.y;
            tmpTile.rotate = curentRotateEnable;
            tmpTile.scale =  curentScaleEnable;
            std::string tmpStr;
            tmpStr = curentMouseTileEnable;
            int p = tmpStr.find("0");
            tmpStr.insert(p-1,"/");
            tmpStr = path + tmpStr;
            std::cout << tmpStr << std::endl;
            strcpy(tmpTile.textureName,tmpStr.c_str());
            mTiles[Index] = tmpTile;
            Index++;
            mMap.numberTile = Index;
            assetsLoaded = false;
            if (  !mapOpen )
                mapOpen = true;
        }

         if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) && mRender->hasFocus){
             for(int i=0;i< mMap.numberTile;i++){
                 sf::FloatRect area = mAssets->getAssetSprite((mTiles[i].textureName+ME::Converter::int_to_str(i)))->getGlobalBounds();
                 if  ( area.contains(mousePos.x,mousePos.y) ){
                    Index = mMap.numberTile = mMap.numberTile  - 1;

                     for(int j = i;j <  mMap.numberTile;j++){
                         mTiles[j] = mTiles[j + 1];
                     }

                     mAssets->removeAsset(mTiles[i].textureName+ME::Converter::int_to_str(i),SPRITE);
                     assetsLoaded = false;
                 }
             }
         }






        mAssets->getAssetSprite(curentMouseTileEnable)->setRotation(curentRotateEnable);
        mAssets->getAssetSprite(curentMouseTileEnable)->setScale(curentScaleEnable,curentScaleEnable);
    }

    mWindow.draw(*mAssets->getAssetSprite(curentMouseTileEnable));

    if (  sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
        showBox  =true;


        //createMap("teste",globalPath+"assets/teste.map");

    }

    if  ( showBox ){
        GUI* mGUI = GUI::getInstace();
        if ( (mGUI->messageBox("Teste de titulo","Teste de Mensagem")).size() > 0){
            std::cout << "OK agora tem respotas"<< std::endl;
            showBox =false;
        }
    }



    mAssets->getAssetText("mapName")->setString("Map Name: Sem nome");
    mAssets->getAssetText("tileCount")->setString("Tile Count:"+ME::Converter::int_to_str(Index));
    mAssets->getAssetText("layer")->setString("Layer:"+ME::Converter::int_to_str(curentLayerEnable));
    mAssets->getAssetText("coords")->setString("Coords X:"+ME::Converter::int_to_str(curentCoordTileEnable.x)+" Y:"+ME::Converter::int_to_str(curentCoordTileEnable.y));
    mAssets->getAssetText("rotate")->setString("Rotate:"+ME::Converter::float_to_string(curentRotateEnable));
    mAssets->getAssetText("scale")->setString("Scale:"+ME::Converter::float_to_string(curentScaleEnable));
}
