/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp

	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "TouchInputHolder.hpp"
#include "Multitouch.hpp"
#include "client/app/Minecraft.hpp"
#include "client/options/Options.hpp"

TouchInputHolder::TouchInputHolder(Minecraft* pMinecraft, Options* pOptions) :
	m_touchScreenInput(pMinecraft, pOptions),
	m_unifiedTurnBuild(2, Minecraft::GetViewportSize(), 200.0f, 1.05f, this),
	m_pMinecraft(pMinecraft)
{
}

bool TouchInputHolder::allowPicking()
{
	const int* ids;
	int count = Multitouch::getActivePointerIds(&ids);

	for (int i = 0; i < count; ++i)
	{
		int finger = ids[i];
		float x = float(Multitouch::getX(finger));
		float y = float(Multitouch::getY(finger));
		if (m_unifiedTurnBuild.isInsideArea(x, y))
		{
			m_feedbackX = x;
			m_feedbackY = y;
			return true;
		}
	}

	return false;
}

bool TouchInputHolder::allowsInputMethod(InputMethod::Type type) const
{
	return type == InputMethod::TOUCHSCREEN;
}

IMoveInput* TouchInputHolder::getMoveInput()
{
	return &m_touchScreenInput;
}

ITurnInput* TouchInputHolder::getTurnInput()
{
	return &m_unifiedTurnBuild;
}

IBuildInput* TouchInputHolder::getBuildInput()
{
	return &m_unifiedTurnBuild;
}

void TouchInputHolder::setScreenSize(const ViewportSize& size)
{
	m_touchScreenInput.setScreenSize(size);
	m_unifiedTurnBuild.field_40 = m_touchScreenInput.getRectangleArea();
	m_unifiedTurnBuild.m_sneakExclude = m_touchScreenInput.getSneakArea();
	m_unifiedTurnBuild.field_58 = m_pMinecraft->m_pGui->getRectangleArea(false);
	m_unifiedTurnBuild.setScreenSize(size);
#ifdef ENH_NEW_TOUCH_CONTROLS
	m_touchScreenInput.setSneakExcludeRef(&m_unifiedTurnBuild.m_sneakExclude);
#endif
}
