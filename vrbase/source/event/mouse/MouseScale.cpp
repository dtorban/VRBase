/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <vrbase/event/mouse/MouseScale.h>

#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace vrbase {

MouseScale::MouseScale(glm::dmat4* trans, MouseButton button) : _trans(trans), _buttonDown(false), _button(button) {

}

MouseScale::~MouseScale() {
}

void MouseScale::handleClick(MouseButton button, bool down,
		const glm::dvec2& pos) {
	if (button == _button)
	{
		_buttonDown = down;
		_lastPos = pos;
		_startPos = pos;
	}
	else if (button == MouseButton::SCROLL)
	{
		double scale =  1.0 + 0.1*(down ? 1.0 : -1.0);
		*(_trans) = glm::scale(glm::dmat4(1.0), glm::dvec3(scale, scale, scale))*(*(_trans));
	}
}

void MouseScale::handleMove(const glm::dvec2& pos) {
	if (_buttonDown)
	{
		double scale = _lastPos.y -  pos.y  + 1.0;
		*(_trans) = glm::scale(glm::dmat4(1.0), glm::dvec3(scale, scale, scale))*(*(_trans));

		_lastPos = pos;
	}
}

} /* namespace Spatialize */
