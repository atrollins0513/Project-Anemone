#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <unordered_map>

#include "BufferObject.h"
#include "ResourceManager.h"
#include "Error.h"
#include "Math.h"
#include "Shader.h"

namespace Anemone
{
	namespace Font
	{
		struct FontVertex
		{

			Anemone::vec3 position;

			Anemone::vec2 tex;

			FontVertex() { }

			FontVertex(Anemone::vec3 _position, Anemone::vec2 _tex)
			{
				position = _position;
				tex = _tex;
			}

		};

		struct FontCharInfo
		{

			int id;

			float x, y, width, height, xoffset, yoffset, xadvance;

			float u, v, u_width, v_height;

			void add(Anemone::vec3 position, float fontSize, std::vector<FontVertex>& _vertices, std::vector<unsigned int>& indices, unsigned int& index_offset)
			{
				float newWidth = width * fontSize;
				float newHeight = height * fontSize;
				position += Anemone::vec3(xoffset * fontSize, 87.0f - (yoffset * fontSize + newHeight), 0.0f);
				_vertices.push_back(FontVertex(Anemone::vec3(position.x, position.y, position.z), Anemone::vec2(u, v + v_height)));
				_vertices.push_back(FontVertex(Anemone::vec3(position.x, position.y + newHeight, position.z), Anemone::vec2(u, v)));
				_vertices.push_back(FontVertex(Anemone::vec3(position.x + newWidth, position.y + newHeight, position.z), Anemone::vec2(u + u_width, v)));
				_vertices.push_back(FontVertex(Anemone::vec3(position.x + newWidth, position.y, position.z), Anemone::vec2(u + u_width, v + v_height)));
				indices.push_back(index_offset + 0);
				indices.push_back(index_offset + 2);
				indices.push_back(index_offset + 1);
				indices.push_back(index_offset + 0);
				indices.push_back(index_offset + 3);
				indices.push_back(index_offset + 2);
				index_offset += 4;
			}

		};

		class FontLoader
		{
		public:

			FontLoader();

			FontLoader(std::string texture_file, std::string bmFontFile);

			void Load(std::string texture_file, std::string bmFontFile);

			const FontCharInfo& getCharacter(unsigned int index);

			const std::string& getFontFileName() { return font_file; }

			const auto getTexture() { return texture; }

		protected:

			std::vector<std::string> explode(std::string const & s, char delim);

		private:

			std::string font_file;

			std::shared_ptr<Anemone::Texture> texture;

			std::map<unsigned int, FontCharInfo> character_info;

		};

		class Text
		{
		public:

			std::string text;

			float fontSize, width;

			Anemone::vec3 position, color;

			int number_of_lines;

			bool display, dynamic;

			Text()
			{
				text = "";
				fontSize = 0;
				display = false;
			}

			Text(std::string _text, Anemone::vec3 _position, float _fontSize, Anemone::vec3 _color, bool _display, bool _dynamic)
			{
				text = _text;
				position = _position;
				fontSize = _fontSize;
				color = _color;
				display = _display;
				dynamic = _dynamic;
			}

			void setText(std::string _text)
			{
				text = _text;
			}

		};

		class FontManager
		{
		public:

			void init();
			
			void update();
			
			void render();
			
			void loadFont(std::string texture_file, std::string bm_font_file);
			
			void addText(std::shared_ptr<Text> text);
			
			void removeText(std::shared_ptr<Text> text);

		private:

			std::vector<std::shared_ptr<Text>> texts;

			FontLoader loader;

			Anemone::VertexArray vao;

			Anemone::VertexBuffer vbo[3];

			unsigned int index_count;

			Anemone::Shader shader;

		};
	};
};