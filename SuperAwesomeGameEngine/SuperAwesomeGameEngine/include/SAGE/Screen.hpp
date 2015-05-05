// Screen.hpp

#ifndef __SAGE_SCREEN_HPP__
#define __SAGE_SCREEN_HPP__

// SAGE Includes
#include <SAGE\GeometryBatch.hpp>
#include <SAGE\SpriteBatch.hpp>

namespace SAGE
{
	class Screen
	{
		public:
			Screen();
			virtual ~Screen();

			bool IsActive() const;
			bool IsVisible() const;

			void SetActive(bool pActive);
			void SetVisible(bool pVisible);

			virtual int Initialize();
			virtual int Finalize();

			virtual int Update(float pDeltaTime) = 0;
			virtual int Render(SpriteBatch& pSpriteBatch) = 0;
			virtual int Render(GeometryBatch& pGeometryBatch) = 0;

		protected:
			bool mIsActive;
			bool mIsVisible;
	};
}

#endif