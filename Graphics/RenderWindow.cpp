//#include "RenderWindow.h"

//using namespace ME;

//RenderWindow::RenderWindow() : mWindowInfomation(ENGINE_DEFAULTS::WIDTH_WINDOW, ENGINE_DEFAULTS::HEIGHT_WINDOW, ENGINE_DEFAULTS::BITS_PER_PIXEL_WINDOW, ENGINE_DEFAULTS::FULLSCREEN_WINDOW, ENGINE_DEFAULTS::ENGINE_NAME) {
//   dbg = Debugger::getInstance();

//}

//Coord RenderWindow::getCameraPosition(const std::string &name) {
//    Coord tmp;
//    tmp.x = getCamera(name)->getCenter().x - getCamera(name)->getSize().x/2;
//    tmp.y = getCamera(name)->getCenter().y - getCamera(name)->getSize().y/2;
//    return tmp;
//}

//void RenderWindow::createWindow(const windowInformation winInfos, int frameLimit, bool vsync) {
//    sf::ContextSettings settings;
//    settings.antialiasingLevel = 8;

//    if (winInfos.fullScreen == true && isValidWindow(winInfos)) {
//        Window = new sf::RenderWindow(sf::VideoMode(winInfos.width, winInfos.height, winInfos.bitsPerPixel), winInfos.windowName, sf::Style::Fullscreen, settings);
//    } else {
//        Window = new sf::RenderWindow(sf::VideoMode(winInfos.width, winInfos.height, winInfos.bitsPerPixel), winInfos.windowName, sf::Style::Close, settings);
//    }

//    Window->setFramerateLimit(frameLimit);
//    Window->setVerticalSyncEnabled(vsync);
//    // Deixa tela preta enquanto carrega o resto dos recursos e inicia os sistemas
//    Window->clear();
//    Window->display();

//    mWindowInfomation.bitsPerPixel = winInfos.bitsPerPixel;
//    mWindowInfomation.fullScreen   = winInfos.fullScreen;
//    mWindowInfomation.height       = winInfos.height;
//    mWindowInfomation.width        = winInfos.width;
//    mWindowInfomation.windowName   = winInfos.windowName;

//    dbg->log(VERBOSE, 1, "[renderWindow::createWindow] Window created");

//}

//void RenderWindow::setIcon(int width, int height, Image icon) {
//    Window->setIcon(width, height, icon.getPixelsPtr());
//}

//bool RenderWindow::pollEvent(Event &evt) {
//    return Window->pollEvent(evt);
//}

//windowInformation RenderWindow::getWindowInformation() {
//    return mWindowInfomation;
//}

//bool RenderWindow::isValidWindow(const windowInformation winInfos) {

//    // Funciona somente em modo FullScreen
//    if (!winInfos.fullScreen)
//        return true;

//    sf::VideoMode tmp(winInfos.width, winInfos.height, winInfos.bitsPerPixel);
//    return  tmp.isValid();
//}

//sf::RenderWindow * RenderWindow::getRenderWindow() {
//    return Window;
//}

//bool RenderWindow::isOpen() {
//    return Window->isOpen();
//}

//void RenderWindow::clear(const sf::Color &color) {
//    Window->clear(color);
//}

//void RenderWindow::display() {
//    Window->display();
//}

//void RenderWindow::draw(const sf::Drawable &draw) {
//    Window->draw(draw);
//}

//void RenderWindow::close() {
//    Window->close();
//}

//float RenderWindow::getTime() {
//    sf::Time seconds = mClock.getElapsedTime();
//    return seconds.asSeconds();
//}

//void RenderWindow::restartTime() {
//    mClock.restart();
//}

//Camera* RenderWindow::createCamera(const std::string &name, const FloatRect &rect) {
//    mCameras.insert(std::make_pair(name, new Camera(rect)));
//    return mCameras[name];
//}

//Camera* RenderWindow::createCamera(const std::string &name, const Camera &cam) {
//    mCameras.insert( std::make_pair(name, new Camera(cam)));
//    return mCameras[name];
//}

//Camera* RenderWindow::getCamera(const std::string &name) {
//    if (name == "default") {
//        return  getDefaultCamera();
//    } else if (mCameras.find(name) != mCameras.end()) {
//        return mCameras[name];
//    } else {
//        dbg->log(WARNING, 1, ("[renderWindow::getCamera] Camera ("+ name + ") not found").c_str());
//        return nullptr;
//    }
//}

//void RenderWindow::setCamera(const std::string &name) {
//    if (mCameras.find(name) != mCameras.end()) {
//        Window->setView(*mCameras[name]);
//    } else {
//        dbg->log(WARNING, 1,("[renderWindow::setCamera] Camera ("+ name + ") not found").c_str());
//    }
//}

//void RenderWindow::setCamera(const Camera &cam) {
//    Window->setView(cam);
//}

//Camera* RenderWindow::getDefaultCamera() {
//    return (Camera*)&Window->getDefaultView();
//}

//RenderWindow* RenderWindow::instance = nullptr;

//RenderWindow* RenderWindow::getInstance() {
//    if (instance == nullptr) {
//        instance = new RenderWindow();
//    }
//    return instance;
//}

//RenderWindow::~RenderWindow() {
//    std::map<std::string,Camera*>::iterator it = mCameras.begin();
//    for(; it != mCameras.end();it++) {
//        delete it->second;
//    }
//    mCameras.clear();
//}
