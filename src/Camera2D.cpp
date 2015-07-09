// Camera2D.cpp

// SAGE Includes
#include <SAGE\Camera2D.hpp>
// SAGE Includes
#include <SAGE\MathUtil.hpp>
#include <SAGE\Matrix4.hpp>

namespace SAGE
{
	const Camera2D Camera2D::DefaultCamera;
	int Camera2D::DefaultWidth = 1280;
	int Camera2D::DefaultHeight = 720;

	Camera2D::Camera2D()
	{
		mPosition = Vector2::Zero;
		mRotation = 0.0f;
		mScale = Vector2::One;
		mWidth = DefaultWidth;
		mHeight = DefaultHeight;
	}

	Camera2D::~Camera2D()
	{
	}

	Vector2 Camera2D::GetPosition() const
	{
		return mPosition;
	}

	float Camera2D::GetRotation() const
	{
		return mRotation;
	}

	Vector2 Camera2D::GetScale() const
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

	void Camera2D::SetPosition(const Vector2& pPosition)
	{
		mPosition = pPosition;
	}

	void Camera2D::SetRotation(float pRotation)
	{
		mRotation = pRotation;
	}

	void Camera2D::SetScale(const Vector2& pScale)
	{
		mScale = pScale;
	}

	void Camera2D::SetTransformation(const Vector2& pPosition, float pRotation, const Vector2& pScale)
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

	void Camera2D::Translate(const Vector2& pTranslation)
	{
		mPosition += pTranslation;
	}

	void Camera2D::Rotate(float pRotation)
	{
		mRotation += pRotation;
	}

	void Camera2D::Scale(const Vector2& pScale)
	{
		mScale += pScale;
	}

	void Camera2D::ScreenToWorld(const Vector2& pScreenPosition, Vector2& pWorldPosition) const
	{
	}

	void Camera2D::WorldToScreen(const Vector2& pWorldPosition, Vector2& pScreenPosition) const
	{
	}
}
