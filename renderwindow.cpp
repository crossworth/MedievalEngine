#include "renderwindow.h"

using namespace ME;

renderWindow::renderWindow() : mWindowInfomation(0,0,32,false,"Medieval Engine") {
   dbg = Debugger::getInstance();

}
Coord renderWindow::getCameraPosition(const std::string &name){
    Coord tmp;
    tmp.x = getCamera(name)->getCenter().x - getCamera(name)->getSize().x/2;
    tmp.y = getCamera(name)->getCenter().y - getCamera(name)->getSize().y/2;
    return tmp;
}

void renderWindow::createWindow(const windowInformation winInfos,int frameLimit, bool Sync){

    if ( isValidWindow(winInfos)){
        if ( winInfos.fullScreen)
            Window = new sf::RenderWindow(sf::VideoMode(winInfos.width,winInfos.height,winInfos.bitsPerPixel),winInfos.windowName,sf::Style::Fullscreen);
        else
            Window = new sf::RenderWindow(sf::VideoMode(winInfos.width,winInfos.height,winInfos.bitsPerPixel),winInfos.windowName,sf::Style::Close);

        Window->setFramerateLimit(frameLimit);
        Window->setVerticalSyncEnabled(Sync);
        dbg->log(WARNING,1, "A janela foi criada");

        mWindowInfomation.bitsPerPixel = winInfos.bitsPerPixel;
        mWindowInfomation.fullScreen = winInfos.fullScreen;
        mWindowInfomation.height = winInfos.height;
        mWindowInfomation.width = winInfos.width;
        mWindowInfomation.windowName = winInfos.windowName;
    }else{
        dbg->log(WARNING,1, "Informacoes de janela invalidas criando janela nas dimensoes da area de trabalho");
        Window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(),engine_name);
        Window->setFramerateLimit(frameLimit);
        Window->setVerticalSyncEnabled(Sync);

        mWindowInfomation.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
        mWindowInfomation.fullScreen = false;
        mWindowInfomation.height = sf::VideoMode::getDesktopMode().height;
        mWindowInfomation.width = sf::VideoMode::getDesktopMode().width;
        mWindowInfomation.windowName = engine_name;
    }
}

bool renderWindow::pollEvent(Event &evt){
    return Window->pollEvent(evt);
}

windowInformation renderWindow::getWindowInformation(){
    return mWindowInfomation;
}

bool renderWindow::isValidWindow(const windowInformation winInfos){
    // Only on fullScreen Mode
    if ( !winInfos.fullScreen)
        return true;

    sf::VideoMode tmp(winInfos.width,winInfos.height,winInfos.bitsPerPixel);
    return  tmp.isValid();
}


sf::RenderWindow * renderWindow::getRenderWindow(){
    return Window;
}

bool renderWindow::isOpen(){
    return Window->isOpen();
}

void renderWindow::clear(const sf::Color &c){
    Window->clear(c);
}

void renderWindow::display(){
    Window->display();
}

void renderWindow::draw(const sf::Drawable &draw){
    Window->draw(draw);
}

void renderWindow::close(){
    Window->close();
}

Camera* renderWindow::createCamera(const std::string &name,const FloatRect &rect){
    mCameras.insert( std::make_pair(name,new Camera(rect)));
    return mCameras[name];
}

Camera* renderWindow::createCamera(const std::string &name,const Camera &cam){
    mCameras.insert( std::make_pair(name,new Camera(cam)));
    return mCameras[name];
}


Camera * renderWindow::getCamera(const std::string &name){
    if ( mCameras.find(name) != mCameras.end())
        return mCameras[name];
    else{
        dbg->log(WARNING,1,("Camera ["+ name + "] nao encontrada").c_str());
        return new Camera();
    }
}

void renderWindow::setCamera(const std::string &name){
    if ( mCameras.find(name) != mCameras.end()){
        Window->setView(*mCameras[name]);
    }else{
        dbg->log(WARNING,1,("Camera ["+ name + "] nao encontrada").c_str());
    }
}


void renderWindow::setCamera(const Camera &cam){
    Window->setView(cam);
}



Camera* renderWindow::getDefaultCamera(){
    return (Camera*)&Window->getDefaultView();
}

renderWindow* renderWindow::getInstance(){
    static renderWindow * renderInstance = new renderWindow();
    return renderInstance;
}

renderWindow::~renderWindow(){
    std::map<std::string,Camera*>::iterator it = mCameras.begin();
    for(; it != mCameras.end();it++){
        delete it->second;
    }
    mCameras.clear();
}
