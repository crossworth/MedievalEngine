#ifndef CALLBACK_H
#define CALLBACK_H
#include "config.h"

class CallBack {
public:
    CallBack(const std::string &functionName, const float &time);
    void update();
    bool execute();

    std::string getFunctionName();

private:
    std::string mFunctioName;
    float mTime;
    sf::Clock mClock;
    bool mExecute;

};

#endif // CALLBACK_H
