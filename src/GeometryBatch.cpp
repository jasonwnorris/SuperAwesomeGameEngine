// GeometryBatch.cpp

// OpenGL Includes
#include <GL/glew.h>
// SAGE Includes
#include <SAGE/GeometryBatch.hpp>
// SDL Includes
#include <SDL2/SDL.h>

namespace SAGE
{
	GeometryBatch::GeometryBatch()
	{
		m_WithinDrawPair = false;
		m_ItemCount = 0;
		m_FlushCount = 0;
	}

	GeometryBatch::~GeometryBatch()
	{
		Finalize();
	}

	int GeometryBatch::GetDrawCallCount() const
	{
		return m_FlushCount;
	}

	bool GeometryBatch::Initialize()
	{
		GLsizei sizeUShort = sizeof(GLushort);
		GLsizei sizeFloat = sizeof(GLfloat);
		GLsizei sizeVPC = sizeof(VertexPositionColor);

		// Enable GLew.
		glewExperimental = GL_TRUE;
		GLenum res = glewInit();
		if (res != GLEW_OK)
		{
			SDL_Log("[GeometryBatch::Initialize] GLEW failed to initialize: %s", glewGetErrorString(res));
			return false;
		}

		GLushort indexData[MaxIndexCount];
		for (int i = 0; i < MaxIndexCount; i++)
		{
			indexData[i] = i;
		}

		m_IndexBufferObject = -1;
		glGenBuffers(1, &m_IndexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndexCount * sizeUShort, indexData, GL_STATIC_DRAW);

		m_VertexArrayObject = -1;
		glGenVertexArrays(1, &m_VertexArrayObject);
		glBindVertexArray(m_VertexArrayObject);

		m_VertexBufferObject = -1;
		glGenBuffers(1, &m_VertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeVPC, nullptr, GL_DYNAMIC_DRAW);

		#define BUFFER_OFFSET(i) ((char*)0 + (i))

		// Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeVPC, BUFFER_OFFSET(sizeFloat * 0));
		// Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeVPC, BUFFER_OFFSET(sizeFloat * 2));

		#undef BUFFER_OFFSET

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return true;
	}

	bool GeometryBatch::Finalize()
	{
		glDeleteVertexArrays(1, &m_VertexArrayObject);
		glDeleteBuffers(1, &m_VertexBufferObject);
		glDeleteBuffers(1, &m_IndexBufferObject);

		return true;
	}

	bool GeometryBatch::Begin(Effect& p_Effect, const Camera2D& p_Camera)
	{
		if (m_WithinDrawPair)
		{
			SDL_Log("[GeometryBatch::Begin] Cannot nest draw pairs.");
			return false;
		}

		m_WithinDrawPair = true;
		m_ItemCount = 0;
		m_FlushCount = 0;

		p_Effect.SetProjection(p_Camera.GetProjectionMatrix());
		p_Effect.SetModelView(p_Camera.GetModelViewMatrix());
		p_Effect.Use();

		return true;
	}

