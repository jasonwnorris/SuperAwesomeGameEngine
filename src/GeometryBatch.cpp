// GeometryBatch.cpp

// OpenGL Includes
#include <gl\glew.h>
// SAGE Includes
#include <SAGE\GeometryBatch.hpp>
// SDL Includes
#include <SDL2\SDL.h>

namespace SAGE
{
	GeometryBatch::GeometryBatch()
	{
		mWithinDrawPair = false;
		mItemCount = 0;
		mFlushCount = 0;
	}

	GeometryBatch::~GeometryBatch()
	{
		Finalize();
	}

	int GeometryBatch::GetDrawCallCount() const
	{
		return mFlushCount;
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
		glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeVPC, nullptr, GL_DYNAMIC_DRAW);

		// Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeVPC, (GLvoid*)(sizeFloat * 0));
		// Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeVPC, (GLvoid*)(sizeFloat * 2));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return true;
	}

	bool GeometryBatch::Finalize()
	{
		glDeleteVertexArrays(1, &mVertexArrayObject);
		glDeleteBuffers(1, &mVertexBufferObject);
		glDeleteBuffers(1, &mIndexBufferObject);

		return true;
	}

	bool GeometryBatch::Begin(Effect& pEffect, const Camera2D& pCamera)
	{
		if (mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::Begin] Cannot nest draw pairs.");
			return false;
		}

		mWithinDrawPair = true;
		mItemCount = 0;
		mFlushCount = 0;

		pEffect.SetProjection(pCamera.GetProjectionMatrix());
		pEffect.SetModelView(pCamera.GetModelViewMatrix());
		pEffect.Use();

		return true;
	}

	bool GeometryBatch::DrawLine(const Vector2& pPositionA, const Vector2& pPositionB, const Color& pColor)
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawLine] Must start a draw pair first.");
			return false;
		}

		GeometryBatchItem& item = mBatchItemList[mItemCount++];

		item.VertexA.Position.X = pPositionA.X;
		item.VertexA.Position.Y = pPositionA.Y;
		item.VertexA.Color.R = pColor.GetRed();
		item.VertexA.Color.G = pColor.GetGreen();
		item.VertexA.Color.B = pColor.GetBlue();
		item.VertexA.Color.A = pColor.GetAlpha();

		item.VertexB.Position.X = pPositionB.X;
		item.VertexB.Position.Y = pPositionB.Y;
		item.VertexB.Color.R = pColor.GetRed();
		item.VertexB.Color.G = pColor.GetGreen();
		item.VertexB.Color.B = pColor.GetBlue();
		item.VertexB.Color.A = pColor.GetAlpha();

		return true;
	}

	bool GeometryBatch::DrawLines(const std::vector<Vector2>& pPositions, const Color& pColor)
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawLines] Must start a draw pair first.");
			return false;
		}

		if (pPositions.size() < 2)
		{
			SDL_Log("[GeometryBatch::DrawLines] Must supply two or more positions to draw.");
			return false;
		}

		for (int i = 1; i < (int)pPositions.size(); ++i)
		{
			if (!DrawLine(pPositions[i - 1], pPositions[i], pColor))
			{
				return false;
			}
		}

		return true;
	}

	bool GeometryBatch::DrawRectangle(const Vector2& pTopLeft, const Vector2& pBottomRight, const Color& pColor)
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawRectangle] Must start a draw pair first.");
			return false;
		}

		Vector2 TL(pTopLeft.X, pTopLeft.Y);
		Vector2 TR(pBottomRight.X, pTopLeft.Y);
		Vector2 BR(pBottomRight.X, pBottomRight.Y);
		Vector2 BL(pTopLeft.X, pBottomRight.Y);

		return DrawLine(TL, TR, pColor) && DrawLine(TR, BR, pColor) && DrawLine(BR, BL, pColor) && DrawLine(BL, TL, pColor);
	}

	bool GeometryBatch::DrawRectangle(const Rectangle& pRectangle, const Color& pColor)
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawRectangle] Must start a draw pair first.");
			return false;
		}

		return DrawRectangle(Vector2(pRectangle.X, pRectangle.Y), Vector2(pRectangle.X + pRectangle.Width, pRectangle.Y + pRectangle.Height), pColor);
	}

	bool GeometryBatch::DrawCircle(const Vector2& pPosition, float pRadius, const Color& pColor, int pCount)
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawCircle] Must start a draw pair first.");
			return false;
		}

		float step = (float)(2.0f * M_PI) / (float)pCount;
		std::vector<float> cosList(pCount + 1);
		std::vector<float> sinList(pCount + 1);

		// Pre-calculate multi-use trigonometry. 
		for (int i = 0; i < pCount + 1; ++i)
		{
			cosList[i] = cosf(i * step) * pRadius;
			sinList[i] = sinf(i * step) * pRadius;
		}

		for (int i = 0; i < pCount; ++i)
		{
			Vector2 positionA(pPosition.X + cosList[i], pPosition.Y + sinList[i]);
			Vector2 positionB(pPosition.X + cosList[i + 1], pPosition.Y + sinList[i + 1]);

			if (!DrawLine(positionA, positionB, pColor))
			{
				return false;
			}
		}

		return true;
	}

	bool GeometryBatch::DrawBezier(const Vector2& pStartPosition, const Vector2& pEndPosition, const Vector2& pControlPoint, const Color& pColor, int pCount)
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawBezier] Must start a draw pair first.");
			return false;
		}

		float step = 1.0f / (float)pCount;

		for (int i = 0; i < pCount; ++i)
		{
			float tA = i * step;
			float tB = (i + 1) * step;
			float invtA = 1.0f - tA;
			float invtB = 1.0f - tB;

			Vector2 positionA = pStartPosition * invtA * invtA + pControlPoint * 2.0f * invtA * tA + pEndPosition * tA * tA;
			Vector2 positionB = pStartPosition * invtB * invtB + pControlPoint * 2.0f * invtB * tB + pEndPosition * tB * tB;

			if (!DrawLine(positionA, positionB, pColor))
			{
				return false;
			}
		}

		return true;
	}

	bool GeometryBatch::DrawBezier(const Vector2& pStartPosition, const Vector2& pEndPosition, const Vector2& pControlPointA, const Vector2& pControlPointB, const Color& pColor, int pCount)
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::DrawBezier] Must start a draw pair first.");
			return false;
		}

		float step = 1.0f / (float)pCount;

		for (int i = 0; i < pCount; ++i)
		{
			float tA = i * step;
			float tB = (i + 1) * step;
			float invtA = 1.0f - tA;
			float invtB = 1.0f - tB;

			Vector2 positionA = pStartPosition * invtA * invtA * invtA + pControlPointA * 3.0f * invtA * invtA * tA + pControlPointB * 3.0f * invtA * tA * tA + pEndPosition * tA * tA * tA;
			Vector2 positionB = pStartPosition * invtB * invtB * invtB + pControlPointA * 3.0f * invtB * invtB * tB + pControlPointB * 3.0f * invtB * tB * tB + pEndPosition * tB * tB * tB;

			if (!DrawLine(positionA, positionB, pColor))
			{
				return false;
			}
		}

		return true;
	}

	bool GeometryBatch::End()
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::End] Cannot end a pair without starting.");
			return false;
		}

		if (mItemCount > 0)
			Render();

		mWithinDrawPair = false;

		return true;
	}

	void GeometryBatch::Render()
	{
		int length = 0;
		int texID = -1;

		for (int i = 0; i < mItemCount; ++i)
		{
			GeometryBatchItem& item = mBatchItemList[i];

			if (length * 2 > MaxVertexCount)
			{
				Flush(length);
				length = 0;
			}

			mVertexBuffer[length * 2 + 0] = item.VertexA;
			mVertexBuffer[length * 2 + 1] = item.VertexB;

			length++;
		}

		Flush(length);
	}

	void GeometryBatch::Flush(int pLength)
	{
		// Ensure there's something to draw.
		if (pLength == 0)
			return;

		// Bind the vertex array.
		glBindVertexArray(mVertexArrayObject);

		// Bind the vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);

		// Insert subset into buffer.
		glBufferSubData(GL_ARRAY_BUFFER, 0, pLength * 2 * sizeof(VertexPositionColor), mVertexBuffer);

		// Bind the element buffer and draw.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferObject);
		glDrawElements(GL_LINES, pLength * 2, GL_UNSIGNED_SHORT, nullptr);

		// Clear bindings.
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		mFlushCount++;
	}
}
