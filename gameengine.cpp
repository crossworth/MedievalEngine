#include "gameengine.h"

using namespace ME;

gameEngine * gameEngine::getInstance(int argc,char **argv){
    static gameEngine *gm = new gameEngine(argc,argv);
    return gm;
}


int gameEngine::onExit(){
    return returnCode;
}

gameEngine::gameEngine(int argc,char **argv)
{
    returnCode = 0;

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


    mEditor = Editor::getInstance();

    //TODO: verify by the command line arguments if any editor flag was passed
    mEditor->setEditMode(true);
   // mEditor->openMap("assets/teste.map");


   Camera map(*mWindow->getDefaultCamera());
   Camera fixed(*mWindow->getDefaultCamera());
   mWindow->createCamera("fixed",fixed);
   mWindow->createCamera("map",map);


}

void gameEngine::init(){

    //TODO: define which one game state will be enable by some configuration file
    //or list of some kind

    mGamesStates.insert( std::make_pair("main",new mainState) );
    mGamesStates["main"]->init();
    mGamesStates["main"]->registerGameEngine(this);
    gameStateEnable = "main";
}

void gameEngine::run(){
    while(mWindow->isOpen()){
        mWindow->clear();
        mGamesStates[gameStateEnable]->handleEvents();
        mGamesStates[gameStateEnable]->update();
        mEditor->render(*mWindow->getRenderWindow());
        mGamesStates[gameStateEnable]->render();
        mWindow->display();

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
        dbg->log(FATAL,1,("O gameState: " + name + " não foi encontrado.").c_str());

}
gameState * gameEngine::getGameStateEnable(){
    return mGamesStates[gameStateEnable];
}


gameEngine::~gameEngine(){

}
