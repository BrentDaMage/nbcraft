#include "IBuildInput.hpp"

IBuildInput::~IBuildInput()
{
}

void IBuildInput::setScreenSize(const ViewportSize& size)
{
}

bool IBuildInput::tickBuild(Player* pPlayer, BuildActionIntention* pIntention)
{
	return false;
}
