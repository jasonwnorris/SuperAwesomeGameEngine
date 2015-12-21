// IGameComponent.hpp

#ifndef __SAGE_IGAMECOMPONENT_HPP__
#define __SAGE_IGAMECOMPONENT_HPP__

namespace SAGE
{
	class Game;
	class IGameComponent
	{
		public:
			IGameComponent(Game* p_Game);
			~IGameComponent();

			Game* GetGame() const;

		private:
			Game* m_Game;
	};
}

#endif
