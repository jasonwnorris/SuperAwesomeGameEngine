// IGameComponent.cpp

// SAGE Includes
#include <SAGE/IGameComponent.hpp>

namespace SAGE
{
	IGameComponent::IGameComponent(Game* p_Game)
	{
		m_Game = p_Game;
	}

	IGameComponent::~IGameComponent()
	{
		m_Game = nullptr;
	}
}
