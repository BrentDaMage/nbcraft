/********************************************************************
	Minecraft: Pocket Edition - Decompilation Project
	Copyright (C) 2023 iProgramInCpp

	The following code is licensed under the BSD 1 clause license.
	SPDX-License-Identifier: BSD-1-Clause
 ********************************************************************/

#include "IInputHolder.hpp"
#include "Mouse.hpp"

IInputHolder::IInputHolder() :
	m_feedbackX(0),
	m_feedbackY(0),
	m_feedbackAlpha(0)
{
}

IInputHolder::~IInputHolder()
{
}

bool IInputHolder::allowPicking()
{
	m_feedbackX = float(Mouse::getX());
	m_feedbackY = float(Mouse::getY());
	return Mouse::getButtonState(MOUSE_BUTTON_LEFT);
}

void IInputHolder::setScreenSize(const ViewportSize& size)
{
	getMoveInput()->setScreenSize(size);
	getTurnInput()->setScreenSize(size);
	getBuildInput()->setScreenSize(size);
}

bool IInputHolder::allowsInputMethod(InputMethod::Type type) const
{
	return type == InputMethod::KEYBOARD || type == InputMethod::MOUSE;
}
