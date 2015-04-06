// Camera2D.cpp

// SAGE Includes
#include <SAGE\Camera2D.hpp>
// HGF Includes
#include <HGF\MathUtil.hpp>
#include <HGF\Matrix4.hpp>
// SDL Includes
#include <SDL2\SDL_opengl.h>

namespace SAGE
{
	Camera2D::Camera2D()
	{
		mPosition = HGF::Vector2::Zero;
		mRotation = 0.0f;
		mScale = HGF::Vector2::One;
	}

	Camera2D::~Camera2D()
	{
	}

	bool Camera2D::Initialize(int pWidth, int pHeight)
	{
		mWidth = pWidth;
		mHeight = pHeight;

		glViewport(0, 0, mWidth, mHeight);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, mWidth, mHeight, 0, 1, -1);

		return true;
	}

	HGF::Vector2 Camera2D::GetPosition() const
	{
		return mPosition;
	}

	float Camera2D::GetRotation() const
	{
		return mRotation;
	}

	HGF::Vector2 Camera2D::GetScale() const
	{
		return mScale;
	}

	int Camera2D::GetWidth() const
	{
		return mWidth;
	}

	int Camera2D::GetHeight() const
	{
		return mHeight;
	}

	void Camera2D::SetPosition(const HGF::Vector2& pPosition)
	{
		mPosition = pPosition;
	}

	void Camera2D::SetRotation(float pRotation)
	{
		mRotation = pRotation;
	}

	void Camera2D::SetScale(const HGF::Vector2& pScale)
	{
		mScale = pScale;
	}

	void Camera2D::Focus()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(mWidth / 2.0f, mHeight / 2.0f, 0.0f);
		glScalef(mScale.X, mScale.Y, 1.0f);
		glRotatef(-HGF::MathUtil::ToDegrees(mRotation), 0, 0, 1);
		glTranslatef(-mPosition.X, -mPosition.Y, 0.0f);
	}

	void Camera2D::Reset()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	HGF::Vector2 Camera2D::ScreenToWorld(const HGF::Vector2& pScreenPosition) const
	{
		/*
		Matrix4 modelMatrix = Matrix4::FromScale(1.0f / Transform.Scale.X, 1.0f / Transform.Scale.Y, 1.0f)
		* Matrix4::FromPitchYawRoll(0.0f, 0.0f, Transform.Rotation)
		* Matrix4::FromTranslation(Transform.Position.X, Transform.Position.Y, 0.0f);

		Vector3f temp(pScreenPosition.X - mViewWidth / 2.0f, pScreenPosition.Y - mViewHeight / 2.0f, 0.0f);
		temp = modelMatrix * temp;

		return Vector2f(temp.X, temp.Y);
		*/

		HGF::Vector2 retVal(pScreenPosition.X - mWidth / 2.0f, pScreenPosition.Y - mHeight / 2.0f);
		retVal /= mScale.X;
		float x = retVal.X;
		float y = retVal.Y;
		float cosA = cosf(mRotation);
		float sinA = sinf(mRotation);
		retVal.X = x * cosA - y * sinA;
		retVal.Y = x * sinA + y * cosA;
		retVal += mPosition;

		return retVal;
	}

	HGF::Vector2 Camera2D::WorldToScreen(const HGF::Vector2& pWorldPosition) const
	{
		return HGF::Vector2::Zero;
	}

	void Camera2D::Translate(const HGF::Vector2& pTranslation)
	{
		mPosition += pTranslation;
	}

	void Camera2D::Rotate(float pRotation)
	{
		mRotation += pRotation;
	}

	void Camera2D::Scale(const HGF::Vector2& pScale)
	{
		mScale += pScale;
	}
}