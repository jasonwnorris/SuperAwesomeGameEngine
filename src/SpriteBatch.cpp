// SpriteBatch.cpp

// OpenGL Includes
#include <gl\glew.h>
// SAGE Includes
#include <SAGE\SpriteBatch.hpp>
// STL Includes
#include <algorithm>

namespace SAGE
{
	SpriteBatch::SpriteBatch()
	{
		m_WithinDrawPair = false;
		m_ItemCount = 0;
		m_FlushCount = 0;
	}

	SpriteBatch::~SpriteBatch()
	{
		Finalize();
	}

	int SpriteBatch::GetDrawCallCount() const
	{
		return m_FlushCount;
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

		// Generate data for index buffer.
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

		// Create the index buffer object.
		m_IndexBufferObject = -1;
		glGenBuffers(1, &m_IndexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndexCount * sizeUShort, indexData, GL_STATIC_DRAW);

		// Create the vertex array object.
		m_VertexArrayObject = -1;
		glGenVertexArrays(1, &m_VertexArrayObject);
		glBindVertexArray(m_VertexArrayObject);

		// Create the vertex buffer object.
		m_VertexBufferObject = -1;
		glGenBuffers(1, &m_VertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeVPCT, nullptr, GL_DYNAMIC_DRAW);

		// Position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeVPCT, (GLvoid*)(sizeFloat * 0));
		// Color attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeVPCT, (GLvoid*)(sizeFloat * 2));
		// Texcoord attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeVPCT, (GLvoid*)(sizeFloat * 6));

		// Clear bindings.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return true;
	}

	bool SpriteBatch::Finalize()
	{
		// Destroy objects.
		glDeleteVertexArrays(1, &m_VertexArrayObject);
		glDeleteBuffers(1, &m_VertexBufferObject);
		glDeleteBuffers(1, &m_IndexBufferObject);

		return true;
	}

	bool SpriteBatch::Begin(Effect& p_Effect, const Camera2D& p_Camera, SortMode p_SortMode, BlendMode p_BlendMode, RasterizerState p_RasterizerState)
	{
		if (m_WithinDrawPair)
		{
			SDL_Log("[SpriteBatch::Begin] Cannot nest draw pairs.");
			return false;
		}

		m_WithinDrawPair = true;
		m_ItemCount = 0;
		m_FlushCount = 0;

		m_SortMode = p_SortMode;
		m_BlendMode = p_BlendMode;
		m_RasterizerState = p_RasterizerState;

		p_Effect.SetProjection(p_Camera.GetProjectionMatrix());
		p_Effect.SetModelView(p_Camera.GetModelViewMatrix());
		p_Effect.Use();

		return true;
	}

	bool SpriteBatch::Draw(const Texture& p_Texture, const Vector2& p_Position, const Vector2& p_Dimensions, const Rectangle& p_SourceRectangle, const Color& p_Color, const Vector2& p_Origin, float p_Rotation, const Vector2& p_Scale, Orientation p_Orientation, float p_Depth)
	{
		// TODO: Factor in p_Dimensions.
		return Draw(p_Texture, p_Position, p_SourceRectangle, p_Color, p_Origin, p_Rotation, p_Scale, p_Orientation, p_Depth);
	}
	
	bool SpriteBatch::Draw(const Texture& p_Texture, const Vector2& p_Position, const Rectangle& p_DestinationRectangle, const Rectangle& p_SourceRectangle, const Color& p_Color, const Vector2& p_Origin, float p_Rotation, const Vector2& p_Scale, Orientation p_Orientation, float p_Depth)
	{
		// TODO: Factor in p_DestinationRectangle.
		return Draw(p_Texture, p_Position, p_SourceRectangle, p_Color, p_Origin, p_Rotation, p_Scale, p_Orientation, p_Depth);
	}
	
	bool SpriteBatch::Draw(const Texture& p_Texture, const Rectangle& p_DestinationRectangle, const Rectangle& p_SourceRectangle, const Color& p_Color, const Vector2& p_Origin, float p_Rotation, const Vector2& p_Scale, Orientation p_Orientation, float p_Depth)
	{
		// TODO: Factor in p_DestinationRectangle BETTERLY.
		return Draw(p_Texture, Vector2(p_DestinationRectangle.X, p_DestinationRectangle.Y), p_SourceRectangle, p_Color, p_Origin, p_Rotation, p_Scale, p_Orientation, p_Depth);
	}

