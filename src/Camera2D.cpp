// Camera2D.cpp

// SAGE Includes
#include <SAGE/Camera2D.hpp>

namespace SAGE
{
	const Camera2D Camera2D::DefaultCamera;
	int Camera2D::DefaultWidth = 1280;
	int Camera2D::DefaultHeight = 720;

	Camera2D::Camera2D()
	{
		m_Position = Vector2::Zero;
		m_Rotation = 0.0f;
		m_Scale = Vector2::One;
		m_Width = DefaultWidth;
		m_Height = DefaultHeight;
	}

	Camera2D::~Camera2D()
	{
	}

	Vector2 Camera2D::GetPosition() const
	{
		return m_Position;
	}

	float Camera2D::GetRotation() const
	{
		return m_Rotation;
	}

	Vector2 Camera2D::GetScale() const
	{
		return m_Scale;
	}

	int Camera2D::GetWidth() const
	{
		return m_Width;
	}

	int Camera2D::GetHeight() const
	{
		return m_Height;
	}

	glm::mat4 Camera2D::GetProjectionMatrix(View p_View) const
	{
		switch (p_View)
		{
			default:
			case View::Orthographic:
				return glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, 1.0f, -1.0f);
			case View::Perspective:
				return glm::perspective(45.0f, (float)m_Width / (float)m_Height, 0.1f, 1000.0f);
		}
	}

	glm::mat4 Camera2D::GetModelViewMatrix() const
	{
		glm::mat4 modelViewMatrix;
		modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3((float)m_Width / 2.0f, (float)m_Height / 2.0f, 0.0f));
		modelViewMatrix = glm::scale(modelViewMatrix, glm::vec3(m_Scale.X, m_Scale.Y, 1.0f));
		modelViewMatrix = glm::rotate(modelViewMatrix, m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(-m_Position.X, -m_Position.Y, 0.0f));

		return modelViewMatrix;
	}

	void Camera2D::SetPosition(const Vector2& p_Position)
	{
		m_Position = p_Position;
	}

	void Camera2D::SetRotation(float p_Rotation)
	{
		m_Rotation = p_Rotation;
	}

	void Camera2D::SetScale(const Vector2& p_Scale)
	{
		m_Scale = p_Scale;
	}

	void Camera2D::SetTransformation(const Vector2& p_Position, float p_Rotation, const Vector2& p_Scale)
	{
		m_Position = p_Position;
		m_Rotation = p_Rotation;
		m_Scale = p_Scale;
	}

	void Camera2D::SetWidth(int p_Width)
	{
		m_Width = p_Width;
	}

	void Camera2D::SetHeight(int p_Height)
	{
		m_Height = p_Height;
	}

	void Camera2D::SetDimensions(int p_Width, int p_Height)
	{
		m_Width = p_Width;
		m_Height = p_Height;
	}

	void Camera2D::Translate(const Vector2& p_Translation)
	{
		m_Position += p_Translation;
	}

	void Camera2D::Rotate(float p_Rotation)
	{
		m_Rotation += p_Rotation;
	}

	void Camera2D::Scale(const Vector2& p_Scale)
	{
		m_Scale += p_Scale;
	}

	void Camera2D::ScreenToWorld(const Vector2& p_ScreenPosition, Vector2& p_WorldPosition) const
	{
	}

	void Camera2D::WorldToScreen(const Vector2& p_WorldPosition, Vector2& p_ScreenPosition) const
	{
	}
}
