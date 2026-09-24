#pragma once

#include "BuildActionIntention.hpp"
#include "client/gui/ViewportSize.hpp"

class Player;

class IBuildInput
{
public:
	virtual ~IBuildInput();
	virtual void setScreenSize(const ViewportSize& size);
	virtual bool tickBuild(Player*, BuildActionIntention*);
};

