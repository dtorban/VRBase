/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <vrbase/event/mouse/MouseTrackball.h>

#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace vrbase {

MouseTrackball::MouseTrackball(glm::dmat4* trans, MouseButton button) : _trans(trans), _buttonDown(false), _button(button) {

}

MouseTrackball::~MouseTrackball() {
}

void MouseTrackball::handleClick(MouseButton button, bool down,
		const glm::dvec2& pos) {
	if (button == _button)
	{
		_buttonDown = down;
		_lastPos = pos;
	}
}

void MouseTrackball::handleMove(const glm::dvec2& pos) {
	if (_buttonDown)
	{
		glm::dvec2 move = (_lastPos - pos);
		glm::dvec2 norm = glm::normalize(move);
		*(_trans) =glm::rotate(glm::dmat4(1.0), -glm::length(move)*360.0, glm::dvec3(norm.y, norm.x, 0.0))*(*(_trans));
		_lastPos = pos;
	}
}

} /* namespace Spatialize */
