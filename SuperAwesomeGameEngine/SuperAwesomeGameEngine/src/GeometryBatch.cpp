// GeometryBatch.cpp

// GL Includes
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeVPC, (GLvoid*)(sizeFloat * 0));
		// Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeVPC, (GLvoid*)(sizeFloat * 3));

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

	int GeometryBatch::GetDrawCallCount() const
	{
		return mFlushCount;
	}

	bool GeometryBatch::Begin()
	{
		if (mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::Begin] Cannot nest draw pairs.");
			return false;
		}

		mWithinDrawPair = true;
		mItemCount = 0;
		mFlushCount = 0;

		return true;
	}

	bool GeometryBatch::Draw(const HGF::Vector2& pPositionA, const HGF::Vector2& pPositionB, const HGF::Color& pColor)
	{
		if (!mWithinDrawPair)
		{
			SDL_Log("[GeometryBatch::Draw] Must start a draw pair first.");
			return false;
		}

		GeometryBatchItem& item = mBatchItemList[mItemCount++];

		item.VertexA.Position.X = pPositionA.X;
		item.VertexA.Position.Y = pPositionA.Y;
		item.VertexA.Position.Z = 0.0f;
		item.VertexA.Color.R = pColor.GetRed();
		item.VertexA.Color.G = pColor.GetGreen();
		item.VertexA.Color.B = pColor.GetBlue();
		item.VertexA.Color.A = pColor.GetAlpha();

		item.VertexB.Position.X = pPositionB.X;
		item.VertexB.Position.Y = pPositionB.Y;
		item.VertexB.Position.Z = 0.0f;
		item.VertexB.Color.R = pColor.GetRed();
		item.VertexB.Color.G = pColor.GetGreen();
		item.VertexB.Color.B = pColor.GetBlue();
		item.VertexB.Color.A = pColor.GetAlpha();

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