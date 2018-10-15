#include "Shader.h"

namespace Anemone
{
	/* Shader Builder */

	ShaderBuilder::ShaderBuilder()
	{
		SetVersion(330);
	}

	ShaderBuilder::ShaderBuilder(AE_UINT _version)
	{
		SetVersion(_version);
	}

	void ShaderBuilder::SetVersion(AE_UINT _version)
	{
		version = _version;
	}

	void ShaderBuilder::AddAttribute(AE_UINT location, std::string data_type, std::string name)
	{
		ShaderBuilderAttrib attrib;
		attrib.location = location;
		attrib.data_type = data_type;
		attrib.name = name;
		attributes.push_back(attrib);
	}

	void ShaderBuilder::AddUniform(std::string data_type, std::string name)
	{
		ShaderBuilderUniform uniform;
		uniform.data_type = data_type;
		uniform.name = name;
		uniforms.push_back(uniform);
	}

	void ShaderBuilder::AddOutput(std::string data_type, std::string name, AE_INT linked_to)
	{
		ShaderBuilderOutput output;
		output.data_type = data_type;
		output.name = name;
		output.linked_to = linked_to;
		outputs.push_back(output);
	}

	void ShaderBuilder::AddInput(std::string data_type, std::string name)
	{
		ShaderBuilderInput input;
		input.data_type = data_type;
		input.name = name;
		inputs.push_back(input);
	}

	void ShaderBuilder::AddFunction(std::string _func)
	{
		func = _func;
	}

	void ShaderBuilder::AddVariable(bool is_const, std::string data_type, std::string name, std::string value)
	{
		ShaderBuilderVariable variable;
		variable.is_const = is_const;
		variable.data_type = data_type;
		variable.name = name;
		variable.value = value;
		variables.push_back(variable);
	}

	std::string ShaderBuilder::Compile() const
	{
		assert(!func.empty());

		std::stringstream ss;
		ss << "#version " << version << "\n";
		for (auto a : attributes)
		{
			ss << "layout(location = " << a.location << ") in " << a.data_type << " " << a.name << ";\n";
		}

		for (auto u : uniforms)
		{
			ss << "uniform " << u.data_type << " " << u.name << ";\n";
		}

		for (auto i : inputs)
		{
			ss << "in " << i.data_type << " " << i.name << ";\n";
		}

		for (auto o : outputs)
		{
			ss << "out " << o.data_type << " " << o.name << ";\n";
		}

		for (auto v : variables)
		{
			if (v.is_const)
			{
				ss << "const ";
			}

			ss << v.data_type << " " << v.name;

			if (v.value != "no value")
			{
				ss << " = " << v.value << ";\n";
			}
			else
			{
				ss << ";\n";
			}
		}

		ss << "void main() {\n";

		for (auto o : outputs)
		{
			if (o.linked_to != -1)
			{
				for (auto a : attributes)
				{
					if (o.linked_to == a.location)
					{
						ss << o.name << " = " << a.name << ";\n";
					}
				}
			}
		}

		ss << func << "\n";
		ss << "}";

		return ss.str().c_str();
	}

	/* Shader */

	Shader::Shader()
	{
		shader_id = 0;
		vertex_id = 0;
		fragment_id = 0;
	}

	Shader::Shader(AE_CHAR* vertex, AE_CHAR* fragment, AE_BOOL loadFromFile)
	{
		if (loadFromFile)
		{
			CreateShader(LoadFile(vertex).c_str(), LoadFile(fragment).c_str());
		}
		else
		{
			CreateShader(vertex, fragment);
		}
	}

	Shader::Shader(const ShaderBuilder& vs, const ShaderBuilder& fs)
	{
		CreateShader(vs.Compile().c_str(), fs.Compile().c_str());
	}

	void Shader::LoadFromFile(AE_CHAR* vertex, AE_CHAR* fragment)
	{
		CreateShader(LoadFile(vertex).c_str(), LoadFile(fragment).c_str());
	}

	void Shader::LoadFromMemory(AE_CHAR* vertex, AE_CHAR* fragment)
	{
		CreateShader(vertex, fragment);
	}

	void Shader::LoadFromShaderBuilder(const ShaderBuilder & vs, const ShaderBuilder & fs)
	{
		CreateShader(vs.Compile().c_str(), fs.Compile().c_str());
	}

	void Shader::bind()
	{
		glUseProgram(shader_id);
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	AE_INT Shader::GetUniformLocation(AE_CHAR* name)
	{
		return glGetUniformLocation(shader_id, name);
	}

	AE_INT Shader::GetAttribLocation(AE_CHAR* name)
	{
		return glGetAttribLocation(shader_id, name);
	}

	Shader::~Shader()
	{
		glDetachShader(shader_id, vertex_id);
		glDetachShader(shader_id, fragment_id);

		glDeleteShader(vertex_id);
		glDeleteShader(fragment_id);
		glDeleteProgram(shader_id);
	}

	void Shader::CreateShader(const AE_CHAR* vertexData, const AE_CHAR* fragmentData)
	{
		vertex_id = glCreateShader(GL_VERTEX_SHADER);
		fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex_id, 1, &vertexData, NULL);
		glShaderSource(fragment_id, 1, &fragmentData, NULL);

		glCompileShader(vertex_id);
		ValidateShader("vertex", vertex_id);
		glCompileShader(fragment_id);
		ValidateShader("fragment", fragment_id);

		shader_id = glCreateProgram();
		glAttachShader(shader_id, vertex_id);
		glAttachShader(shader_id, fragment_id);
		glLinkProgram(shader_id);
		ValidateProgram(shader_id);

		LoadUniforms();
	}

