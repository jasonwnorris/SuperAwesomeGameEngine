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
			Screen(ScreenManager* p_Manager);
			virtual ~Screen();

			bool IsActive() const;
			bool IsVisible() const;

			void SetActive(bool p_Active);
			void SetVisible(bool p_Visible);

			virtual int Initialize();
			virtual int Finalize();

			virtual int Pause();
			virtual int Resume();

			virtual int Update(float p_DeltaTime) = 0;
			virtual int Render(SpriteBatch& p_SpriteBatch) = 0;
			virtual int Render(GeometryBatch& p_GeometryBatch);

		protected:
			enum TransitionState
			{
				Off,
				On,
				In,
				Out,
			};

			ScreenManager* m_Manager;
			TransitionState m_TransitionState;
			bool m_IsActive;
			bool m_IsVisible;
	};
}

#endif
