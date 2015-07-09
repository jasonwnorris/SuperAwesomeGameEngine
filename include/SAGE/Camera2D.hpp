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
			glm::mat4 GetProjectionMatrix(View pView = View::Orthographic) const;
			glm::mat4 GetModelViewMatrix() const;

			void SetPosition(const Vector2& pPosition);
			void SetRotation(float pRotation);
			void SetScale(const Vector2& pScale);
			void SetTransformation(const Vector2& pPosition, float pRotation, const Vector2& pScale);
			void SetWidth(int pWidth);
			void SetHeight(int pHeight);
			void SetDimensions(int pWidth, int pHeight);

			void Translate(const Vector2& pTranslation);
			void Rotate(float pRotation);
			void Scale(const Vector2& pScale);

			void ScreenToWorld(const Vector2& pScreenPosition, Vector2& pWorldPosition) const;
			void WorldToScreen(const Vector2& pWorldPosition, Vector2& pScreenPosition) const;

		private:
			static int DefaultWidth;
			static int DefaultHeight;

			Vector2 mPosition;
			float mRotation;
			Vector2 mScale;
			int mWidth;
			int mHeight;
	};
}

#endif
