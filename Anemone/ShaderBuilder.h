#pragma once

#include "Anemone.h"

#include <string>
#include <vector>
#include <sstream>
#include <assert.h>

namespace Anemone
{
	namespace
	{
		struct ShaderBuilderAttrib
		{
			AE_UINT location;
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
			AE_INT linked_to;
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
	};

	class ShaderBuilder
	{
	public:

		ShaderBuilder();

		ShaderBuilder(AE_UINT _version);

		void SetVersion(AE_UINT  _version);

		void AddAttribute(AE_UINT location, std::string data_type, std::string name);

		void AddUniform(std::string data_type, std::string name);

		void AddOutput(std::string data_type, std::string name, AE_INT linked_to = -1);

		void AddInput(std::string data_type, std::string name);

		void AddFunction(std::string _func);

		void AddVariable(bool is_const, std::string data_type, std::string name, std::string value = "no value");

		std::string Compile() const;

	protected:
	private:

		int version;

		std::vector<ShaderBuilderAttrib> attributes;

		std::vector<ShaderBuilderUniform> uniforms;

		std::vector<ShaderBuilderOutput> outputs;

		std::vector<ShaderBuilderInput> inputs;

		std::vector<ShaderBuilderVariable> variables;

		std::string func;

	};
};