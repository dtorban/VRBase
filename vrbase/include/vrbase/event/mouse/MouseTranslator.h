/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef MOUSETRANSLATOR_H_
#define MOUSETRANSLATOR_H_

#include "vrbase/event/mouse/MouseListener.h"

namespace vrbase {

class MouseTranslator : public MouseListener {
public:
	MouseTranslator(glm::dmat4* trans);
	virtual ~MouseTranslator();

	void handleClick(MouseButton button, bool down, const glm::dvec2& pos);
	void handleMove(const glm::dvec2& pos);

private:
	glm::dmat4* _trans;
	bool _buttonDown;
	glm::dvec2 _lastPos;
};

} /* namespace Spatialize */

#endif /* MOUSETRANSLATOR_H_ */
