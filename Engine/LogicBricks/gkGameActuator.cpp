/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2013 Charlie C.

    Contributor(s): Thomas Trocha(dertom)
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "gkGameActuator.h"
#include "gkEngine.h"
#include "gkGameObject.h"
#include "gkScene.h"



gkGameActuator::gkGameActuator(gkGameObject* object, gkLogicLink* link, const gkString& name)
	:   gkLogicActuator(object, link, name), m_mode(-1), m_otherGame("")

{
}


gkGameActuator::~gkGameActuator()
{
}


gkLogicBrick* gkGameActuator::clone(gkLogicLink* link, gkGameObject* dest)
{
	gkGameActuator* act = new gkGameActuator(*this);
	act->cloneImpl(link, dest);
	return act;
}


void gkGameActuator::execute(void)
{
	switch (m_mode)
	{
	case GM_QUIT:
		{
			gkEngine::getSingleton().requestExit();
			break;
		} break;
	case GM_RESTART:
		{
			m_object->getOwner()->reinstance(true);
			break;
		} break;
	default:
		printf("todo!\n");
		break;
	}
	setPulse(BM_OFF);

}
