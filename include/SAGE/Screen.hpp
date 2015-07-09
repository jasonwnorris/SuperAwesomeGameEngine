// Screen.hpp

#ifndef __SAGE_SCREEN_HPP__
#define __SAGE_SCREEN_HPP__

// SAGE Includes
#include <SAGE\GeometryBatch.hpp>
#include <SAGE\SpriteBatch.hpp>

namespace SAGE
{
	class ScreenManager;
	class Screen
	{
		public:
			Screen(ScreenManager* pManager);
			virtual ~Screen();

			bool IsActive() const;
			bool IsVisible() const;

			void SetActive(bool pActive);
			void SetVisible(bool pVisible);

			virtual int Initialize();
			virtual int Finalize();

			virtual int Pause();
			virtual int Resume();

			virtual int Update(float pDeltaTime) = 0;
			virtual int Render(SpriteBatch& pSpriteBatch) = 0;
			virtual int Render(GeometryBatch& pGeometryBatch);

		protected:
			enum TransitionState
			{
				Off,
				On,
				In,
				Out,
			};

			ScreenManager* mManager;
			TransitionState mTransitionState;
			bool mIsActive;
			bool mIsVisible;
	};
}

#endif
