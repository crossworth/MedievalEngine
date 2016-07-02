#ifndef MEDIEVALENGINE_GAMESTATE_GAMESTATE_H_
#define MEDIEVALENGINE_GAMESTATE_GAMESTATE_H_

#include "Helper/BasicTypes.h"

#include "Graphics/Window.h"
#include "Events/Event.h"

namespace ME {

class GameState {
public:
    /**
     * The ME::GameState::Status enum
     */
    enum Status {
        PLAYING,  ///< GameState playing status
        PAUSED, ///< GameState paused status
        ON_ENTER, ///< GameState on enter status
        ON_EXIT ///< GameState on exit status
    };

    GameState();
    virtual ~GameState();

    virtual void update(const uint64 &delta) = 0;
    virtual void handleEvents(Event &evt) = 0;
    virtual void draw(Window &window) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;

    inline bool isPlaying() {
        return mPlaying;
    }

    inline GameState::Status getCurrentStatus() {
        return mStatus;
    }

    inline bool updateOnPause() {
        return mUpdateOnPause;
    }

    inline void setUpdateOnPause(bool update) {
        mUpdateOnPause = update;
    }

    inline void setGameStatus(const GameState::Status &status) {
        mStatus = status;
    }

private:
    GameState::Status mStatus;
    bool mPlaying;
    bool mUpdateOnPause;
};

}

#endif // MEDIEVALENGINE_GAMESTATE_GAMESTATE_H_