	bool Shader::ValidateShader(AE_CHAR* name, AE_UINT shader_id)
	{
		AE_INT buffer_size = 4096;
		AE_CHAR* buffer = new AE_CHAR[buffer_size];

		GLsizei length = 0;

		glGetShaderInfoLog(shader_id, buffer_size, &length, buffer);
		if (length > 0)
		{
			// Failed to validate shader
			AE_CHAR log_buffer[8192];
			sprintf(log_buffer, "%s%s%s%s", "Failed to validate the ", name, " shader: ", buffer);
			Error::Log("Shader", log_buffer);

			delete buffer;

			return false;
		}

		delete buffer;

		return true;
	}

	bool Shader::ValidateProgram(AE_UINT program_id)
	{
		AE_INT buffer_size = 4096;
		AE_CHAR* buffer = new AE_CHAR[buffer_size];
		GLsizei length = 0;

		glGetProgramInfoLog(program_id, buffer_size, &length, buffer);
		if (length > 0)
		{
			// Program link error
			AE_CHAR log_buffer[8192];
			sprintf(log_buffer, "%s%s", "Program link error: ", buffer);
			Error::Log("Shader", log_buffer);

			delete buffer;

			return false;
		}

		delete buffer;

		glValidateProgram(program_id);

		GLint status;

		glGetProgramiv(program_id, GL_VALIDATE_STATUS, &status);

		if (status == GL_FALSE)
		{
			// Error validating shader
			Error::Log("Shader", "Error in validating the shader.");
			return false;
		}

		return true;
	}

	void Shader::LoadUniforms()
	{
		GLint i;
		GLint count;

		GLint size; // size of the variable
		GLenum type; // type of the variable (float, vec3 or mat4, etc)

		const GLsizei bufSize = 16; // maximum name length
		GLchar name[bufSize]; // variable name in GLSL
		GLsizei length; // name length

		glGetProgramiv(shader_id, GL_ACTIVE_UNIFORMS, &count);

		for (i = 0; i < count; i++)
		{
			glGetActiveUniform(shader_id, (GLuint)i, bufSize, &length, &size, &type, name);
			UNIFORM_INFO info;
			info.id = i;
			info.type = type;
			uniforms[name] = info;
		}
	}

	// uniform Shader::set functions
	void Shader::setUniform1f(std::string name, AE_FLOAT value)
	{
		glUniform1f(uniforms[name].id, value);
	}

	void Shader::setUniform1d(std::string name, AE_DOUBLE value)
	{
		glUniform1d(uniforms[name].id, value);
	}

	void Shader::setUniform1i(std::string name, AE_INT value)
	{
		glUniform1i(uniforms[name].id, value);
	}

	void Shader::setUniform1ui(std::string name, AE_UINT value)
	{
		glUniform1ui(uniforms[name].id, value);
	}

	void Shader::setUniform2f(std::string name, AE_FLOAT v0, AE_FLOAT v1)
	{
		glUniform2f(uniforms[name].id, v0, v1);
	}

	void Shader::setUniform2d(std::string name, AE_DOUBLE v0, AE_DOUBLE v1)
	{
		glUniform2d(uniforms[name].id, v0, v1);
	}

	void Shader::setUniform2i(std::string name, AE_INT v0, AE_INT v1)
	{
		glUniform2i(uniforms[name].id, v0, v1);
	}

	void Shader::setUniform2ui(std::string name, AE_UINT v0, AE_UINT v1)
	{
		glUniform2ui(uniforms[name].id, v0, v1);
	}

	void Shader::setUniform3f(std::string name, AE_FLOAT v0, AE_FLOAT v1, AE_FLOAT v2)
	{
		glUniform3f(uniforms[name].id, v0, v1, v2);
	}

	void Shader::setUniform3d(std::string name, AE_DOUBLE v0, AE_DOUBLE v1, AE_DOUBLE v2)
	{
		glUniform3d(uniforms[name].id, v0, v1, v2);
	}

	void Shader::setUniform3i(std::string name, AE_INT v0, AE_INT v1, AE_INT v2)
	{
		glUniform3i(uniforms[name].id, v0, v1, v2);
	}

	void Shader::setUniform3ui(std::string name, AE_UINT v0, AE_UINT v1, AE_UINT v2)
	{
		glUniform3ui(uniforms[name].id, v0, v1, v2);
	}

	void Shader::setUniform4f(std::string name, AE_FLOAT v0, AE_FLOAT v1, AE_FLOAT v2, AE_FLOAT v3)
	{
		glUniform4f(uniforms[name].id, v0, v1, v2, v3);
	}

	void Shader::setUniform4d(std::string name, AE_DOUBLE v0, AE_DOUBLE v1, AE_DOUBLE v2, AE_DOUBLE v3)
	{
		glUniform4d(uniforms[name].id, v0, v1, v2, v3);
	}

	void Shader::setUniform4i(std::string name, AE_INT v0, AE_INT v1, AE_INT v2, AE_INT v3)
	{
		glUniform4i(uniforms[name].id, v0, v1, v2, v3);
	}

	void Shader::setUniform4ui(std::string name, AE_UINT v0, AE_UINT v1, AE_UINT v2, AE_UINT v3)
	{
		glUniform4ui(uniforms[name].id, v0, v1, v2, v3);
	}

	void Shader::setUniformMatrix3fv(std::string name, AE_INT count, AE_BOOL transpose, const AE_FLOAT* value)
	{
		glUniformMatrix3fv(uniforms[name].id, count, transpose, value);
	}

	void Shader::setUniformMatrix4fv(std::string name, AE_INT count, AE_BOOL transpose, const AE_FLOAT* value)
	{
		glUniformMatrix4fv(uniforms[name].id, count, transpose, value);
	}

};