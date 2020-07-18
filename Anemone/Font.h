#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <unordered_map>

#include "BufferObject.h"
#include "ResourceManager.h"
#include "Math.h"
#include "Shader.h"
#include "Utilities.h"
#include "Texture.h"

namespace ae
{
	namespace Font
	{
		struct FontVertex
		{

			vec3 position;

			vec2 tex;

			FontVertex() { }

			FontVertex(vec3 _position, vec2 _tex)
			{
				position = _position;
				tex = _tex;
			}

		};

		struct FontCharInfo
		{

			int id, x, y, width, height, xoffset, yoffset, xadvance;

			float u, v, u_width, v_height;

			void add(vec3 position, float fontSize, std::vector<FontVertex>& _vertices, std::vector<unsigned int>& indices, unsigned int& index_offset)
			{
				float newWidth = width * fontSize;
				float newHeight = height * fontSize;
				position += vec3(xoffset * fontSize, 87.0f - (yoffset * fontSize + newHeight), 0.0f);
				_vertices.push_back(FontVertex(vec3(position.x, position.y, position.z), vec2(u, v + v_height)));
				_vertices.push_back(FontVertex(vec3(position.x, position.y + newHeight, position.z), vec2(u, v)));
				_vertices.push_back(FontVertex(vec3(position.x + newWidth, position.y + newHeight, position.z), vec2(u + u_width, v)));
				_vertices.push_back(FontVertex(vec3(position.x + newWidth, position.y, position.z), vec2(u + u_width, v + v_height)));
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

			FontLoader(sptr<Texture> _texture, std::string bmFontFile);

			void Load(sptr<Texture> _texture, std::string bmFontFile);

			const FontCharInfo& getCharacter(unsigned int index);

			const std::string& getFontFileName() { return font_file; }

			const auto getTexture() { return texture; }

		protected:

			std::vector<std::string> explode(std::string const & s, char delim);

		private:

			std::string font_file;

			sptr<Texture> texture;

			std::map<unsigned int, FontCharInfo> character_info;

		};

		class Text
		{
		public:

			std::string text;

			float fontSize, width;

			vec3 position, color;

			int number_of_lines;

			bool display, dynamic;

			Text()
			{
				text = "";
				fontSize = 0;
				display = false;
			}

			Text(std::string _text, vec3 _position, float _fontSize, vec3 _color, bool _display, bool _dynamic)
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
			
			void loadFont(sptr<Texture> _texture, std::string bm_font_file);
			
			void addText(std::shared_ptr<Text> text);
			
			void removeText(std::shared_ptr<Text> text);

		private:

			std::vector<std::shared_ptr<Text>> texts;

			FontLoader loader;

			VertexArray vao;

			VertexBuffer vbo[3];

			unsigned int index_count;

			Shader shader;

		};
	};
};