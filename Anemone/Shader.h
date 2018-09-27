#pragma once

#include "Anemone.h"

#include <Windows.h>
#include <gl\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <string>
#include <unordered_map>

#include "Error.h"
#include "File.h"
#include "ShaderBuilder.h"

namespace Anemone
{
	struct UNIFORM_INFO
	{
		AE_INT id;
		GLenum type;
	};

	class Shader
	{
	public:
		
		Shader();
		
		Shader(AE_CHAR* vertex, AE_CHAR* fragment, AE_BOOL loadFromFile);

		Shader(const ShaderBuilder& vs, const ShaderBuilder& fs);

		void LoadFromFile(AE_CHAR* vertex, AE_CHAR* fragment);

		void LoadFromMemory(AE_CHAR* vertex, AE_CHAR* fragment);

		void LoadFromShaderBuilder(const ShaderBuilder& vs, const ShaderBuilder& fs);

		AE_UINT id() const { return shader_id; }

		void bind();

		void unbind();

		AE_INT GetUniformLocation(AE_CHAR* name);

		AE_INT GetAttribLocation(AE_CHAR* name);

		~Shader();

		// uniform set functions
		void setUniform1f(std::string name, AE_FLOAT value);
		void setUniform1d(std::string name, AE_DOUBLE value);
		void setUniform1i(std::string name, AE_INT value);
		void setUniform1ui(std::string name, AE_UINT value);
		void setUniform2f(std::string name, AE_FLOAT v0, AE_FLOAT v1);
		void setUniform2d(std::string name, AE_DOUBLE v0, AE_DOUBLE v1);
		void setUniform2i(std::string name, AE_INT v0, AE_INT v1);
		void setUniform2ui(std::string name, AE_UINT v0, AE_UINT v1);
		void setUniform3f(std::string name, AE_FLOAT v0, AE_FLOAT v1, AE_FLOAT v2);
		void setUniform3d(std::string name, AE_DOUBLE v0, AE_DOUBLE v1, AE_DOUBLE v2);
		void setUniform3i(std::string name, AE_INT v0, AE_INT v1, AE_INT v2);
		void setUniform3ui(std::string name, AE_UINT v0, AE_UINT v1, AE_UINT v2);
		void setUniform4f(std::string name, AE_FLOAT v0, AE_FLOAT v1, AE_FLOAT v2, AE_FLOAT v3);
		void setUniform4d(std::string name, AE_DOUBLE v0, AE_DOUBLE v1, AE_DOUBLE v2, AE_DOUBLE v3);
		void setUniform4i(std::string name, AE_INT v0, AE_INT v1, AE_INT v2, AE_INT v3);
		void setUniform4ui(std::string name, AE_UINT v0, AE_UINT v1, AE_UINT v2, AE_UINT v3);
		void setUniformMatrix3fv(std::string name, AE_INT count, AE_BOOL transpose, const AE_FLOAT* value);
		void setUniformMatrix4fv(std::string name, AE_INT count, AE_BOOL transpose, const AE_FLOAT* value);

	protected:

		void CreateShader(const AE_CHAR* vertexData, const AE_CHAR* fragmentData);

		bool ValidateShader(AE_CHAR* name, AE_UINT shader_id);

		bool ValidateProgram(AE_UINT program_id);

		void LoadUniforms();

	private:

		AE_UINT shader_id;

		AE_UINT vertex_id;

		AE_UINT fragment_id;

		std::unordered_map<std::string, UNIFORM_INFO> uniforms;

	};
};