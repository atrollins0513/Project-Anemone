#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <unordered_map>

#include "ResourceManager.h"
#include "Error.h"
#include "Math.h"
#include "BufferObject.h"
#include "Shader.h"

namespace Anemone
{
	namespace Font
	{
		struct FontVertex
		{

			ae::vec3 position;

			ae::vec2 tex;

			FontVertex() { }

			FontVertex(ae::vec3 _position, ae::vec2 _tex)
			{
				position = _position;
				tex = _tex;
			}

		};

		struct FontCharInfo
		{

			AE_INT id;

			AE_FLOAT x, y, width, height, xoffset, yoffset, xadvance;

			AE_FLOAT u, v, u_width, v_height;

			void add(ae::vec3 position, AE_FLOAT fontSize, std::vector<FontVertex>& _vertices, std::vector<AE_UINT>& indices, AE_UINT& index_offset)
			{
				AE_FLOAT newWidth = width * fontSize;
				AE_FLOAT newHeight = height * fontSize;
				position += ae::vec3(xoffset * fontSize, 87.0f - (yoffset * fontSize + newHeight), 0.0f);
				_vertices.push_back(FontVertex(ae::vec3(position.x, position.y, position.z), ae::vec2(u, v + v_height)));
				_vertices.push_back(FontVertex(ae::vec3(position.x, position.y + newHeight, position.z), ae::vec2(u, v)));
				_vertices.push_back(FontVertex(ae::vec3(position.x + newWidth, position.y + newHeight, position.z), ae::vec2(u + u_width, v)));
				_vertices.push_back(FontVertex(ae::vec3(position.x + newWidth, position.y, position.z), ae::vec2(u + u_width, v + v_height)));
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

			const FontCharInfo& getCharacter(AE_UINT index);

			const std::string& getFontFileName() { return font_file; }

			const auto getTexture() { return texture; }

		protected:

			std::vector<std::string> explode(std::string const & s, AE_CHAR delim);

		private:

			std::string font_file;

			std::shared_ptr<Anemone::Texture> texture;

			std::map<AE_UINT, FontCharInfo> character_info;

		};

		class Text
		{
		public:

			std::string text;

			AE_FLOAT fontSize, width;

			ae::vec3 position, color;

			AE_INT number_of_lines;

			AE_BOOL display, dynamic;

			Text()
			{
				text = "";
				fontSize = 0;
				display = false;
			}

			Text(std::string _text, ae::vec3 _position, AE_FLOAT _fontSize, ae::vec3 _color, AE_BOOL _display, AE_BOOL _dynamic)
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

			AE_UINT index_count;

			Anemone::Shader shader;

		};
	};
};