/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <vrbase/event/mouse/MouseTranslator.h>

#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace vrbase {

MouseTranslator::MouseTranslator(glm::dmat4* trans) : _trans(trans), _buttonDown(false) {

}

MouseTranslator::~MouseTranslator() {
}

void MouseTranslator::handleClick(MouseButton button, bool down,
		const glm::dvec2& pos) {
	if (button == MouseButton::LEFT)
	{
		_buttonDown = down;
		_lastPos = pos;
	}
}

void MouseTranslator::handleMove(const glm::dvec2& pos) {
	if (_buttonDown)
	{
		glm::dvec2 move = (_lastPos - pos);
		*(_trans) = glm::translate(glm::dmat4(1.0f), glm::dvec3(-move.x, move.y, 0.0f))*(*(_trans));
		_lastPos = pos;
	}
}

} /* namespace Spatialize */
