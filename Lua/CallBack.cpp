//#include "CallBack.h"

//using namespace ME;

//CallBack::CallBack(const std::string &functionName, const float &time) {
//    mFunctioName = functionName;
//    mTime        = time;
//    mClock.restart();
//    mExecute = false;
//}

//std::string CallBack::getFunctionName() {
//    return mFunctioName;
//}

//void CallBack::update() {
//    sf::Time tmpTime = mClock.getElapsedTime();
//    if (tmpTime.asSeconds() >= mTime) {
//        mExecute = true;
//    }
//}

//bool CallBack::execute() {
//    return mExecute;
//}
