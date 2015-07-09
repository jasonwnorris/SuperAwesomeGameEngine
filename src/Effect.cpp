// Effect.cpp

// SDL Includes
#include <SDL2\SDL.h>
// SAGE Includes
#include <SAGE\Effect.hpp>
// STL Includes
#include <iostream>
#include <fstream>
#include <string>

namespace SAGE
{
	const std::string Effect::PositionColorVertexSource =
		"#version 330 core\n\n"
		"uniform mat4 uProjectionMatrix;\n"
		"uniform mat4 uModelViewMatrix;\n\n"
		"layout(location = 0) in vec2 Position;\n"
		"layout(location = 1) in vec4 Color;\n\n"
		"out vec4 vs_fs_color;\n\n"
		"void main()\n"
		"{\n"
		"	vs_fs_color = Color;\n\n"
		"	gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(Position, 1.0, 1.0);\n"
		"}";

	const std::string Effect::PositionColorFragmentSource =
		"#version 330 core\n\n"
		"in vec4 vs_fs_color;\n\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = vs_fs_color;\n"
		"}";

	const std::string Effect::PositionColorTextureVertexSource =
		"#version 330 core\n\n"
		"uniform mat4 uProjectionMatrix;\n"
		"uniform mat4 uModelViewMatrix;\n\n"
		"layout(location = 0) in vec2 Position;\n"
		"layout(location = 1) in vec4 Color;\n"
		"layout(location = 2) in vec2 TexCoord;\n\n"
		"out vec4 vs_fs_color;\n"
		"out vec2 vs_fs_texcoord;\n\n"
		"void main()\n"
		"{\n"
		"	vs_fs_color = Color;\n"
		"	vs_fs_texcoord = TexCoord;\n\n"
		"	gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(Position, 1.0, 1.0);\n"
		"}";

	const std::string Effect::PositionColorTextureFragmentSource =
		"#version 330 core\n\n"
		"uniform sampler2D uTextureSampler;\n\n"
		"in vec4 vs_fs_color;\n"
		"in vec2 vs_fs_texcoord;\n\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = texture2D(uTextureSampler, vs_fs_texcoord) * vs_fs_color;\n"
		"}";

	Effect::Effect()
	{
	}

	Effect::~Effect()
	{
		Finalize();
	}

	bool Effect::Create(BasicType pBasicType)
	{
		if (!Initialize())
			return false;

		switch (pBasicType)
		{
			case BasicType::PositionColor:
				if (!Attach(PositionColorVertexSource, ShaderType::Vertex))
					return false;
				if (!Attach(PositionColorFragmentSource, ShaderType::Fragment))
					return false;
				if (!Link())
					return false;
				return true;
			case BasicType::PositionColorTexture:
				if (!Attach(PositionColorTextureVertexSource, ShaderType::Vertex))
					return false;
				if (!Attach(PositionColorTextureFragmentSource, ShaderType::Fragment))
					return false;
				if (!Link())
					return false;
				SetUniform("uTextureSampler", 0);
				return true;
		}

		return false;
	}

	bool Effect::Initialize()
	{
		mProgram = glCreateProgram();

		return true;
	}

	bool Effect::Finalize()
	{
		glUseProgram(0);
		glDeleteProgram(mProgram);

		return true;
	}

	bool Effect::Attach(const std::string& pSource, ShaderType pType)
	{
		const GLchar* source = pSource.c_str();

		GLint status;
		GLuint shader = glCreateShader(pType);
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			GLint length;
			GLchar message[256];
			glGetShaderInfoLog(shader, length, &length, message);

			SDL_Log("[Effect::Attach] Error compiling shader: ", message);

			return false;
		}
		else
		{
			glAttachShader(mProgram, shader);
		}

		glDeleteShader(shader);

		return true;
	}

	bool Effect::AttachFromFile(const std::string& pFilename, ShaderType pType)
	{
		std::ifstream file(pFilename);
		if (file.is_open())
		{
			std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			file.close();

			return Attach(buffer, pType);
		}

		return false;
	}

	bool Effect::Link()
	{
		GLint linked = GL_FALSE;

		glLinkProgram(mProgram);
		glGetProgramiv(mProgram, GL_LINK_STATUS, &linked);
		if (linked != GL_TRUE)
		{
			GLsizei length;
			glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &length);
			GLchar* message = new GLchar[length + 1];
			glGetProgramInfoLog(mProgram, length, &length, message);

			SDL_Log("[Effect::Link] Shader linking failed: ", message);
			delete [] message;

			return false;
		}

		// TODO: Make matrix acquisition more dynamic.
		mProjectionMatrixLocation = glGetUniformLocation(mProgram, "uProjectionMatrix");
		mModelViewMatrixLocation = glGetUniformLocation(mProgram, "uModelViewMatrix");

		return true;
	}

	void Effect::Use()
	{
		glUseProgram(mProgram);
	}

	void Effect::PrintUniforms()
	{
		GLint total;
		glGetProgramiv(mProgram, GL_ACTIVE_UNIFORMS, &total);
		for (GLint i = 0; i < total; i++)
		{
			int number;
			int length;
			GLenum type = GL_ZERO;
			char name[128];
			glGetActiveUniform(mProgram, i, 127, &length, &number, &type, name);
			name[length] = 0;

			std::cout << "Uniform #" << (i + 1) << ": " << name << std::endl;
		}
	}

	GLint Effect::GetUniform(const std::string& pName)
	{
		return glGetUniformLocation(mProgram, pName.c_str());
	}

	void Effect::SetProjection(const glm::mat4& pMatrix)
	{
		glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(pMatrix));
	}

	void Effect::SetModelView(const glm::mat4& pMatrix)
	{
		glUniformMatrix4fv(mModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(pMatrix));
	}

	void Effect::SetUniform(const std::string& pName, int pValue)
	{
		if (mUniforms.find(pName) == mUniforms.end())
		{
			mUniforms[pName] = glGetUniformLocation(mProgram, pName.c_str());
		}

		glUniform1i(mUniforms[pName], pValue);
	}

	void Effect::SetUniform(const std::string& pName, float pValue)
	{
		if (mUniforms.find(pName) == mUniforms.end())
		{
			mUniforms[pName] = glGetUniformLocation(mProgram, pName.c_str());
		}

		glUniform1f(mUniforms[pName], pValue);
	}
}
