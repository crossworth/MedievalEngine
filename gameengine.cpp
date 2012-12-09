#include "gameengine.h"

using namespace ME;

gameEngine * gameEngine::getInstance(){
    static gameEngine *gm = new gameEngine;
    return gm;
}

gameEngine::gameEngine()
{
    dbg = Debugger::getInstance();

    mWindow = renderWindow::getInstance();

    CFGParser windowConfg;
    windowConfg.readFile("config.cfg");


    windowInformation mWindowInformation(0,0,32,false,"Medieval Engine");

    mWindowInformation.bitsPerPixel = windowConfg.getKey<int>("bitsPerPixel");
    mWindowInformation.height = windowConfg.getKey<int>("height");
    mWindowInformation.width = windowConfg.getKey<int>("width");
    mWindowInformation.fullScreen = Converter::str_to_bool(windowConfg.getKey<std::string>("fullScreen"));
    mWindowInformation.windowName = "Medieval Engine";



    mWindow->createWindow(mWindowInformation);


    if ( !mWindow->isValidWindow(mWindowInformation)){
        windowInformation validWindow = mWindow->getWindowInformation();
        windowConfg.clear();
        windowConfg.add("bitsPerPixel",Converter::int_to_str(validWindow.bitsPerPixel));
        windowConfg.add("height",Converter::int_to_str(validWindow.height));
        windowConfg.add("width",Converter::int_to_str(validWindow.width));
        windowConfg.add("fullScreen",Converter::bool_to_str(validWindow.fullScreen));
        windowConfg.saveFile("config.cfg");
    }

    assets = AssetsManager::getInstance();
    registerAllLuaFunctions();
}

void gameEngine::init(){
    mGamesStates.insert( std::make_pair("main",new mainState) );
    mGamesStates["main"]->init();
    mGamesStates["main"]->registerGameEngine(this);
    gameStateEnable = "main";
}

void gameEngine::run(){
    while(mWindow->isOpen()){
        mGamesStates[gameStateEnable]->handleEvents();
        mGamesStates[gameStateEnable]->update();
        mGamesStates[gameStateEnable]->render();
    }
}



void gameEngine::clear(){
    mWindow->~renderWindow();
    assets->~AssetsManager();
}


void gameEngine::changeGameState(const std::string &name){
    if( mGamesStates.find(name) != mGamesStates.end())
        gameStateEnable = name;
    else
        dbg->log(CRITICAL,1,("O gameState: " + name + " não foi encontrado.").c_str());

}
gameState * gameEngine::getGameStateEnable(){
    return mGamesStates[gameStateEnable];
}


gameEngine::~gameEngine(){

}
