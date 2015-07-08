// Camera2D.cpp

// SAGE Includes
#include <SAGE\Camera2D.hpp>
// HGF Includes
#include <HGF\MathUtil.hpp>
#include <HGF\Matrix4.hpp>

namespace SAGE
{
	const Camera2D Camera2D::DefaultCamera;
	int Camera2D::DefaultWidth = 1280;
	int Camera2D::DefaultHeight = 720;

	Camera2D::Camera2D()
	{
		mPosition = HGF::Vector2::Zero;
		mRotation = 0.0f;
		mScale = HGF::Vector2::One;
		mWidth = DefaultWidth;
		mHeight = DefaultHeight;
	}

	Camera2D::~Camera2D()
	{
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

	glm::mat4 Camera2D::GetProjectionMatrix(View pView) const
	{
		switch (pView)
		{
			default:
			case View::Orthographic:
				return glm::ortho(0.0f, (float)mWidth, (float)mHeight, 0.0f, 1.0f, -1.0f);
			case View::Perspective:
				return glm::perspective(45.0f, (float)mWidth / (float)mHeight, 0.1f, 1000.0f);
		}
	}

	glm::mat4 Camera2D::GetModelViewMatrix() const
	{
		glm::mat4 modelViewMatrix;
		modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3((float)mWidth / 2.0f, (float)mHeight / 2.0f, 0.0f));
		modelViewMatrix = glm::scale(modelViewMatrix, glm::vec3(mScale.X, mScale.Y, 1.0f));
		modelViewMatrix = glm::rotate(modelViewMatrix, mRotation, glm::vec3(0.0f, 0.0f, 1.0f));
		modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(-mPosition.X, -mPosition.Y, 0.0f));

		return modelViewMatrix;
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

	void Camera2D::SetTransformation(const HGF::Vector2& pPosition, float pRotation, const HGF::Vector2& pScale)
	{
		mPosition = pPosition;
		mRotation = pRotation;
		mScale = pScale;
	}

	void Camera2D::SetWidth(int pWidth)
	{
		mWidth = pWidth;
	}

	void Camera2D::SetHeight(int pHeight)
	{
		mHeight = pHeight;
	}

	void Camera2D::SetDimensions(int pWidth, int pHeight)
	{
		mWidth = pWidth;
		mHeight = pHeight;
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

	void Camera2D::ScreenToWorld(const HGF::Vector2& pScreenPosition, HGF::Vector2& pWorldPosition) const
	{
	}

	void Camera2D::WorldToScreen(const HGF::Vector2& pWorldPosition, HGF::Vector2& pScreenPosition) const
	{
	}
}