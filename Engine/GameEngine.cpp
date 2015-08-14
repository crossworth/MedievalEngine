//#include "GameEngine.h"
//#include "LuaEngine.h"
//#include "LuaState.h"
//#include "luafunctions.h"

//using namespace ME;

//GameEngine* GameEngine::gm = nullptr;

//GameEngine* GameEngine::getInstance(int argc, char **argv) {
//    if (gm == nullptr) {
//        gm = new GameEngine(argc, argv);
//    }
//    return gm;
//}


//int GameEngine::onExit() {
//    return returnCode;
//}

//GameEngine::GameEngine(int argc, char** argv) {
//    returnCode       = 0; // Define o código de retorno padrão
//    _startedMainLoop = false;

//    dbg     = Debugger::getInstance();
//    mWindow = RenderWindow::getInstance();
//    mLua    = LuaEngine::getInstace();

//    CFGParser configurations;
//    configurations.readFile(ENGINE_DEFAULTS::CONFIG_FILE);

//    // Verifica as informações do arquivo de configuração
//    // e cria a janela com base nelas ou com base nas defaults
//    windowInformation mWindowInformation;

//    std::string tmpBitsPerPixel, tmpHeight, tmpWidth, tmpFullScreen, tmpWindowName;

//    tmpBitsPerPixel = configurations.getKey("bits_per_pixel");
//    tmpHeight       = configurations.getKey("height");
//    tmpWidth        = configurations.getKey("width");
//    tmpFullScreen   = configurations.getKey("fullscreen");
//    tmpWindowName   = configurations.getKey("engine_name");


//    if(tmpBitsPerPixel != "") {
//        mWindowInformation.bitsPerPixel = TO::str_to_int(tmpBitsPerPixel);
//    }

//    if(tmpHeight != "") {
//        mWindowInformation.height = TO::str_to_int(tmpHeight);
//    }

//    if(tmpWidth != "") {
//        mWindowInformation.width = TO::str_to_int(tmpWidth);
//    }

//    if(tmpFullScreen != "") {
//        mWindowInformation.fullScreen = TO::str_to_bool(tmpFullScreen);
//    }

//    if (tmpWindowName != "") {
//        mWindowInformation.windowName = tmpWindowName;
//    }

//    mWindow->createWindow(mWindowInformation);

//    // Caso não seja uma janela válida cria um arquivo com as informações válidas para janela
//    if (!mWindow->isValidWindow(mWindowInformation)) {
//        windowInformation validWindow = mWindow->getWindowInformation();
//        configurations.add("bits_per_pixel", TO::int_to_str(validWindow.bitsPerPixel));
//        configurations.add("height", TO::int_to_str(validWindow.height));
//        configurations.add("width", TO::int_to_str(validWindow.width));
//        configurations.add("fullscreen", TO::bool_to_str(validWindow.fullScreen));
//        configurations.saveFile(ENGINE_DEFAULTS::CONFIG_FILE);
//    }

//    // Inicia o AssetsManager
//    assets = AssetsManager::getInstance();

//    Image *icon = assets->loadImage("icon_engine", "icon.png", true);
//    if(icon != nullptr) {
//        sf::Vector2u iconSize = icon->getSize();
//        mWindow->setIcon(iconSize.x, iconSize.y, *icon);
//    }

//}

//void GameEngine::init() {

//    // Registra as funções da LuaEngine
//    registerFunctions();

//    QDir gameStateDir;
//    gameStateDir.setCurrent(QString((GLOBAL_PATH + "data/state").c_str()));
//    gameStateDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
//    QFileInfoList gameStatesList = gameStateDir.entryInfoList();

//    if (!gameStatesList.contains(QFileInfo("main"))) {
//        dbg->log(CRITICAL, 1, ("[gameEngine::init] Game State not found on folder " + gameStateDir.absolutePath().toStdString()).c_str());
//    }

//    for (int i = 0; i < gameStatesList.size(); i++) {
//        std::string gameStateName = gameStatesList.at(i).fileName().toStdString();
//        std::string gameStatePath = gameStatesList.at(i).absolutePath().toStdString();
//        gameStatePath             = gameStatePath + "/" + gameStateName;

//        mGamesStates.insert(std::make_pair(gameStateName, new LuaState(gameStateName, gameStatePath)));
//        mGamesStates[gameStateName]->registerGameEngine(this);

//        dbg->log(VERBOSE, 1, ("[gameEngine::init] Game State (" + gameStateName + ") added").c_str());
//    }

//    changeGameState("main");
//}

//void GameEngine::run() {
//    _startedMainLoop = true;
//    while(mWindow->isOpen()) {
//        mWindow->clear();
//        mGamesStates[gameStateEnable]->handleEvents();
//        mGamesStates[gameStateEnable]->update();
//        mGamesStates[gameStateEnable]->render();
//        mWindow->display();
//    }
//}

//void GameEngine::clear() {
//    mWindow->~RenderWindow();
//    assets->~AssetsManager();
//}

//void GameEngine::changeGameState(const std::string &name) {
//    GameEngine* gm = GameEngine::getInstance();

//    if (gm->mGamesStates.find(name) != gm->mGamesStates.end()) {
//        if (gm->_startedMainLoop) {
//            gm->mGamesStates[gm->gameStateEnable]->onDisableTransition();
//        }

//        gm->gameStateEnable = name;
//        gm->mGamesStates[gm->gameStateEnable]->init();
//        gm->mGamesStates[gm->gameStateEnable]->onEnableTransition();
//    } else {
//        gm->dbg->log(CRITICAL, 1 ,("[gameEngine::changeGameState] GameState (" + name + ") not found.").c_str());
//    }
//}

//GameState* GameEngine::getActiveGameState() {
//    return mGamesStates[gameStateEnable];
//}


//GameEngine::~GameEngine() {

//}
