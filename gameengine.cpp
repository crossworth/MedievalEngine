#include "gameengine.h"

using namespace ME;

gameEngine * gameEngine::getInstance(int argc,char **argv) {
    static gameEngine *gm = new gameEngine(argc,argv);
    return gm;
}


int gameEngine::onExit() {
    return returnCode;
}

gameEngine::gameEngine(int argc, char** argv) {
    returnCode = 0; // Define o código de retorno padrão

    dbg     = Debugger::getInstance();
    mWindow = renderWindow::getInstance();

    CFGParser configurations;
    configurations.readFile(ENGINE_DEFAULTS::CONFIG_FILE);

    // Verifica as informações do arquivo de configuração
    // e cria a janela com base nelas ou com base nas defaults
    windowInformation mWindowInformation;

    std::string tmpBitsPerPixel, tmpHeight, tmpWidth, tmpFullScreen, tmpWindowName;

    tmpBitsPerPixel = configurations.getKey("bits_per_pixel");
    tmpHeight       = configurations.getKey("height");
    tmpWidth        = configurations.getKey("width");
    tmpFullScreen   = configurations.getKey("fullscreen");
    tmpWindowName   = configurations.getKey("engine_name");


    if(tmpBitsPerPixel != "") {
        mWindowInformation.bitsPerPixel = TO::str_to_int(tmpBitsPerPixel);
    }

    if(tmpHeight != "") {
        mWindowInformation.height = TO::str_to_int(tmpHeight);
    }

    if(tmpWidth != "") {
        mWindowInformation.width = TO::str_to_int(tmpWidth);
    }

    if(tmpFullScreen != "") {
        mWindowInformation.fullScreen = TO::str_to_bool(tmpFullScreen);
    }

    if (tmpWindowName != "") {
        mWindowInformation.windowName = tmpWindowName;
    }

    mWindow->createWindow(mWindowInformation);

    // Caso não seja uma janela válida cria um arquivo com as informações válidas para janela
    if (!mWindow->isValidWindow(mWindowInformation)) {
        windowInformation validWindow = mWindow->getWindowInformation();
        configurations.add("bits_per_pixel", TO::int_to_str(validWindow.bitsPerPixel));
        configurations.add("height", TO::int_to_str(validWindow.height));
        configurations.add("width", TO::int_to_str(validWindow.width));
        configurations.add("fullscreen", TO::bool_to_str(validWindow.fullScreen));
        configurations.saveFile(ENGINE_DEFAULTS::CONFIG_FILE);
    }

    // Inicia o AssetsManager
    assets = AssetsManager::getInstance();

    // Registra as funções da LuaEngine
    registerFunctions();


    Image *icon           = assets->loadImage("icon_engine", "icon.png", true);
    sf::Vector2u iconSize = icon->getSize();

    mWindow->setIcon(iconSize.x, iconSize.y, *icon);


}

void gameEngine::init() {

    QDir gameStateDir;
    gameStateDir.setCurrent(QString((GLOBAL_PATH + "data/state").c_str()));
    gameStateDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QFileInfoList gameStatesList = gameStateDir.entryInfoList();

    if (!gameStatesList.contains(QFileInfo("main"))) {
        dbg->log(CRITICAL, 1, ("[gameEngine::init] Game State not found on folder " + gameStateDir.absolutePath().toStdString()).c_str());
    }


    for (int i = 0; i < gameStatesList.size(); i++) {
        std::string gameStateName = gameStatesList.at(i).fileName().toStdString();
        std::string gameStatePath = gameStatesList.at(i).absolutePath().toStdString();
        gameStatePath             = gameStatePath + "/" + gameStateName;

        mGamesStates.insert(std::make_pair(gameStateName, new luaState(gameStateName, gameStatePath)));
        mGamesStates[gameStateName]->registerGameEngine(this);

        dbg->log(VERBOSE, 1, ("[gameEngine::init] Game State (" + gameStateName + ") added").c_str());
    }

    gameStateEnable = "main";
    mGamesStates[gameStateEnable]->init();
}

void gameEngine::run() {

    while(mWindow->isOpen()) {
        mWindow->clear();
        mGamesStates[gameStateEnable]->handleEvents();
        mGamesStates[gameStateEnable]->update();
        mGamesStates[gameStateEnable]->render();
        mWindow->display();
    }
}

void gameEngine::clear() {
    mWindow->~renderWindow();
    assets->~AssetsManager();
}

void gameEngine::changeGameState(const std::string &name) {
    if( mGamesStates.find(name) != mGamesStates.end()) {
        gameStateEnable = name;
        mGamesStates[gameStateEnable]->init();
    } else {
        dbg->log(CRITICAL, 1 ,("[gameEngine::changeGameState] GameState (" + name + ") not found.").c_str());
    }
}

gameState * gameEngine::getActiveGameState() {
    return mGamesStates[gameStateEnable];
}


gameEngine::~gameEngine() {

}
