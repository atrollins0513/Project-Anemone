#include "ShaderBuilder.h"

namespace Anemone
{
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
};