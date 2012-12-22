#ifndef TEXTHANDLE_H
#define TEXTHANDLE_H
#include "engine_config.h"
#include "assetsmanager.h"
#include "renderwindow.h"

namespace ME{

class TextHandle
{
public:
    static void TextShadow(const std::string &fileName,sf::RenderWindow &mWindow,const sf::Color &colorShadow,const sf::Vector2f &pos);
    //static std::string ask(const std::string &title,const std::string &text);
protected:
    TextHandle();
};

}

#endif // TEXTHANDLE_H
