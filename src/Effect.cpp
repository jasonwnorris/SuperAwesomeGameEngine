// Effect.cpp

// SDL Includes
#include <SDL2/SDL.h>
// SAGE Includes
#include <SAGE/Effect.hpp>
// STL Includes
#include <iostream>
#include <fstream>
#include <string>

namespace SAGE
{
	const std::string Effect::PositionColorVertexSource =
		"#version 330 core/n/n"
		"uniform mat4 uProjectionMatrix;/n"
		"uniform mat4 uModelViewMatrix;/n/n"
		"layout(location = 0) in vec2 Position;/n"
		"layout(location = 1) in vec4 Color;/n/n"
		"out vec4 vs_fs_color;/n/n"
		"void main()/n"
		"{/n"
		"	vs_fs_color = Color;/n/n"
		"	gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(Position, 1.0, 1.0);/n"
		"}";

	const std::string Effect::PositionColorFragmentSource =
		"#version 330 core/n/n"
		"in vec4 vs_fs_color;/n/n"
		"void main()/n"
		"{/n"
		"	gl_FragColor = vs_fs_color;/n"
		"}";

	const std::string Effect::PositionColorTextureVertexSource =
		"#version 330 core/n/n"
		"uniform mat4 uProjectionMatrix;/n"
		"uniform mat4 uModelViewMatrix;/n/n"
		"layout(location = 0) in vec2 Position;/n"
		"layout(location = 1) in vec4 Color;/n"
		"layout(location = 2) in vec2 TexCoord;/n/n"
		"out vec4 vs_fs_color;/n"
		"out vec2 vs_fs_texcoord;/n/n"
		"void main()/n"
		"{/n"
		"	vs_fs_color = Color;/n"
		"	vs_fs_texcoord = TexCoord;/n/n"
		"	gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(Position, 1.0, 1.0);/n"
		"}";

	const std::string Effect::PositionColorTextureFragmentSource =
		"#version 330 core/n/n"
		"uniform sampler2D uTextureSampler;/n/n"
		"in vec4 vs_fs_color;/n"
		"in vec2 vs_fs_texcoord;/n/n"
		"void main()/n"
		"{/n"
		"	gl_FragColor = texture2D(uTextureSampler, vs_fs_texcoord) * vs_fs_color;/n"
		"}";

	Effect::Effect()
	{
	}

	Effect::~Effect()
	{
		Finalize();
	}

	bool Effect::Create(BasicType p_BasicType)
	{
		if (!Initialize())
			return false;

		switch (p_BasicType)
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
		m_Program = glCreateProgram();

		return true;
	}

	bool Effect::Finalize()
	{
		glUseProgram(0);
		glDeleteProgram(m_Program);

		return true;
	}

	bool Effect::Attach(const std::string& p_Source, ShaderType p_Type)
	{
		const GLchar* source = p_Source.c_str();

		GLint status;
		GLuint shader = glCreateShader(p_Type);
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			GLint length = 0;
			GLchar message[256];
			glGetShaderInfoLog(shader, length, &length, message);

			SDL_Log("[Effect::Attach] Error compiling shader: ", message);

			return false;
		}
		else
		{
			glAttachShader(m_Program, shader);
		}

		glDeleteShader(shader);

		return true;
	}

	bool Effect::AttachFromFile(const std::string& p_Filename, ShaderType p_Type)
	{
		std::ifstream file(p_Filename);
		if (file.is_open())
		{
			std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			file.close();

			return Attach(buffer, p_Type);
		}

		return false;
	}

	bool Effect::Link()
	{
		GLint linked = GL_FALSE;

		glLinkProgram(m_Program);
		glGetProgramiv(m_Program, GL_LINK_STATUS, &linked);
		if (linked != GL_TRUE)
		{
			GLsizei length = 0;
			glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &length);
			GLchar* message = new GLchar[length + 1];
			glGetProgramInfoLog(m_Program, length, &length, message);

			SDL_Log("[Effect::Link] Shader linking failed: ", message);
			delete [] message;

			return false;
		}

		// TODO: Make matrix acquisition more dynamic.
		m_ProjectionMatrixLocation = glGetUniformLocation(m_Program, "uProjectionMatrix");
		m_ModelViewMatrixLocation = glGetUniformLocation(m_Program, "uModelViewMatrix");

		return true;
	}

	void Effect::Use()
	{
		glUseProgram(m_Program);
	}

	void Effect::PrintUniforms()
	{
		GLint total;
		glGetProgramiv(m_Program, GL_ACTIVE_UNIFORMS, &total);
		for (GLint i = 0; i < total; i++)
		{
			int number = 0;
			int length = 0;
			GLenum type = GL_ZERO;
			char name[128];
			glGetActiveUniform(m_Program, i, 127, &length, &number, &type, name);
			name[length] = 0;

			std::cout << "Uniform #" << (i + 1) << ": " << name << std::endl;
		}
	}

	GLint Effect::GetUniform(const std::string& p_Name)
	{
		return glGetUniformLocation(m_Program, p_Name.c_str());
	}

	void Effect::SetProjection(const glm::mat4& p_Matrix)
	{
		glUniformMatrix4fv(m_ProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(p_Matrix));
	}

	void Effect::SetModelView(const glm::mat4& p_Matrix)
	{
		glUniformMatrix4fv(m_ModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(p_Matrix));
	}

	void Effect::SetUniform(const std::string& p_Name, int p_Value)
	{
		if (m_Uniforms.find(p_Name) == m_Uniforms.end())
		{
			m_Uniforms[p_Name] = glGetUniformLocation(m_Program, p_Name.c_str());
		}

		glUniform1i(m_Uniforms[p_Name], p_Value);
	}

	void Effect::SetUniform(const std::string& p_Name, float p_Value)
	{
		if (m_Uniforms.find(p_Name) == m_Uniforms.end())
		{
			m_Uniforms[p_Name] = glGetUniformLocation(m_Program, p_Name.c_str());
		}

		glUniform1f(m_Uniforms[p_Name], p_Value);
	}
}
