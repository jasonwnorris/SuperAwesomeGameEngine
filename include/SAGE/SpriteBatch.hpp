// SpriteBatch.hpp

#ifndef __SAGE_SPRITEBATCH_HPP__
#define __SAGE_SPRITEBATCH_HPP__

// SAGE Includes
#include <SAGE/Color.hpp>
#include <SAGE/Camera2D.hpp>
#include <SAGE/Effect.hpp>
#include <SAGE/Orientation.hpp>
#include <SAGE/Rectangle.hpp>
#include <SAGE/SpriteFont.hpp>
#include <SAGE/Texture.hpp>
#include <SAGE/Vector2.hpp>
#include <SAGE/VertexDefinitions.hpp>
// STL Includes
#include <vector>

namespace SAGE
{
	enum class SortMode
	{
		None,
		FrontToBack,
		BackToFront,
		Texture,
		Immediate,
	};

	enum class BlendMode
	{
		None,
		Premultiplied,
		Additive,
		AlphaBlended,
	};

	enum class RasterizerState
	{
		None,
		CullClockwise,
		CullCounterClockwise,
	};

	struct SpriteBatchItem
	{
		unsigned int TextureID;
		float Depth;
		VertexPositionColorTexture VertexA;
		VertexPositionColorTexture VertexB;
		VertexPositionColorTexture VertexC;
	};

	class SpriteBatch
	{
		private:
			static const int MaxBatchSize = 1024 * 10;
			static const int MaxVertexCount = MaxBatchSize * 3;
			static const int MaxIndexCount = MaxBatchSize * 3;

		public:
			SpriteBatch();
			~SpriteBatch();

			int GetDrawCallCount() const;

			bool Initialize();
			bool Finalize();

			bool Begin(Effect& p_Effect, const Camera2D& p_Camera = Camera2D::DefaultCamera, SortMode p_SortMode = SortMode::None, BlendMode p_BlendMode = BlendMode::None, RasterizerState p_RasterizerState = RasterizerState::CullCounterClockwise);

			bool DrawLine(const Vector2& p_PositionA, const Vector2& p_PositionB, const Color& p_Color, float p_Thickness = 1.0f, float p_Depth = 0.0f);
			bool DrawLine(const Vector2& p_PositionA, const Color& p_ColorA, const Vector2& p_PositionB, const Color& p_ColorB, float p_Thickness = 1.0f, float p_Depth = 0.0f);

			bool DrawLines(const std::vector<Vector2>& p_Positions, const Color& p_Color, float p_Thickness = 1.0f, float p_Depth = 0.0f);
			bool DrawLines(const std::vector<Vector2>& p_Positions, const std::vector<Color>& p_Colors, float p_Thickness = 1.0f, float p_Depth = 0.0f);

			bool DrawLineLoop(const std::vector<Vector2>& p_Positions, const Color& p_Color, float p_Thickness = 1.0f, float p_Depth = 0.0f);
			bool DrawLineLoop(const std::vector<Vector2>& p_Positions, const std::vector<Color>& p_Colors, float p_Thickness = 1.0f, float p_Depth = 0.0f);

			bool DrawCircle(const Vector2& p_Position, const Color& p_Color, float p_Radius, float p_Thickness = 1.0f, float p_Depth = 0.0f);
			bool DrawCircle(const Vector2& p_Position, const std::vector<Color>& p_Colors, float p_Radius, float p_Thickness = 1.0f, float p_Depth = 0.0f);

			bool DrawSolidTriangle(const Vector2 p_Positions[3], const Color& p_Color, float p_Depth = 0.0f);

			bool DrawSolidRectangle(float p_X, float p_Y, float p_Width, float p_Height, const Color& p_Color, float p_Depth = 0.0f);
			bool DrawSolidRectangle(const Rectangle& p_Rectangle, const Color& p_Color, float p_Depth = 0.0f);
			bool DrawSolidRectangle(const Vector2& p_Position, const Vector2& p_Dimensions, const Color& p_Color, float p_Depth = 0.0f);

			bool DrawSprite(const Texture& p_Texture, const Vector2& p_Position, const Vector2& p_Dimensions, const Rectangle& p_SourceRectangle, const Color& p_Color, const Vector2& p_Origin, float p_Rotation, const Vector2& p_Scale, Orientation p_Orientation, float p_Depth = 0.0f);
			bool DrawSprite(const Texture& p_Texture, const Vector2& p_Position, const Rectangle& p_DestinationRectangle, const Rectangle& p_SourceRectangle, const Color& p_Color, const Vector2& p_Origin, float p_Rotation, const Vector2& p_Scale, Orientation p_Orientation, float p_Depth = 0.0f);
			bool DrawSprite(const Texture& p_Texture, const Rectangle& p_DestinationRectangle, const Rectangle& p_SourceRectangle, const Color& p_Color, const Vector2& p_Origin, float p_Rotation, const Vector2& p_Scale, Orientation p_Orientation, float p_Depth = 0.0f);
			bool DrawSprite(const Texture& p_Texture, const Vector2& p_Position, const Rectangle& p_SourceRectangle, const Color& p_Color, const Vector2& p_Origin, float p_Rotation, const Vector2& p_Scale, Orientation p_Orientation, float p_Depth = 0.0f);

			bool DrawString(const SAGE::IFont* const p_Font, const std::string& p_String, const Vector2& p_Position, const Color& p_Color, float p_Depth = 0.0f);
			bool DrawString(const SAGE::IFont* const p_Font, const std::string& p_String, const Vector2& p_Position, const Color& p_Color, const Vector2& p_Origin, float p_Rotation, const Vector2& p_Scale, Orientation p_Orientation, float p_Depth = 0.0f);

			bool End();

		private:
			void Render();
			void Flush(int p_TextureID, int p_Length);

			SpriteBatchItem& GetNextItem(const Texture& p_Texture, float p_Depth = 0.0f);
			void SetVertexPosition(VertexPositionColorTexture& p_Vertex, float p_X, float p_Y);
			void SetVertexColor(VertexPositionColorTexture& p_Vertex, const Color& p_Color);
			void SetVertexTexCoords(VertexPositionColorTexture& p_Vertex, float p_U, float p_V);
			void SetVertex(VertexPositionColorTexture& p_Vertex, float p_X, float p_Y, const Color& p_Color, float p_U, float p_V);
			void TransformVerticesAbout(SpriteBatchItem& p_Item, const Vector2& p_Position, float p_CosAngle, float p_SinAngle, Orientation p_Orientation);
			void RotateVerticesAbout(SpriteBatchItem& p_Item, const Vector2& p_Position, float p_CosAngle, float p_SinAngle);
			void FlipVerticesAbout(SpriteBatchItem& p_Item, const Vector2& p_Position, Orientation p_Orientation);
			void RotateVertexAbout(VertexPositionColorTexture& p_Vertex, const Vector2& p_Position, float p_CosAngle, float p_SinAngle);
			void FlipVertexAbout(VertexPositionColorTexture& p_Vertex, const Vector2& p_Position, Orientation p_Orientation);

			bool m_WithinDrawPair;
			int m_ItemCount;
			int m_FlushCount;
			SortMode m_SortMode;
			BlendMode m_BlendMode;
			RasterizerState m_RasterizerState;
			GLuint m_VertexArrayObject;
			GLuint m_VertexBufferObject;
			GLuint m_IndexBufferObject;
			SpriteBatchItem m_BatchItemList[MaxBatchSize];
			VertexPositionColorTexture m_VertexBuffer[MaxVertexCount];
			Texture m_BlankTexture;
	};
}

#endif
