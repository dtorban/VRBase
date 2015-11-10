/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "vrbase/event/mouse/MouseListener.h"
#include "MVRCore/AbstractWindow.H"

namespace vrbase {

MouseListener::MouseListener() {
}

MouseListener::~MouseListener() {
}

bool stringCompare(const std::string& a, const char* b, int pos, int len)
{
	if (a.size() < len || pos >= a.size() || pos + len > a.size())
	{
		return false;
	}

	return a.compare(pos, len, b) == 0;
}

bool startsWith(const std::string& a, const char* b, int len)
{
	return stringCompare(a, b, 0, len);
}

bool stringCompare(const std::string& a, const std::string& b, int pos)
{
	return stringCompare(a, b.c_str(), pos, b.size());
}

bool startsWith(const std::string& a, const std::string& b)
{
	return stringCompare(a, b, 0);
}

void MouseListener::handleEvent(const MinVR::EventRef& event,
		double synchronizedTime) {

	if (startsWith(event->getName(), "mouse_", 6))
	{
		if (event->getName() == "mouse_scroll")
		{
			handleClick(MouseButton::SCROLL, event->get2DData().y > 0, event->get2DData());
			return;
		}

		MinVR::WindowRef window = event->getWindow();
		glm::dvec2 res(window->getWidth(), window->getHeight());
		glm::dvec2 pos = event->get2DData() / res;

		if (event->getName() == "mouse_pointer")
		{
			handleMove(pos);
		}
		else
		{
			MouseButton button;
			if (stringCompare(event->getName(), "left", 10, 4))
			{
				button = LEFT;
			}
			else if (stringCompare(event->getName(), "middle", 10, 6))
			{
				button = MIDDLE;
			}
			else if (stringCompare(event->getName(), "right", 10, 5))
			{
				button = RIGHT;
			}

			if (stringCompare(event->getName(), "up", event->getName().size()-2, 2))
			{
				handleClick(button, false, pos);
			}
			else
			{
				handleClick(button, true, pos);
			}
		}
	}
}

} /* namespace Spatialize */
