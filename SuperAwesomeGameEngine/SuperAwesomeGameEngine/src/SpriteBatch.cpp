// SpriteBatch.cpp

// GL Includes
#include <gl\glew.h>
// SAGE Includes
#include <SAGE\SpriteBatch.hpp>
// STL Includes
#include <algorithm>

namespace SAGE
{
	SpriteBatch::SpriteBatch()
	{
		mWithinDrawPair = false;
		mItemCount = 0;
		mFlushCount = 0;
	}

	SpriteBatch::~SpriteBatch()
	{
		Finalize();
	}

	bool SpriteBatch::Initialize()
	{
		GLsizei sizeUShort = sizeof(GLushort);
		GLsizei sizeFloat = sizeof(GLfloat);
		GLsizei sizeVPCT = sizeof(VertexPositionColorTexture);

		// Enable GLew.
		glewExperimental = GL_TRUE;
		GLenum res = glewInit();
		if (res != GLEW_OK)
		{
			SDL_Log("[SpriteBatch::Initialize] GLEW failed to initialize: %s", glewGetErrorString(res));
			return false;
		}

		GLushort indexData[MaxIndexCount];
		for (int i = 0; i < MaxIndexCount / 6; i++)
		{
			indexData[i * 6 + 0] = i * 4 + 0;
			indexData[i * 6 + 1] = i * 4 + 1;
			indexData[i * 6 + 2] = i * 4 + 2;
			indexData[i * 6 + 3] = i * 4 + 0;
			indexData[i * 6 + 4] = i * 4 + 2;
			indexData[i * 6 + 5] = i * 4 + 3;
		}

		mIndexBufferObject = -1;
		glGenBuffers(1, &mIndexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndexCount * sizeUShort, indexData, GL_STATIC_DRAW);

		mVertexArrayObject = -1;
		glGenVertexArrays(1, &mVertexArrayObject);
		glBindVertexArray(mVertexArrayObject);

		mVertexBufferObject = -1;
		glGenBuffers(1, &mVertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeVPCT, nullptr, GL_DYNAMIC_DRAW);

		// Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeVPCT, (GLvoid*)(sizeFloat * 0));
		// Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeVPCT, (GLvoid*)(sizeFloat * 2));
		// Texcoord
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeVPCT, (GLvoid*)(sizeFloat * 6));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return true;
	}

	bool SpriteBatch::Finalize()
	{
		glDeleteVertexArrays(1, &mVertexArrayObject);
		glDeleteBuffers(1, &mVertexBufferObject);
		glDeleteBuffers(1, &mIndexBufferObject);

		return true;
	}

	int SpriteBatch::GetDrawCallCount() const
	{
		return mFlushCount;
	}

	bool SpriteBatch::Begin(SortMode pSortMode, BlendMode pBlendMode, SamplerState pSamplerState, DepthStencilState pDepthStencilState, RasterizerState pRasterizerState)
	{
		if (mWithinDrawPair)
		{
			SDL_Log("[SpriteBatch::Begin] Cannot nest draw pairs.");
			return false;
		}

		mSortMode = pSortMode;
		mBlendMode = pBlendMode;
		mSamplerState = pSamplerState;
		mDepthStencilState = pDepthStencilState;
		mRasterizerState = pRasterizerState;

		mWithinDrawPair = true;
		mItemCount = 0;
		mFlushCount = 0;

		return true;
	}

	bool SpriteBatch::Draw(const HGF::Texture& pTexture, const HGF::Vector2& pPosition, const HGF::Rectangle& pSource, const HGF::Color& pColor, const HGF::Vector2& pOrigin, float pRotation, const HGF::Vector2& pScale, Orientation pOrientation, float pDepth)
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[SpriteBatch::Draw] Must start a draw pair first.");
			return false;
		}

		int texWidth = pTexture.GetWidth();
		int texHeight = pTexture.GetHeight();
		HGF::Vector2 correction(1.0f / (float)texWidth, 1.0f / (float)texHeight);

		HGF::Rectangle rect;
		if (pSource != HGF::Rectangle::Empty)
			rect = pSource;
		else
			rect = HGF::Rectangle(0, 0, texWidth, texHeight);

		HGF::Vector2 size(rect.Width * pScale.X, rect.Height * pScale.Y);
		HGF::Vector2 origin(-pOrigin.X * pScale.X, -pOrigin.Y * pScale.Y);
		HGF::Vector2 texCoordTL(rect.X / (float)texWidth + correction.X, rect.Y / (float)texHeight + correction.X);
		HGF::Vector2 texCoordBR((rect.X + rect.Width) / (float)texWidth - correction.X, (rect.Y + rect.Height) / (float)texHeight - correction.Y);

		// Calculate cos/sin for rotation in radians.
		float cos = cosf(pRotation * (float)M_PI / 180.0f);
		float sin = sinf(pRotation * (float)M_PI / 180.0f);

		// Flip texture coordinates for orientation.
		if ((pOrientation & Orientation::FlipHorizontal) == Orientation::FlipHorizontal)
			std::swap(texCoordTL.X, texCoordBR.X);
		if ((pOrientation & Orientation::FlipVertical) == Orientation::FlipVertical)
			std::swap(texCoordTL.Y, texCoordBR.Y);

		SpriteBatchItem& item = mBatchItemList[mItemCount++];
		item.TextureID = pTexture.GetID();
		item.Depth = pDepth;

		item.VertexTL.Position.X = pPosition.X + origin.X * cos - origin.Y * sin;
		item.VertexTL.Position.Y = pPosition.Y + origin.X * sin + origin.Y * cos;
		item.VertexTL.Color.R = pColor.GetRed();
		item.VertexTL.Color.G = pColor.GetGreen();
		item.VertexTL.Color.B = pColor.GetBlue();
		item.VertexTL.Color.A = pColor.GetAlpha();
		item.VertexTL.TexCoord.X = texCoordTL.X;
		item.VertexTL.TexCoord.Y = texCoordTL.Y;

		item.VertexTR.Position.X = pPosition.X + (origin.X + size.X) * cos - origin.Y * sin;
		item.VertexTR.Position.Y = pPosition.Y + (origin.X + size.X) * sin + origin.Y * cos;
		item.VertexTR.Color.R = pColor.GetRed();
		item.VertexTR.Color.G = pColor.GetGreen();
		item.VertexTR.Color.B = pColor.GetBlue();
		item.VertexTR.Color.A = pColor.GetAlpha();
		item.VertexTR.TexCoord.X = texCoordBR.X;
		item.VertexTR.TexCoord.Y = texCoordTL.Y;

		item.VertexBL.Position.X = pPosition.X + origin.X * cos - (origin.Y + size.Y) * sin;
		item.VertexBL.Position.Y = pPosition.Y + origin.X * sin + (origin.Y + size.Y) * cos;
		item.VertexBL.Color.R = pColor.GetRed();
		item.VertexBL.Color.G = pColor.GetGreen();
		item.VertexBL.Color.B = pColor.GetBlue();
		item.VertexBL.Color.A = pColor.GetAlpha();
		item.VertexBL.TexCoord.X = texCoordTL.X;
		item.VertexBL.TexCoord.Y = texCoordBR.Y;

		item.VertexBR.Position.X = pPosition.X + (origin.X + size.X) * cos - (origin.Y + size.Y) * sin;
		item.VertexBR.Position.Y = pPosition.Y + (origin.X + size.X) * sin + (origin.Y + size.Y) * cos;
		item.VertexBR.Color.R = pColor.GetRed();
		item.VertexBR.Color.G = pColor.GetGreen();
		item.VertexBR.Color.B = pColor.GetBlue();
		item.VertexBR.Color.A = pColor.GetAlpha();
		item.VertexBR.TexCoord.X = texCoordBR.X;
		item.VertexBR.TexCoord.Y = texCoordBR.Y;

		return true;
	}

	bool SpriteBatch::DrawString(const SAGE::SpriteFont& pSpriteFont, const std::string& pString, const HGF::Vector2& pPosition, const HGF::Color& pColor, const HGF::Vector2& pOrigin, float pRotation, const HGF::Vector2& pScale, Orientation pOrientation, float pDepth)
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[SpriteBatch::DrawString] Must start a draw pair first.");
			return false;
		}

		const HGF::Texture& texture = pSpriteFont.GetTexture();

		int texWidth = texture.GetWidth();
		int texHeight = texture.GetHeight();

		float size = pSpriteFont.GetSize();
		float spacing = pSpriteFont.GetSpacing();

		HGF::Vector2 correction(1.0f / (float)texWidth, 1.0f / (float)texHeight);
		HGF::Vector2 origin(-pOrigin.X * pScale.X, -pOrigin.Y * pScale.Y);

		HGF::Vector2 offset = HGF::Vector2::Zero;

		for (char glyph : pString)
		{
			if (glyph == '\n')
			{
				offset.X = 0.0f;
				offset.Y += size * pScale.Y;
			}
			else
			{
				HGF::Rectangle rect = pSpriteFont.GetGlyphBounds(glyph);

				HGF::Vector2 size(rect.Width * pScale.X, rect.Height * pScale.Y);
				HGF::Vector2 texCoordTL(rect.X / (float)texWidth + correction.X, rect.Y / (float)texHeight + correction.X);
				HGF::Vector2 texCoordBR((rect.X + rect.Width) / (float)texWidth - correction.X, (rect.Y + rect.Height) / (float)texHeight - correction.Y);

				SpriteBatchItem& item = mBatchItemList[mItemCount++];
				item.TextureID = texture.GetID();
				item.Depth = pDepth;

				item.VertexTL.Position.X = pPosition.X + origin.X + offset.X;
				item.VertexTL.Position.Y = pPosition.Y + origin.Y + offset.Y;
				item.VertexTL.Color.R = pColor.GetRed();
				item.VertexTL.Color.G = pColor.GetGreen();
				item.VertexTL.Color.B = pColor.GetBlue();
				item.VertexTL.Color.A = pColor.GetAlpha();
				item.VertexTL.TexCoord.X = texCoordTL.X;
				item.VertexTL.TexCoord.Y = texCoordTL.Y;

				RotateAbout(pPosition, pRotation, item.VertexTL.Position);
				FlipAbout(pPosition, pOrientation, item.VertexTL.Position);

				item.VertexTR.Position.X = pPosition.X + origin.X + size.X + offset.X;
				item.VertexTR.Position.Y = pPosition.Y + origin.Y + offset.Y;
				item.VertexTR.Color.R = pColor.GetRed();
				item.VertexTR.Color.G = pColor.GetGreen();
				item.VertexTR.Color.B = pColor.GetBlue();
				item.VertexTR.Color.A = pColor.GetAlpha();
				item.VertexTR.TexCoord.X = texCoordBR.X;
				item.VertexTR.TexCoord.Y = texCoordTL.Y;

				RotateAbout(pPosition, pRotation, item.VertexTR.Position);
				FlipAbout(pPosition, pOrientation, item.VertexTR.Position);

				item.VertexBL.Position.X = pPosition.X + origin.X + offset.X;
				item.VertexBL.Position.Y = pPosition.Y + origin.Y + size.Y + offset.Y;
				item.VertexBL.Color.R = pColor.GetRed();
				item.VertexBL.Color.G = pColor.GetGreen();
				item.VertexBL.Color.B = pColor.GetBlue();
				item.VertexBL.Color.A = pColor.GetAlpha();
				item.VertexBL.TexCoord.X = texCoordTL.X;
				item.VertexBL.TexCoord.Y = texCoordBR.Y;

				RotateAbout(pPosition, pRotation, item.VertexBL.Position);
				FlipAbout(pPosition, pOrientation, item.VertexBL.Position);

				item.VertexBR.Position.X = pPosition.X + origin.X + size.X + offset.X;
				item.VertexBR.Position.Y = pPosition.Y + origin.Y + size.Y + offset.Y;
				item.VertexBR.Color.R = pColor.GetRed();
				item.VertexBR.Color.G = pColor.GetGreen();
				item.VertexBR.Color.B = pColor.GetBlue();
				item.VertexBR.Color.A = pColor.GetAlpha();
				item.VertexBR.TexCoord.X = texCoordBR.X;
				item.VertexBR.TexCoord.Y = texCoordBR.Y;

				RotateAbout(pPosition, pRotation, item.VertexBR.Position);
				FlipAbout(pPosition, pOrientation, item.VertexBR.Position);

				offset.X += spacing * pScale.X;
			}
		}

		return false;
	}

	bool SpriteBatch::End()
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[SpriteBatch::End] Cannot end a pair without starting.");
			return false;
		}

		switch (mSortMode)
		{
			case SortMode::Texture:
				std::sort(std::begin(mBatchItemList), std::end(mBatchItemList), [](const SpriteBatchItem& pItemA, const SpriteBatchItem& pItemB) { return pItemA.TextureID > pItemB.TextureID; });
				break;
			case SortMode::FrontToBack:
				std::sort(std::begin(mBatchItemList), std::end(mBatchItemList), [](const SpriteBatchItem& pItemA, const SpriteBatchItem& pItemB) { return pItemA.Depth > pItemB.Depth; });
				break;
			case SortMode::BackToFront:
				std::sort(std::begin(mBatchItemList), std::end(mBatchItemList), [](const SpriteBatchItem& pItemA, const SpriteBatchItem& pItemB) { return pItemA.Depth < pItemB.Depth; });
				break;
		}

		switch (mBlendMode)
		{
			case BlendMode::None:
				glDisable(GL_BLEND);
				break;
			case BlendMode::Premultiplied:
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
				break;
			case BlendMode::AlphaBlended:
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				break;
			case BlendMode::Additive:
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				break;
		}

		if (mItemCount > 0)
			Render();

		mWithinDrawPair = false;

		return true;
	}

	void SpriteBatch::Render()
	{
		int length = 0;
		int texID = -1;

		for (int i = 0; i < mItemCount; ++i)
		{
			SpriteBatchItem& item = mBatchItemList[i];

			if (item.TextureID != texID)
			{
				if (texID != -1)
				{
					Flush(texID, length);
				}
				length = 0;
				texID = item.TextureID;
			}

			if (length * 6 > MaxVertexCount)
			{
				Flush(texID, length);
				length = 0;
			}

			mVertexBuffer[length * 4 + 0] = item.VertexBL;
			mVertexBuffer[length * 4 + 1] = item.VertexBR;
			mVertexBuffer[length * 4 + 2] = item.VertexTR;
			mVertexBuffer[length * 4 + 3] = item.VertexTL;

			length++;
		}

		Flush(texID, length);
	}

	void SpriteBatch::Flush(int pTextureID, int pLength)
	{
		// Ensure there's something to draw.
		if (pLength == 0)
			return;

		// Enable textures and bind the current ID.
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, pTextureID);

		// Bind the vertex array.
		glBindVertexArray(mVertexArrayObject);

		// Bind the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);

		// Option 1: Insert subset into buffer.
		glBufferSubData(GL_ARRAY_BUFFER, 0, pLength * 4 * sizeof(VertexPositionColorTexture), mVertexBuffer);

		// Option 2: Write to buffer mapping.
		/*
		glBufferData(GL_ARRAY_BUFFER, mVertexBuffer.size() * sizeof(VertexPositionColorTexture), nullptr, GL_DYNAMIC_DRAW);
		VertexPositionColorTexture* map = reinterpret_cast<VertexPositionColorTexture*>(
		glMapBufferRange(GL_ARRAY_BUFFER,
		0,
		pLength * sizeof(VertexPositionColorTexture),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)
		);
		std::copy(mVertexBuffer.begin(), mVertexBuffer.end(), map);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		*/

		// Bind the element buffer and draw.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferObject);
		glDrawElements(GL_TRIANGLES, pLength * 6, GL_UNSIGNED_SHORT, nullptr);

		// Clear bindings.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Disable textures.
		glDisable(GL_TEXTURE_2D);

		mFlushCount++;
	}

	void SpriteBatch::RotateAbout(const HGF::Vector2& pPosition, float pRotation, VertexVector2& pVertex)
	{
		float cos = cosf(pRotation);
		float sin = sinf(pRotation);

		pVertex.X -= pPosition.X;
		pVertex.Y -= pPosition.Y;

		float rotX = pVertex.X * cos - pVertex.Y * sin;
		float rotY = pVertex.X * sin + pVertex.Y * cos;

		pVertex.X = rotX + pPosition.X;
		pVertex.Y = rotY + pPosition.Y;
	}

	void SpriteBatch::FlipAbout(const HGF::Vector2& pPosition, Orientation pOrientation, VertexVector2& pVertex)
	{
		// Flip texture coordinates for orientation.
		if ((pOrientation & Orientation::FlipHorizontal) == Orientation::FlipHorizontal)
			pVertex.X = pPosition.X - (pVertex.X - pPosition.X);
		if ((pOrientation & Orientation::FlipVertical) == Orientation::FlipVertical)
			pVertex.Y = pPosition.Y - (pVertex.Y - pPosition.Y);
	}
}