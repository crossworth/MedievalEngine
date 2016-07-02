/*
* @Project MedievalEngine
* @Author: Pedro Henrique - system.pedrohenrique@gmail.com
* @Website: http://pedrohenrique.ninja
* @Date:   2016-06-04 01:32:41
*
*
* @File: RenderArea.cpp
* @Last Modified by:   Pedro Henrique
* @Last Modified time: 2016-06-04 11:06:34
*/

// TODO(Pedro): implement the rest of this

#include "RenderArea.h"

using namespace ME;


RenderArea::RenderArea() { 

} 

void RenderArea::reset(const Area& view) { 
	mView.reset(sf::FloatRect(view.left, view.top, view.width, view.height));
}

sf::View *RenderArea::getView() {
	return &mView;
}

void RenderArea::setViewArea(const Area& view) { 
	mView.setViewport(sf::FloatRect(view.left, view.top, view.width, view.height));
}

void RenderArea::draw(Window& window) { 

}

void RenderArea::setPosition(const Vect2f& pos) { 

}

Vect2f RenderArea::getPosition() { 
	Vect2f position(0.0f, 0.0f);

	return position;
}

void RenderArea::setSize(const Vect2f& size) { 

}

Vect2f RenderArea::getSize() { 
	Vect2f size(0.0f, 0.0f);
	
	return size;
}

void RenderArea::setScale(const Vect2f& scale) { 

}

Vect2f RenderArea::getScale() { 
	Vect2f scale(0.0f, 0.0f);
	
	return scale;
}

void RenderArea::setColor(const Color& color) { 

}

Color RenderArea::getColor() { 
	return Color(0, 0, 0, 0);
}

float RenderArea::getRotation() { 
	return 0.0f;
}

void RenderArea::setRotation(const float& angle) { 

}

void RenderArea::rotate(const float& angle) { 

}

Vect2f RenderArea::getOrigin() {
	Vect2f origin(0.0f, 0.0f);
	
	return origin;
}

void RenderArea::setOrigin(const Vect2f& origin) { 

}

Area RenderArea::getLocalBounds() { 
	Area bounds;
	return bounds;
}

Area RenderArea::getGlobalBounds() { 
	Area bounds;
	return bounds;
}
