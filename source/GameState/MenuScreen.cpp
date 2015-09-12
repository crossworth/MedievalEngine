#include "MenuScreen.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

MenuScreen::MenuScreen() {
    LOG << Log::VERBOSE << "[MenuScreen::MenuScreen]" << std::endl;
}

// NOTE(Pedro) TODO(Pedro)
// Test if we change the resolution on runtime the game can still positionate all
// the objects in the right position and size's
// maybe put all the Size specific things on the init method
// or something like that
void MenuScreen::create() {
    ProfileBlock();
    
    LOG << Log::VERBOSE << "[MenuScreen::create]" << std::endl;

    ResourceID bgTXT = mResources->loadTexture("menu/bg_menu.png");
    bgID             = mResources->createSprite(bgTXT);

    ResourceID bgOptionsTXT = mResources->loadTexture("menu/bg_options.png");
    bgOptionsID             = mResources->createSprite(bgOptionsTXT);

    ResourceID logoTXT = mResources->loadTexture("menu/title_menu.png");
    logoID             = mResources->createSprite(logoTXT);

    Sprite* logoSPT      = mResources->getResource<Sprite>(logoID);
    Sprite* bgSPT        = mResources->getResource<Sprite>(bgID);
    Sprite* bgOptionsSPT = mResources->getResource<Sprite>(bgOptionsID);

    // Set the background image to fullScreen
    Window::setSizeFullScreen(bgSPT);
    // Set the menu options background to the relative size
    Window::setRelative(bgOptionsSPT);
    // Do the same for the logo
    Window::setRelative(logoSPT);
    // Set the menu options background to the right center position
    Window::setPosition(bgOptionsSPT, Window::Position::RIGHT, Window::Position::CENTER);
    // Set 11% of padding on top and bottom
    logoSPT->setPadding(0.11f, Padding::TOP);
    logoSPT->setPadding(0.11f, Padding::BOTTOM);
    // Set the logo to the center top of the menu options background
    Window::setPosition(logoSPT, Window::Position::CENTER, Window::Position::TOP, bgOptionsSPT);


    int fontSize = Window::fontSize(0.5f);

    // Create the new Game button Text Widget
    mNewGame = TextWidgetPtr(new TextWidget(Strings::get("new_game"), fontSize, Vect2f(0.f, 0.f), mEngine->GAME_FONT_ID));
    // Add the Widget to the GUI
    mGUI.addWidget("new_game_btn", mNewGame);

    // Set 25% padding top of the first menu Object
    mNewGame->setPadding(0.25f, Padding::TOP);
    mNewGame->setColor(Color::BLACK);
    // And We finally set the position of the Widget
    Window::setPosition(mNewGame, Window::Position::CENTER, Window::Position::TOP, bgOptionsSPT);



    // Create the new Game button Text Widget
    mContinue = TextWidgetPtr(new TextWidget(Strings::get("continue"), fontSize, Vect2f(0.f, 0.f), mEngine->GAME_FONT_ID));
    // Add the Widget to the GUI
    mGUI.addWidget("continue_btn", mContinue);

    // Set 25% padding top of the first menu Object
    mContinue->setPadding(0.35f, Padding::TOP);
    mContinue->setColor(Color::BLACK);
    // And We finally set the position of the Widget
    Window::setPosition(mContinue, Window::Position::CENTER, Window::Position::TOP, bgOptionsSPT);



    // Create the new Game button Text Widget
    mMultiplayer = TextWidgetPtr(new TextWidget(Strings::get("multiplayer"), fontSize, Vect2f(0.f, 0.f), mEngine->GAME_FONT_ID));
    // Add the Widget to the GUI
    mGUI.addWidget("multiplayer_btn", mMultiplayer);

    // Set 25% padding top of the first menu Object
    mMultiplayer->setPadding(0.45f, Padding::TOP);
    mMultiplayer->setColor(Color::BLACK);
    // And We finally set the position of the Widget
    Window::setPosition(mMultiplayer, Window::Position::CENTER, Window::Position::TOP, bgOptionsSPT);



    // Create the new Game button Text Widget
    mOptions = TextWidgetPtr(new TextWidget(Strings::get("options"), fontSize, Vect2f(0.f, 0.f), mEngine->GAME_FONT_ID));
    // Add the Widget to the GUI
    mGUI.addWidget("options_btn", mOptions);

    // Set 25% padding top of the first menu Object
    mOptions->setPadding(0.55f, Padding::TOP);
    mOptions->setColor(Color::BLACK);
    // And We finally set the position of the Widget
    Window::setPosition(mOptions, Window::Position::CENTER, Window::Position::TOP, bgOptionsSPT);


    GUIEventPtr optionsEvent = GUIEventPtr(new GUIEvent());

    // NOTE(Pedro): Test this
    // For some reason we could not pass this to the lambda function
    // somehow it don't work as expect
    // try something like this->bgOptionsSPT since it's obvious on the scope of this
    optionsEvent->setOnClick([=](Widget* widget) {
        Window::setSizeFullScreen(bgOptionsSPT);
        Window::setPosition(bgOptionsSPT, Window::Position::CENTER, Window::Position::TOP);
    });

    optionsEvent->setOnMouseOut([this](Widget* widget) {
        mOptions->setColor(Color::BLACK);
    });

    optionsEvent->setOnMouseOver([this](Widget* widget) {
        mOptions->setColor(Color::DODGER_BLUE);
    });

    mOptions->addEventHandle(optionsEvent);




    // Create the new Game button Text Widget
    mExit = TextWidgetPtr(new TextWidget(Strings::get("exit"), fontSize, Vect2f(0.f, 0.f), mEngine->GAME_FONT_ID));
    // Add the Widget to the GUI
    mGUI.addWidget("exit_btn", mExit);

    // Set 25% padding top of the first menu Object
    mExit->setPadding(0.65f, Padding::TOP);
    mExit->setColor(Color::BLACK);
    // And We finally set the position of the Widget
    Window::setPosition(mExit, Window::Position::CENTER, Window::Position::TOP, bgOptionsSPT);

    GUIEventPtr exitEvent = GUIEventPtr(new GUIEvent());

    exitEvent->setOnClick([this](Widget* widget) {
        // TODO(Pedro): Cleanup everything on the engine close event
        // including all the GUI releated stuff and game state
        // maybe do some exit animation
        this->mEngine->close();
    });

    exitEvent->setOnMouseOut([this](Widget* widget) {
        mExit->setColor(Color::BLACK);
    });

    exitEvent->setOnMouseOver([this](Widget* widget) {
        mExit->setColor(Color::DODGER_BLUE);
    });

    mExit->addEventHandle(exitEvent);


    mFadeTime = 500;

    shader = new Shader("blur.frag", Shader::Type::FRAGMENT);
    shader->setParameter("blur_radius", 0.025f);

}