	bool GeometryBatch::DrawLine(const Vector2& p_PositionA, const Vector2& p_PositionB, const Color& p_Color)
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawLine] Must start a draw pair first.");
			return false;
		}

		GeometryBatchItem& item = m_BatchItemList[m_ItemCount++];

		item.VertexA.Position.X = p_PositionA.X;
		item.VertexA.Position.Y = p_PositionA.Y;
		item.VertexA.Color.R = p_Color.GetRed();
		item.VertexA.Color.G = p_Color.GetGreen();
		item.VertexA.Color.B = p_Color.GetBlue();
		item.VertexA.Color.A = p_Color.GetAlpha();

		item.VertexB.Position.X = p_PositionB.X;
		item.VertexB.Position.Y = p_PositionB.Y;
		item.VertexB.Color.R = p_Color.GetRed();
		item.VertexB.Color.G = p_Color.GetGreen();
		item.VertexB.Color.B = p_Color.GetBlue();
		item.VertexB.Color.A = p_Color.GetAlpha();

		return true;
	}

	bool GeometryBatch::DrawLines(const std::vector<Vector2>& p_Positions, const Color& p_Color)
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawLines] Must start a draw pair first.");
			return false;
		}

		if (p_Positions.size() < 2)
		{
			SDL_Log("[GeometryBatch::DrawLines] Must supply two or more positions to draw.");
			return false;
		}

		for (int i = 1; i < (int)p_Positions.size(); ++i)
		{
			if (!DrawLine(p_Positions[i - 1], p_Positions[i], p_Color))
			{
				return false;
			}
		}

		return true;
	}

	bool GeometryBatch::DrawRectangle(const Vector2& p_TopLeft, const Vector2& p_BottomRight, const Color& p_Color)
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawRectangle] Must start a draw pair first.");
			return false;
		}

		Vector2 TL(p_TopLeft.X, p_TopLeft.Y);
		Vector2 TR(p_BottomRight.X, p_TopLeft.Y);
		Vector2 BR(p_BottomRight.X, p_BottomRight.Y);
		Vector2 BL(p_TopLeft.X, p_BottomRight.Y);

		return DrawLine(TL, TR, p_Color) && DrawLine(TR, BR, p_Color) && DrawLine(BR, BL, p_Color) && DrawLine(BL, TL, p_Color);
	}

	bool GeometryBatch::DrawRectangle(const Rectangle& p_Rectangle, const Color& p_Color)
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawRectangle] Must start a draw pair first.");
			return false;
		}

		return DrawRectangle(Vector2(p_Rectangle.X, p_Rectangle.Y), Vector2(p_Rectangle.X + p_Rectangle.Width, p_Rectangle.Y + p_Rectangle.Height), p_Color);
	}

	bool GeometryBatch::DrawCircle(const Vector2& p_Position, float p_Radius, const Color& p_Color, int p_Count)
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawCircle] Must start a draw pair first.");
			return false;
		}

		float step = (float)(2.0f * M_PI) / (float)p_Count;
		std::vector<float> cosList(p_Count + 1);
		std::vector<float> sinList(p_Count + 1);

		// Pre-calculate multi-use trigonometry. 
		for (int i = 0; i < p_Count + 1; ++i)
		{
			cosList[i] = cosf(i * step) * p_Radius;
			sinList[i] = sinf(i * step) * p_Radius;
		}

		for (int i = 0; i < p_Count; ++i)
		{
			Vector2 positionA(p_Position.X + cosList[i], p_Position.Y + sinList[i]);
			Vector2 positionB(p_Position.X + cosList[i + 1], p_Position.Y + sinList[i + 1]);

			if (!DrawLine(positionA, positionB, p_Color))
			{
				return false;
			}
		}

		return true;
	}

	bool GeometryBatch::DrawBezier(const Vector2& p_StartPosition, const Vector2& p_EndPosition, const Vector2& p_ControlPoint, const Color& p_Color, int p_Count)
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawBezier] Must start a draw pair first.");
			return false;
		}

		float step = 1.0f / (float)p_Count;

		for (int i = 0; i < p_Count; ++i)
		{
			float tA = i * step;
			float tB = (i + 1) * step;
			float invtA = 1.0f - tA;
			float invtB = 1.0f - tB;

			Vector2 positionA = p_StartPosition * invtA * invtA + p_ControlPoint * 2.0f * invtA * tA + p_EndPosition * tA * tA;
			Vector2 positionB = p_StartPosition * invtB * invtB + p_ControlPoint * 2.0f * invtB * tB + p_EndPosition * tB * tB;

			if (!DrawLine(positionA, positionB, p_Color))
			{
				return false;
			}
		}

		return true;
	}

	bool GeometryBatch::DrawBezier(const Vector2& p_StartPosition, const Vector2& p_EndPosition, const Vector2& p_ControlPointA, const Vector2& p_ControlPointB, const Color& p_Color, int p_Count)
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawBezier] Must start a draw pair first.");
			return false;
		}

		float step = 1.0f / (float)p_Count;

		for (int i = 0; i < p_Count; ++i)
		{
			float tA = i * step;
			float tB = (i + 1) * step;
			float invtA = 1.0f - tA;
			float invtB = 1.0f - tB;

			Vector2 positionA = p_StartPosition * invtA * invtA * invtA + p_ControlPointA * 3.0f * invtA * invtA * tA + p_ControlPointB * 3.0f * invtA * tA * tA + p_EndPosition * tA * tA * tA;
			Vector2 positionB = p_StartPosition * invtB * invtB * invtB + p_ControlPointA * 3.0f * invtB * invtB * tB + p_ControlPointB * 3.0f * invtB * tB * tB + p_EndPosition * tB * tB * tB;

			if (!DrawLine(positionA, positionB, p_Color))
			{
				return false;
			}
		}

		return true;
	}

	bool GeometryBatch::End()
	{
		if (!m_WithinDrawPair)
		{
			SDL_Log("[GeometryBatch::End] Cannot end a pair without starting.");
			return false;
		}

		if (m_ItemCount > 0)
			Render();

		m_WithinDrawPair = false;

		return true;
	}

	void GeometryBatch::Render()
	{
		int length = 0;

		for (int i = 0; i < m_ItemCount; ++i)
		{
			GeometryBatchItem& item = m_BatchItemList[i];

			if (length * 2 > MaxVertexCount)
			{
				Flush(length);
				length = 0;
			}

			m_VertexBuffer[length * 2 + 0] = item.VertexA;
			m_VertexBuffer[length * 2 + 1] = item.VertexB;

			length++;
		}

		Flush(length);
	}

	void GeometryBatch::Flush(int p_Length)
	{
		// Ensure there's something to draw.
		if (p_Length == 0)
			return;

		// Bind the vertex array.
		glBindVertexArray(m_VertexArrayObject);

		// Bind the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);

		// Insert subset into buffer.
		glBufferSubData(GL_ARRAY_BUFFER, 0, p_Length * 2 * sizeof(VertexPositionColor), m_VertexBuffer);

		// Bind the element buffer and draw.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
		glDrawElements(GL_LINES, p_Length * 2, GL_UNSIGNED_SHORT, nullptr);

		// Clear bindings.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_FlushCount++;
	}
}
