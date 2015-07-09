// Camera2D.hpp

#ifndef __SAGE_CAMERA2D_HPP__
#define __SAGE_CAMERA2D_HPP__

// GLM Includes
#define GLM_FORCE_RADIANS
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
// SAGE Includes
#include <SAGE\Vector2.hpp>

namespace SAGE
{
	class Camera2D
	{
		public:
			Camera2D();
			~Camera2D();

			enum class View
			{
				Orthographic,
				Perspective,
			};

			static const Camera2D DefaultCamera;

			Vector2 GetPosition() const;
			float GetRotation() const;
			Vector2 GetScale() const;
			int GetWidth() const;
			int GetHeight() const;
			glm::mat4 GetProjectionMatrix(View p_View = View::Orthographic) const;
			glm::mat4 GetModelViewMatrix() const;

			void SetPosition(const Vector2& p_Position);
			void SetRotation(float p_Rotation);
			void SetScale(const Vector2& p_Scale);
			void SetTransformation(const Vector2& p_Position, float p_Rotation, const Vector2& p_Scale);
			void SetWidth(int p_Width);
			void SetHeight(int p_Height);
			void SetDimensions(int p_Width, int p_Height);

			void Translate(const Vector2& p_Translation);
			void Rotate(float p_Rotation);
			void Scale(const Vector2& p_Scale);

			void ScreenToWorld(const Vector2& p_ScreenPosition, Vector2& p_WorldPosition) const;
			void WorldToScreen(const Vector2& p_WorldPosition, Vector2& p_ScreenPosition) const;

		private:
			static int DefaultWidth;
			static int DefaultHeight;

			Vector2 m_Position;
			float m_Rotation;
			Vector2 m_Scale;
			int m_Width;
			int m_Height;
	};
}

#endif
