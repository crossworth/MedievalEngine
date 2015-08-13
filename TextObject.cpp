#include "TextObject.h"

using namespace ME;

TextObject::TextObject(const std::string &text, const int &textSize, const std::string &font) {
    Text tmpText;
    tmpText.setString(text);
    tmpText.setCharacterSize(textSize);

    if (font != "default") {
        if (assets->getFont(font) != nullptr) {
            tmpText.setFont(*assets->getFont(font));
        }
    }

    tmpText.setFont(*assets->loadFont("default", "state/main/font.ttf"));

    tmpText.setPosition(10.0f, 10.0f);
    tmpText.setColor(sf::Color::White);

    textReference = "text_" + TO::int_to_str(static_cast<int>(time(0)));
    assets->createText(textReference, tmpText);
}

void TextObject::draw() {
    if(_isVisible) {
        renderWindow->draw(*getObject());
    }
}

Text* TextObject::getObject() {
    if (assets->getText(textReference) != nullptr){
        return assets->getText(textReference);
    } else {
        dbg->log(CRITICAL, 1, ("[TextObject::getObject] Text Object " + textReference + " not found").c_str());
    }
}

void TextObject::update() {
    if(_isActive) {

    }
}

void TextObject::processEvents(Event evt) {

}