	bool SpriteBatch::Draw(const Texture& p_Texture, const Vector2& p_Position, const Rectangle& p_SourceRectangle, const Color& p_Color, const Vector2& p_Origin, float p_Rotation, const Vector2& p_Scale, Orientation p_Orientation, float p_Depth)
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[SpriteBatch::Draw] Must start a draw pair first.");
			return false;
		}

		int texWidth = p_Texture.GetWidth();
		int texHeight = p_Texture.GetHeight();
		Vector2 correction(1.0f / (float)texWidth, 1.0f / (float)texHeight);

		Rectangle rect;
		if (p_SourceRectangle != Rectangle::Empty)
			rect = p_SourceRectangle;
		else
			rect = Rectangle(0, 0, texWidth, texHeight);

		Vector2 size(rect.Width * p_Scale.X, rect.Height * p_Scale.Y);
		Vector2 origin(-p_Origin.X * p_Scale.X, -p_Origin.Y * p_Scale.Y);
		Vector2 texCoordTL(rect.X / (float)texWidth + correction.X, rect.Y / (float)texHeight + correction.X);
		Vector2 texCoordBR((rect.X + rect.Width) / (float)texWidth - correction.X, (rect.Y + rect.Height) / (float)texHeight - correction.Y);

		// Calculate cos/sin for rotation in radians.
		float cos = cosf(p_Rotation * (float)M_PI / 180.0f);
		float sin = sinf(p_Rotation * (float)M_PI / 180.0f);

		// Flip texture coordinates for orientation.
		if ((p_Orientation & Orientation::FlipHorizontal) == Orientation::FlipHorizontal)
			std::swap(texCoordTL.X, texCoordBR.X);
		if ((p_Orientation & Orientation::FlipVertical) == Orientation::FlipVertical)
			std::swap(texCoordTL.Y, texCoordBR.Y);

		SpriteBatchItem& item = m_BatchItemList[m_ItemCount++];
		item.TextureID = p_Texture.GetID();
		item.Depth = p_Depth;

		item.VertexTL.Position.X = p_Position.X + origin.X * cos - origin.Y * sin;
		item.VertexTL.Position.Y = p_Position.Y + origin.X * sin + origin.Y * cos;
		item.VertexTL.Color.R = p_Color.GetRed();
		item.VertexTL.Color.G = p_Color.GetGreen();
		item.VertexTL.Color.B = p_Color.GetBlue();
		item.VertexTL.Color.A = p_Color.GetAlpha();
		item.VertexTL.TexCoord.X = texCoordTL.X;
		item.VertexTL.TexCoord.Y = texCoordTL.Y;

		item.VertexTR.Position.X = p_Position.X + (origin.X + size.X) * cos - origin.Y * sin;
		item.VertexTR.Position.Y = p_Position.Y + (origin.X + size.X) * sin + origin.Y * cos;
		item.VertexTR.Color.R = p_Color.GetRed();
		item.VertexTR.Color.G = p_Color.GetGreen();
		item.VertexTR.Color.B = p_Color.GetBlue();
		item.VertexTR.Color.A = p_Color.GetAlpha();
		item.VertexTR.TexCoord.X = texCoordBR.X;
		item.VertexTR.TexCoord.Y = texCoordTL.Y;

		item.VertexBL.Position.X = p_Position.X + origin.X * cos - (origin.Y + size.Y) * sin;
		item.VertexBL.Position.Y = p_Position.Y + origin.X * sin + (origin.Y + size.Y) * cos;
		item.VertexBL.Color.R = p_Color.GetRed();
		item.VertexBL.Color.G = p_Color.GetGreen();
		item.VertexBL.Color.B = p_Color.GetBlue();
		item.VertexBL.Color.A = p_Color.GetAlpha();
		item.VertexBL.TexCoord.X = texCoordTL.X;
		item.VertexBL.TexCoord.Y = texCoordBR.Y;

		item.VertexBR.Position.X = p_Position.X + (origin.X + size.X) * cos - (origin.Y + size.Y) * sin;
		item.VertexBR.Position.Y = p_Position.Y + (origin.X + size.X) * sin + (origin.Y + size.Y) * cos;
		item.VertexBR.Color.R = p_Color.GetRed();
		item.VertexBR.Color.G = p_Color.GetGreen();
		item.VertexBR.Color.B = p_Color.GetBlue();
		item.VertexBR.Color.A = p_Color.GetAlpha();
		item.VertexBR.TexCoord.X = texCoordBR.X;
		item.VertexBR.TexCoord.Y = texCoordBR.Y;

		return true;
	}

	bool SpriteBatch::DrawString(const SAGE::SpriteFont& p_SpriteFont, const std::string& p_String, const Vector2& p_Position, const Color& p_Color, float p_Depth)
	{
		return DrawString(p_SpriteFont, p_String, p_Position, p_Color, Vector2::Zero, 0.0f, Vector2::One, SAGE::Orientation::None, p_Depth);
	}

	bool SpriteBatch::DrawString(const SAGE::SpriteFont& p_SpriteFont, const std::string& p_String, const Vector2& p_Position, const Color& p_Color, const Vector2& p_Origin, float p_Rotation, const Vector2& p_Scale, Orientation p_Orientation, float p_Depth)
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[SpriteBatch::DrawString] Must start a draw pair first.");
			return false;
		}

		const Texture& texture = p_SpriteFont.GetTexture();

		int texWidth = texture.GetWidth();
		int texHeight = texture.GetHeight();

		float size = p_SpriteFont.GetSize();
		float spacing = p_SpriteFont.GetSpacing();

		Vector2 correction(1.0f / (float)texWidth, 1.0f / (float)texHeight);
		Vector2 origin(-p_Origin.X * p_Scale.X, -p_Origin.Y * p_Scale.Y);

		Vector2 offset = Vector2::Zero;

		for (char glyph : p_String)
		{
			if (glyph == '\n')
			{
				offset.X = 0.0f;
				offset.Y += size * p_Scale.Y;
			}
			else
			{
				Rectangle rect = p_SpriteFont.GetGlyphBounds(glyph);

				Vector2 size(rect.Width * p_Scale.X, rect.Height * p_Scale.Y);
				Vector2 texCoordTL(rect.X / (float)texWidth + correction.X, rect.Y / (float)texHeight + correction.X);
				Vector2 texCoordBR((rect.X + rect.Width) / (float)texWidth - correction.X, (rect.Y + rect.Height) / (float)texHeight - correction.Y);

				SpriteBatchItem& item = m_BatchItemList[m_ItemCount++];
				item.TextureID = texture.GetID();
				item.Depth = p_Depth;

				item.VertexTL.Position.X = p_Position.X + origin.X + offset.X;
				item.VertexTL.Position.Y = p_Position.Y + origin.Y + offset.Y;
				item.VertexTL.Color.R = p_Color.GetRed();
				item.VertexTL.Color.G = p_Color.GetGreen();
				item.VertexTL.Color.B = p_Color.GetBlue();
				item.VertexTL.Color.A = p_Color.GetAlpha();
				item.VertexTL.TexCoord.X = texCoordTL.X;
				item.VertexTL.TexCoord.Y = texCoordTL.Y;

				RotateAbout(p_Position, p_Rotation, item.VertexTL.Position);
				FlipAbout(p_Position, p_Orientation, item.VertexTL.Position);

				item.VertexTR.Position.X = p_Position.X + origin.X + size.X + offset.X;
				item.VertexTR.Position.Y = p_Position.Y + origin.Y + offset.Y;
				item.VertexTR.Color.R = p_Color.GetRed();
				item.VertexTR.Color.G = p_Color.GetGreen();
				item.VertexTR.Color.B = p_Color.GetBlue();
				item.VertexTR.Color.A = p_Color.GetAlpha();
				item.VertexTR.TexCoord.X = texCoordBR.X;
				item.VertexTR.TexCoord.Y = texCoordTL.Y;

				RotateAbout(p_Position, p_Rotation, item.VertexTR.Position);
				FlipAbout(p_Position, p_Orientation, item.VertexTR.Position);

				item.VertexBL.Position.X = p_Position.X + origin.X + offset.X;
				item.VertexBL.Position.Y = p_Position.Y + origin.Y + size.Y + offset.Y;
				item.VertexBL.Color.R = p_Color.GetRed();
				item.VertexBL.Color.G = p_Color.GetGreen();
				item.VertexBL.Color.B = p_Color.GetBlue();
				item.VertexBL.Color.A = p_Color.GetAlpha();
				item.VertexBL.TexCoord.X = texCoordTL.X;
				item.VertexBL.TexCoord.Y = texCoordBR.Y;

				RotateAbout(p_Position, p_Rotation, item.VertexBL.Position);
				FlipAbout(p_Position, p_Orientation, item.VertexBL.Position);

				item.VertexBR.Position.X = p_Position.X + origin.X + size.X + offset.X;
				item.VertexBR.Position.Y = p_Position.Y + origin.Y + size.Y + offset.Y;
				item.VertexBR.Color.R = p_Color.GetRed();
				item.VertexBR.Color.G = p_Color.GetGreen();
				item.VertexBR.Color.B = p_Color.GetBlue();
				item.VertexBR.Color.A = p_Color.GetAlpha();
				item.VertexBR.TexCoord.X = texCoordBR.X;
				item.VertexBR.TexCoord.Y = texCoordBR.Y;

				RotateAbout(p_Position, p_Rotation, item.VertexBR.Position);
				FlipAbout(p_Position, p_Orientation, item.VertexBR.Position);

				offset.X += spacing * p_Scale.X;
			}
		}

		return false;
	}

	bool SpriteBatch::End()
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[SpriteBatch::End] Cannot end a pair without starting.");
			return false;
		}

		switch (m_SortMode)
		{
			case SortMode::Texture:
				std::sort(std::begin(m_BatchItemList), std::end(m_BatchItemList), [](const SpriteBatchItem& p_ItemA, const SpriteBatchItem& p_ItemB) { return p_ItemA.TextureID > p_ItemB.TextureID; });
				break;
			case SortMode::FrontToBack:
				std::sort(std::begin(m_BatchItemList), std::end(m_BatchItemList), [](const SpriteBatchItem& p_ItemA, const SpriteBatchItem& p_ItemB) { return p_ItemA.Depth > p_ItemB.Depth; });
				break;
			case SortMode::BackToFront:
				std::sort(std::begin(m_BatchItemList), std::end(m_BatchItemList), [](const SpriteBatchItem& p_ItemA, const SpriteBatchItem& p_ItemB) { return p_ItemA.Depth < p_ItemB.Depth; });
				break;
		}

		switch (m_BlendMode)
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

		switch (m_RasterizerState)
		{
			case RasterizerState::None:
				glDisable(GL_CULL_FACE);
				break;
			case RasterizerState::CullClockwise:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				break;
			case RasterizerState::CullCounterClockwise:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				break;
		}

		if (m_ItemCount > 0)
			Render();

		m_WithinDrawPair = false;

		return true;
	}

	void SpriteBatch::Render()
	{
		int length = 0;
		int texID = -1;

		for (int i = 0; i < m_ItemCount; ++i)
		{
			SpriteBatchItem& item = m_BatchItemList[i];

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

			m_VertexBuffer[length * 4 + 0] = item.VertexBL;
			m_VertexBuffer[length * 4 + 1] = item.VertexBR;
			m_VertexBuffer[length * 4 + 2] = item.VertexTR;
			m_VertexBuffer[length * 4 + 3] = item.VertexTL;

			length++;
		}

		Flush(texID, length);
	}

	void SpriteBatch::Flush(int p_TextureID, int p_Length)
	{
		// Ensure there's something to draw.
		if (p_Length == 0)
			return;

		// Enable textures and bind the current ID.
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, p_TextureID);

		// Bind the vertex array.
		glBindVertexArray(m_VertexArrayObject);

		// Bind the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);

		// Option 1: Insert subset into buffer.
		glBufferSubData(GL_ARRAY_BUFFER, 0, p_Length * 4 * sizeof(VertexPositionColorTexture), m_VertexBuffer);

		// Option 2: Write to buffer mapping.
		/*
		glBufferData(GL_ARRAY_BUFFER, m_VertexBuffer.size() * sizeof(VertexPositionColorTexture), nullptr, GL_DYNAMIC_DRAW);
		VertexPositionColorTexture* map = reinterpret_cast<VertexPositionColorTexture*>(
		glMapBufferRange(GL_ARRAY_BUFFER,
		0,
		p_Length * sizeof(VertexPositionColorTexture),
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)
		);
		std::copy(m_VertexBuffer.begin(), m_VertexBuffer.end(), map);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		*/

		// Bind the element buffer and draw.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
		glDrawElements(GL_TRIANGLES, p_Length * 6, GL_UNSIGNED_SHORT, nullptr);

		// Clear bindings.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Disable textures.
		glDisable(GL_TEXTURE_2D);

		m_FlushCount++;
	}

	void SpriteBatch::RotateAbout(const Vector2& p_Position, float p_Rotation, VertexVector2& p_Vertex)
	{
		float cos = cosf(p_Rotation);
		float sin = sinf(p_Rotation);

		p_Vertex.X -= p_Position.X;
		p_Vertex.Y -= p_Position.Y;

		float rotX = p_Vertex.X * cos - p_Vertex.Y * sin;
		float rotY = p_Vertex.X * sin + p_Vertex.Y * cos;

		p_Vertex.X = rotX + p_Position.X;
		p_Vertex.Y = rotY + p_Position.Y;
	}

	void SpriteBatch::FlipAbout(const Vector2& p_Position, Orientation p_Orientation, VertexVector2& p_Vertex)
	{
		// Flip texture coordinates for orientation.
		if ((p_Orientation & Orientation::FlipHorizontal) == Orientation::FlipHorizontal)
			p_Vertex.X = p_Position.X - (p_Vertex.X - p_Position.X);
		if ((p_Orientation & Orientation::FlipVertical) == Orientation::FlipVertical)
			p_Vertex.Y = p_Position.Y - (p_Vertex.Y - p_Position.Y);
	}
}
