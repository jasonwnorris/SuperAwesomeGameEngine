// Camera2D.hpp

#ifndef __SAGE_CAMERA2D_HPP__
#define __SAGE_CAMERA2D_HPP__

// HGF Includes
#include <HGF\Vector2.hpp>

namespace SAGE
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		bool Initialize(int pWidth, int pHeight);

		HGF::Vector2 GetPosition() const;
		float GetRotation() const;
		HGF::Vector2 GetScale() const;
		int GetWidth() const;
		int GetHeight() const;

		void SetPosition(const HGF::Vector2& pPosition);
		void SetRotation(float pRotation);
		void SetScale(const HGF::Vector2& pScale);

		void Focus();
		void Reset();
		HGF::Vector2 ScreenToWorld(const HGF::Vector2& pScreenPosition) const;
		HGF::Vector2 WorldToScreen(const HGF::Vector2& pWorldPosition) const;

		void Translate(const HGF::Vector2& pTranslation);
		void Rotate(float pRotation);
		void Scale(const HGF::Vector2& pScale);

	private:
		HGF::Vector2 mPosition;
		float mRotation;
		HGF::Vector2 mScale;
		int mWidth;
		int mHeight;
	};
}

#endif