// Camera2D.hpp

#ifndef __SAGE_CAMERA2D_HPP__
#define __SAGE_CAMERA2D_HPP__

// GLM Includes
#define GLM_FORCE_RADIANS
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
// HGF Includes
#include <HGF\Vector2.hpp>

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

			HGF::Vector2 GetPosition() const;
			float GetRotation() const;
			HGF::Vector2 GetScale() const;
			int GetWidth() const;
			int GetHeight() const;
			glm::mat4 GetProjectionMatrix(View pView = View::Orthographic) const;
			glm::mat4 GetModelViewMatrix() const;

			void SetPosition(const HGF::Vector2& pPosition);
			void SetRotation(float pRotation);
			void SetScale(const HGF::Vector2& pScale);
			void SetTransformation(const HGF::Vector2& pPosition, float pRotation, const HGF::Vector2& pScale);
			void SetWidth(int pWidth);
			void SetHeight(int pHeight);
			void SetDimensions(int pWidth, int pHeight);

			void Translate(const HGF::Vector2& pTranslation);
			void Rotate(float pRotation);
			void Scale(const HGF::Vector2& pScale);

			void ScreenToWorld(const HGF::Vector2& pScreenPosition, HGF::Vector2& pWorldPosition) const;
			void WorldToScreen(const HGF::Vector2& pWorldPosition, HGF::Vector2& pScreenPosition) const;

		private:
			static int DefaultWidth;
			static int DefaultHeight;

			HGF::Vector2 mPosition;
			float mRotation;
			HGF::Vector2 mScale;
			int mWidth;
			int mHeight;
	};
}

#endif