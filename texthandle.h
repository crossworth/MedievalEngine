#ifndef TEXTHANDLE_H
#define TEXTHANDLE_H
#include "Config.h"
#include "AssetsManager.h"
#include "RenderWindow.h"

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
