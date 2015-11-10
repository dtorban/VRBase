/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef MOUSELISTENER_H_
#define MOUSELISTENER_H_

#include "vrbase/EventListener.h"
#include <glm/glm.hpp>

namespace vrbase {

class MouseListener : public EventListener {
public:
	enum MouseButton {
		LEFT = 0,
		MIDDLE = 1,
		RIGHT = 2
	};

	MouseListener();
	virtual ~MouseListener();

	void handleEvent(const MinVR::EventRef &event, double synchronizedTime);

	virtual void handleClick(MouseButton button, bool down, const glm::dvec2& pos) = 0;
	virtual void handleMove(const glm::dvec2& pos) = 0;
};

} /* namespace Spatialize */

#endif /* MOUSELISTENER_H_ */
