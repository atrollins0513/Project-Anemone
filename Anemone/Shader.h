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
			std::string qualifier;
			std::string data_type;
			std::string name;
			int linked_to;
		};

		struct ShaderBuilderInput
		{
			std::string qualifier;
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

	public:

		ShaderBuilder();

		ShaderBuilder(unsigned int _version);

		void setVersion(unsigned int  _version);

		void addAttribute(unsigned int location, const std::string& data_type, const std::string& name);

		void addAttribute(unsigned int location, const std::string& data_type, const std::string& name, const std::string& output_name);

		void addUniform(const std::string& data_type, const std::string& name);

		/*
		template<typename... Targs>
		void addUniform(const std::string& data_type, const std::string& name, const Targs&... targs)
		{
			ShaderBuilderUniform uniform;
			uniform.data_type = data_type;
			uniform.name = name;
			uniforms.push_back(uniform);
			addUniform(data_type, targs...);
		}
		*/
		
		void addOutput(const std::string& data_type, const std::string& name, int linked_to = -1);

		void addOutput(const std::string& qualifier, const std::string& data_type, const std::string& name, int linked_to = -1);

		void addInput(const std::string& data_type, const std::string& name, const std::string& qualifier = "");

		/*
		template<typename... Targs>
		void addInput(const std::string& data_type, const std::string& name, const Targs&... targs)
		{
			ShaderBuilderInput input;
			input.data_type = data_type;
			input.name = name;
			inputs.push_back(input);
			addInput(data_type, targs...);
		}
		*/

		void addLine(const std::string& line);

		void addVariable(bool is_const, const std::string& data_type, const std::string& name, const std::string& value = "no value");

		std::string compile() const;

		const std::vector<ShaderBuilderAttrib>& getAttributes() const
		{
			return attributes;
		}

		const std::vector<ShaderBuilderOutput>& getOutputs() const
		{
			return outputs;
		}

		const std::vector<ShaderBuilderInput>& getInputs() const
		{
			return inputs;
		}

	private:

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

	class Shader : public MakeSmartExt<Shader>
	{
	public:
		
		Shader();
		
		Shader(const std::string& vertex, const std::string& fragment, bool loadFromFile);

		Shader(ShaderBuilder& vs, ShaderBuilder& fs, bool autoInput = true);

		void loadFromFile(const std::string& vertex, const std::string& fragment);

		void loadFromMemory(const std::string& vertex, const std::string& fragment);

		void loadFromShaderBuilder(ShaderBuilder& vs, ShaderBuilder& fs, bool autoInput = true);

		unsigned int id() const { return shader_id; }

		void bind();

		void unbind();

		int getUniformLocation(const char* name);

		int getAttribLocation(const char* name);

		~Shader();

		// uniform set functions
		void setUniform(const std::string& name, float value);
		void setUniform(const std::string& name, double value);
		void setUniform(const std::string& name, int value);
		void setUniform(const std::string& name, unsigned int value);
		void setUniform(const std::string& name, float v0, float v1);
		void setUniform(const std::string& name, double v0, double v1);
		void setUniform(const std::string& name, int v0, int v1);
		void setUniform(const std::string& name, unsigned int v0, unsigned int v1);
		void setUniform(const std::string& name, float v0, float v1, float v2);
		void setUniform(const std::string& name, double v0, double v1, double v2);
		void setUniform(const std::string& name, int v0, int v1, int v2);
		void setUniform(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2);
		void setUniform(const std::string& name, float v0, float v1, float v2, float v3);
		void setUniform(const std::string& name, double v0, double v1, double v2, double v3);
		void setUniform(const std::string& name, int v0, int v1, int v2, int v3);
		void setUniform(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);
		void setUniformMatrix3fv(const std::string& name, int count, bool transpose, const float* value);
		void setUniformMatrix3fv(const std::string& name, int count, bool transpose, const mat3& value);
		void setUniformMatrix4fv(const std::string& name, int count, bool transpose, const float* value);
		void setUniformMatrix4fv(const std::string& name, int count, bool transpose, const mat4& value);

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

	using ShaderRef = sptr<Shader>;

};