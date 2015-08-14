//#include "LuaState.h"
//#include "GameEngine.h"
//#include "Fade.h"

//using namespace ME;

//LuaState::LuaState(std::string name, std::string path) {
//    this->name = name;
//    this->path = path;

//    mGUI.addObject("testText", new TextObject("Teste", 30));
//}

//void LuaState::init() {
//    GameState::setState(INIT);
//    mLua->doFile(path + "/scripts/init.lua");
//    running = true;


//}

//void LuaState::render() {
//    RenderWindow* mWindow = RenderWindow::getInstance();
//    mWindow->getRenderWindow()->setTitle(ENGINE_DEFAULTS::ENGINE_NAME + " - State: " + GameState::getStateString());

//    for(std::vector<Effects*>::iterator it = mEffects.begin(); it != mEffects.end(); it++) {
//        (*it)->draw();
//    }

//    switch (GameState::getState()) {
//    case RENDER:
//        mLua->doFile(path + "/scripts/render.lua");
//        mGUI.draw();
//        break;
//    case PLAY:
//        mLua->doFile(path + "/scripts/play.lua");
//        break;
//    case PAUSE:
//        mLua->doFile(path + "/scripts/pause.lua");
//        break;
//    case ENABLE_TRANSITION:
//        mLua->doFile(path + "/scripts/enable_transition.lua");
//        break;
//    case DISABLE_TRANSITION:
//        mLua->doFile(path + "/scripts/disable_transition.lua");
//        break;
//    default:
//        break;
//    }
//}

//void LuaState::handleEvents() {
//    while(mRender->pollEvent(mEvent)) {
//        mGUI.processEvents(mEvent);

//        if (mEvent.type == sf::Event::Closed) {
//            mLua->doFile(path + "/scripts/events/close.lua");
//            mRender->close(); // Aguardar close do close.lua ?
//        }
//        if (mEvent.type == sf::Event::GainedFocus) {
//            mLua->doFile(path + "/scripts/events/gained_focus.lua");
//            mRender->hasFocus = true;
//        }
//        if (mEvent.type == sf::Event::LostFocus) {
//            mRender->hasFocus = false;
//            mLua->doFile(path + "/scripts/events/lost_focus.lua");
//        }
//        if (mEvent.type == sf::Event::KeyReleased) {
//            mLua->doFile(path + "/scripts/events/key_released.lua");
//        }
//        if (mEvent.type == sf::Event::KeyPressed) {
//            mLua->doFile(path + "/scripts/events/key_pressed.lua");
//        }
//        if (mEvent.type == sf::Event::MouseButtonPressed ){
//            mLua->doFile(path + "/scripts/events/mouse_button_pressed.lua");
//        }
//        if (mEvent.type == sf::Event::MouseButtonReleased) {
//            mLua->doFile(path + "/scripts/events/mouse_button_released.lua");
//        }
//        if (mEvent.type == sf::Event::MouseWheelMoved) {
//            mLua->doFile(path + "/scripts/events/mouse_wheel_moved.lua");
//        }
//    }
//}

//LuaState::~LuaState() {

//}

//void LuaState::update() {
//    if (running) {
//        mLua->doFile(path + "/scripts/update.lua");

//        mGUI.update();

//        std::vector<Effects*>::iterator itEffects = mEffects.begin();

//        for(uint i = 0; i < mEffects.size(); i++) {
//            if ((*itEffects)->done()) {

//                // Chama a função effectDone no arquivo update.lua após finalizar um efeito em algum objeto
//                // void effectDone (string sprite_name, string effect_name)
//                mLua->callFunction("effectDone", (*itEffects)->getSpriteName(), (*itEffects)->getEffectName());
//                delete *itEffects;
//                mEffects.erase(itEffects);
//            } else {
//                (*itEffects)->update();
//            }
//            itEffects++;
//        }

//        std::vector<CallBack*>::iterator itCallBack = mCallBacks.begin();

//        for(uint i = 0; i < mCallBacks.size(); i++) {
//            if ((*itCallBack)->execute()) {

//                // Chama a função registrada em callBack
//                mLua->callRegistredFunction((*itCallBack)->getFunctionName().c_str());
//                delete *itCallBack;
//                mCallBacks.erase(itCallBack);
//            } else {
//                (*itCallBack)->update();
//            }
//            itCallBack++;
//        }
//    }
//}

//void LuaState::onEnableTransition() {
//    GameState::setState(ENABLE_TRANSITION);
//}

//void LuaState::onDisableTransition() {
//    GameState::setState(DISABLE_TRANSITION);
//}

//void LuaState::restart() {
//    this->init();
//}

//void LuaState::play() {
//    GameState::setState(PLAY);
//    running = true;
//}

//void LuaState::pause() {
//    GameState::setState(PAUSE);
//    running = false;
//}