void MenuScreen::init() {
    ProfileBlock();

    // LOG << Log::VERBOSE << "[MenuScreen::init]" << std::endl;

    mGUI.addEffect(new Strobe(10000, 0.6f, -1));

    // mNewGame->addEffect(shader);
    mContinue->addEffect(new Fade(mFadeTime, Fade::Type::FADEIN));
    mMultiplayer->addEffect(new Fade(mFadeTime, Fade::Type::FADEIN));
    mOptions->addEffect(new Fade(mFadeTime, Fade::Type::FADEIN));
    mExit->addEffect(new Fade(mFadeTime, Fade::Type::FADEIN));

    mResources->getResource<Sprite>(bgID)->addEffect(new Fade(mFadeTime, Fade::Type::FADEIN));
    mResources->getResource<Sprite>(logoID)->addEffect(new Fade(mFadeTime, Fade::Type::FADEIN));
    mResources->getResource<Sprite>(bgOptionsID)->addEffect(new Fade(mFadeTime, Fade::Type::FADEIN, [this] (void) {
        this->setCurrentStatus(GameState::Status::ON_PLAYING);
    }));
}

void MenuScreen::onEnable(Window &window) {
    window.draw(mResources->getResource<Sprite>(bgID));
    window.draw(mResources->getResource<Sprite>(bgOptionsID));
    window.draw(mResources->getResource<Sprite>(logoID));
    window.draw(&mGUI);
}

void MenuScreen::onDisable(Window &window) {

}

void MenuScreen::onPlaying(Window &window) {
    ProfileBlock();

    window.draw(mResources->getResource<Sprite>(bgID));
    window.draw(mResources->getResource<Sprite>(bgOptionsID));
    window.draw(mResources->getResource<Sprite>(logoID));
    window.draw(&mGUI);
}

void MenuScreen::update() {
    ProfileBlock();

    mGUI.update();
}

void MenuScreen::handleEvents(Event& evt) {
    ProfileBlock();

    mGUI.handleEvents(evt);
    if(evt.type == Event::Closed) {
        mEngine->close();
    }
}


MenuScreen::~MenuScreen() {
    // TODO(pedro): Dealocate all the memory used

}
