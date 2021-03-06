/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef MOUSETRACKBALL_H_
#define MOUSETRACKBALL_H_

#include "vrbase/event/mouse/MouseListener.h"

namespace vrbase {

class MouseTrackball : public MouseListener {
public:
	MouseTrackball(glm::dmat4* trans, MouseButton button = MouseButton::LEFT);
	virtual ~MouseTrackball();

	void handleClick(MouseButton button, bool down, const glm::dvec2& pos);
	void handleMove(const glm::dvec2& pos);

private:
	MouseButton _button;
	glm::dmat4* _trans;
	bool _buttonDown;
	glm::dvec2 _lastPos;
};

} /* namespace Spatialize */

#endif /* MOUSETRANSLATOR_H_ */
