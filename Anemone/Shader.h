#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <Windows.h>
#include <string>
#include <unordered_map>
#include "includes\glew.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include <cassert>
#include <sstream>

#include "Utilities.h"

namespace ae
{
	class ShaderBuilder
	{
	public:

		ShaderBuilder();

		ShaderBuilder(unsigned int _version);

		void SetVersion(unsigned int  _version);

		void AddAttribute(unsigned int location, std::string data_type, std::string name);

		void AddUniform(std::string data_type, std::string name);

		void AddOutput(std::string data_type, std::string name, int linked_to = -1);

		void AddInput(std::string data_type, std::string name);

		void AddLine(std::string line);

		void AddVariable(bool is_const, std::string data_type, std::string name, std::string value = "no value");

		std::string Compile() const;

	private:

		struct ShaderBuilderAttrib
		{
			unsigned int location;
			std::string data_type;
			std::string name;
		};

		struct ShaderBuilderUniform
		{
			std::string data_type;
			std::string name;
		};

		struct ShaderBuilderOutput
		{
			std::string data_type;
			std::string name;
			int linked_to;
		};

		struct ShaderBuilderInput
		{
			std::string data_type;
			std::string name;
		};

		struct ShaderBuilderVariable
		{
			std::string data_type;
			std::string name;
			std::string value;
			bool is_const;
		};

		int version;

		std::vector<ShaderBuilderAttrib> attributes;

		std::vector<ShaderBuilderUniform> uniforms;

		std::vector<ShaderBuilderOutput> outputs;

		std::vector<ShaderBuilderInput> inputs;

		std::vector<ShaderBuilderVariable> variables;

		std::vector<std::string> lines;
	};

	struct UNIFORM_INFO
	{
		int id;
		GLenum type;
	};

	class Shader
	{
	public:
		
		Shader();
		
		Shader(const std::string& vertex, const std::string& fragment, bool loadFromFile);

		Shader(const ShaderBuilder& vs, const ShaderBuilder& fs);

		void loadFromFile(const std::string& vertex, const std::string& fragment);

		void loadFromMemory(const std::string& vertex, const std::string& fragment);

		void loadFromShaderBuilder(const ShaderBuilder& vs, const ShaderBuilder& fs);

		unsigned int id() const { return shader_id; }

		void bind();

		void unbind();

		int getUniformLocation(char* name);

		int getAttribLocation(char* name);

		~Shader();

		// uniform set functions
		void setUniform1f(const std::string& name, float value);
		void setUniform1d(const std::string& name, double value);
		void setUniform1i(const std::string& name, int value);
		void setUniform1ui(const std::string& name, unsigned int value);
		void setUniform2f(const std::string& name, float v0, float v1);
		void setUniform2d(const std::string& name, double v0, double v1);
		void setUniform2i(const std::string& name, int v0, int v1);
		void setUniform2ui(const std::string& name, unsigned int v0, unsigned int v1);
		void setUniform3f(const std::string& name, float v0, float v1, float v2);
		void setUniform3d(const std::string& name, double v0, double v1, double v2);
		void setUniform3i(const std::string& name, int v0, int v1, int v2);
		void setUniform3ui(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2);
		void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void setUniform4d(const std::string& name, double v0, double v1, double v2, double v3);
		void setUniform4i(const std::string& name, int v0, int v1, int v2, int v3);
		void setUniform4ui(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);
		void setUniformMatrix3fv(const std::string& name, int count, bool transpose, const float* value);
		void setUniformMatrix4fv(const std::string& name, int count, bool transpose, const float* value);

	protected:

		void CreateShader(const std::string& vertexData, const std::string& fragmentData);

		bool ValidateShader(char* name, unsigned int shader_id);

		bool ValidateProgram(unsigned int program_id);

		void LoadUniforms();

	private:

		unsigned int shader_id;

		unsigned int vertex_id;

		unsigned int fragment_id;

		std::unordered_map<std::string, UNIFORM_INFO> uniforms;

	};
};