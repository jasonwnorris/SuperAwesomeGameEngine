// Effect.hpp

#ifndef __SAGE_EFFECT_HPP__
#define __SAGE_EFFECT_HPP__

// GL Includes
#include <gl\glew.h>
// GLM Includes
#define GLM_FORCE_RADIANS
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
// STL Includes
#include <map>
#include <string>

namespace SAGE
{
	class Effect
	{
		public:
			Effect();
			~Effect();

			enum ShaderType
			{
				Vertex = GL_VERTEX_SHADER,
				Fragment = GL_FRAGMENT_SHADER,
				Geometry = GL_GEOMETRY_SHADER
			};

			enum BasicType
			{
				PositionColor,
				PositionColorTexture,
			};

			bool Create(BasicType pBasicType);

			bool Initialize();
			bool Finalize();

			bool Attach(const std::string& pSource, ShaderType pType);
			bool AttachFromFile(const std::string& pFilename, ShaderType pType);
			bool Link();
			void Use();
			void PrintUniforms();

			GLint GetUniform(const std::string& pName);

			void SetProjection(const glm::mat4& pMatrix);
			void SetModelView(const glm::mat4& pMatrix);
			void SetUniform(const std::string& pName, int pValue);
			void SetUniform(const std::string& pName, float pValue);

		private:
			static const std::string PositionColorVertexSource;
			static const std::string PositionColorFragmentSource;
			static const std::string PositionColorTextureVertexSource;
			static const std::string PositionColorTextureFragmentSource;

			GLuint mProgram;
			GLint mProjectionMatrixLocation;
			GLint mModelViewMatrixLocation;
			std::map<std::string, GLint> mUniforms;
	};
}

#endif
