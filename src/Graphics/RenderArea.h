/*
* @Project MedievalEngine
* @Author: Pedro Henrique - system.pedrohenrique@gmail.com
* @Website: http://pedrohenrique.ninja
* @Date:   2016-06-04 01:32:41
*
*
* @File: RenderArea.cpp
* @Last Modified by:   Pedro Henrique
* @Last Modified time: 2016-06-04 01:32:41
*/



/*
*
* while(true) {
*   window.clear();
*
*	RenderArea rs;
*	rs.create(Rectangle(0, 0, 10, 10))
*   rs.setPosition(something)
*	rs.draw(background)	
*	rs.draw(text)
*
*	window.draw(rs)
*	window.clear()
* }
*
*
*
*/

#ifndef GRAPHICS_RENDERAREA_H_
#define GRAPHICS_RENDERAREA_H_

#include "Graphics/Drawable.h"


namespace ME {


class RenderArea : Drawable{
public:
	RenderArea();

	void reset(const Area& view);
	void setViewArea(const Area& view);

	void draw(Window& window);

	void setPosition(const Vect2f& pos);
	Vect2f getPosition();

	void setSize(const Vect2f& size);
	Vect2f getSize();
	void setScale(const Vect2f& scale);
	Vect2f getScale();

	void setColor(const Color& color);
	Color getColor();

	float getRotation();
	void setRotation(const float& angle);
	void rotate(const float& angle);

	Vect2f getOrigin();
	void setOrigin(const Vect2f& origin);

	Area getLocalBounds();
	Area getGlobalBounds();


	sf::View *getView();
private:
	Area mSize;
	sf::View mView;
};

}

#endif // GRAPHICS_RENDERAREA_H_