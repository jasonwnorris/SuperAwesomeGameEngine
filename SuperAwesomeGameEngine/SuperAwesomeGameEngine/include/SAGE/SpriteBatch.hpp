// SpriteBatch.hpp

#ifndef __SAGE_SPRITEBATCH_HPP__
#define __SAGE_SPRITEBATCH_HPP__

// SAGE Includes
#include <SAGE\VertexDefinitions.hpp>
// HGF Includes
#include <HGF\Rectangle.hpp>
#include <HGF\Texture.hpp>
// STL Includes
#include <vector>

namespace SAGE
{
	struct SpriteBatchItem
	{
		unsigned int TextureID;
		float Depth;
		VertexPositionColorNormalTexture VertexTL;
		VertexPositionColorNormalTexture VertexTR;
		VertexPositionColorNormalTexture VertexBL;
		VertexPositionColorNormalTexture VertexBR;
	};

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

	enum class SamplerState
	{
		PointClamp,
		PointWrap,
		LinearClamp,
		LinearWrap,
		AnisotropicClamp,
		AnisotropicWrap,
	};

	enum class DepthStencilState
	{
		None,
		Default,
		DepthRead,
	};

	enum class RasterizerState
	{
		None,
		CullClockwise,
		CullCounterClockwise,
	};

	enum class OrientationEffect
	{
		None = 1 << 0,
		FlipHorizontal = 1 << 1,
		FlipVertical = 1 << 2,
		FlipBoth = (1 << 1) | (1 << 2)
	};

	inline OrientationEffect operator|(OrientationEffect pEffectA, OrientationEffect pEffectB)
	{
		return static_cast<OrientationEffect>(static_cast<int>(pEffectA) | static_cast<int>(pEffectB));
	}

	inline OrientationEffect operator&(OrientationEffect pEffectA, OrientationEffect pEffectB)
	{
		return static_cast<OrientationEffect>(static_cast<int>(pEffectA)& static_cast<int>(pEffectB));
	}

	class SpriteBatch
	{
		private:
			static const int MaxBatchSize = 1024;
			static const int MaxVertexCount = MaxBatchSize * 4;
			static const int MaxIndexCount = MaxVertexCount / 2 * 3;
			static const int RingBufferCount = 3;

		public:
			SpriteBatch();
			~SpriteBatch();

			bool Initialize();
			bool Finalize();

			bool Begin(SortMode pSortMode = SortMode::None, BlendMode pBlendMode = BlendMode::None, SamplerState pSamplerState = SamplerState::LinearClamp, DepthStencilState pDepthStencilState = DepthStencilState::Default, RasterizerState pRasterizerState = RasterizerState::CullCounterClockwise);
			bool Draw(const HGF::Texture& pTexture, const HGF::Vector2& pPosition, const HGF::Rectangle& pSource, const HGF::Color& pColor, const HGF::Vector2& pOrigin, float pRotation, const HGF::Vector2& pScale, OrientationEffect pOrientationEffect, float pDepth = 0.0f);
			bool End();

		private:
			void Render();
			void Flush(int pTextureID, int pLength);

			bool mWithinDrawPair;
			SortMode mSortMode;
			BlendMode mBlendMode;
			SamplerState mSamplerState;
			DepthStencilState mDepthStencilState;
			RasterizerState mRasterizerState;
			int mBufferIndex;
			GLuint mVertexArrayObject[RingBufferCount];
			GLuint mVertexBufferObject[RingBufferCount];
			GLuint mIndexBufferObject;
			std::vector<SpriteBatchItem> mBatchItemList;
			std::vector<VertexPositionColorNormalTexture> mVertexBuffer;
	};
}

#endif