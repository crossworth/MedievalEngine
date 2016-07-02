
GameState {
    isRunning;
    onState = Entered, Exit, Running, Pause

    GameState(GameStateManager) {

    }

    pause()
    resume()

    update()
    draw()
    handleEvents() <-- execute lua scripts

    onEntered()
    onExit()
}

GameStateManager {
    push
    pop
    getCurrent()

    update
    draw
    handleEvents
}

LoadingScreen {

    LoadingScreen(GameStateManager) {
        mGameStateManager = GameStateManager;
    }

    onExit() {
        mGameStateManager->push(new MenuScreen());
    }


    onEntered() {
        isRunning = true
    }
}


mGameStates.push(new LoadingScreen(mGameStates));

while(Running) {

    mGameStates->update();
    mGameStates->draw();
    mGameStates->handleEvents();

}







