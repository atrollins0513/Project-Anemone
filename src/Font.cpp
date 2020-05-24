#include "..\Anemone\Font.h"

namespace Anemone
{
	namespace Font
	{

		// Font Loader

		FontLoader::FontLoader()
		{
			font_file = "";
		}

		FontLoader::FontLoader(std::string texture_file, std::string bmFontFile)
		{
			Load(texture_file, bmFontFile);
		}

		void FontLoader::Load(std::string texture_file, std::string bmFontFile)
		{
			font_file = bmFontFile;
			texture = rm::texture(texture_file);

			std::ifstream font_file(bmFontFile);

			if (font_file.is_open())
			{
				std::string line;
				while (std::getline(font_file, line))
				{
					if (line.substr(0, 8) == "char id=")
					{
						FontCharInfo info;
						auto strings = explode(line, ' ');
						for (auto s : strings)
						{
							if (s.find("=") != std::string::npos)
							{
								auto values = explode(s, '=');
								if (values.size() == 2)
								{
									if (values[0] == "id")
									{
										info.id = std::stoi(values[1]);
									}
									else if (values[0] == "x")
									{
										info.x = std::stoi(values[1]);
									}
									else if (values[0] == "y")
									{
										info.y = std::stoi(values[1]);
									}
									else if (values[0] == "width")
									{
										info.width = std::stoi(values[1]);
									}
									else if (values[0] == "height")
									{
										info.height = std::stoi(values[1]);
									}
									else if (values[0] == "xoffset")
									{
										info.xoffset = std::stoi(values[1]);
									}
									else if (values[0] == "yoffset")
									{
										info.yoffset = std::stoi(values[1]);
									}
									else if (values[0] == "xadvance")
									{
										info.xadvance = std::stoi(values[1]);
									}
								}
							}
						}

						info.u = info.x / texture->width();
						info.v = info.y / texture->height();
						info.u_width = info.width / texture->width();
						info.v_height = info.height / texture->height();

						character_info[info.id] = info;
					}
				}

				font_file.close();
			}
			else
			{
				Anemone::Error::Log("FontLoader", "Failed to load font file");
			}
		}

		const FontCharInfo& FontLoader::getCharacter(unsigned int index)
		{
			return character_info[index];
		}

		std::vector<std::string> FontLoader::explode(std::string const & s, char delim)
		{
			std::vector<std::string> result;
			std::istringstream iss(s);

			for (std::string token; std::getline(iss, token, delim); )
			{
				result.push_back(std::move(token));
			}

			return result;
		}

		// Font Manager

		void FontManager::init()
		{
			vao.init();
			vbo[0].init(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
			vbo[0].setData(0, nullptr);
			vao.bindAttribute(0, vbo[0], GL_FLOAT, 3, 20, 0);
			vao.bindAttribute(1, vbo[0], GL_FLOAT, 2, 20, 12);
			vbo[1].init(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
			vbo[1].setData(0, nullptr);
			vao.bindAttribute(2, vbo[1], GL_FLOAT, 3, 12, 0);
			vbo[2].init(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
			vbo[2].setData(0, nullptr);
			vao.setIndexBuffer(vbo[2]);

			Anemone::ShaderBuilder vs(330);
			vs.AddAttribute(0, "vec3", "pos");
			vs.AddAttribute(1, "vec2", "tex");
			vs.AddAttribute(2, "vec3", "color");
			vs.AddUniform("mat4", "proj");
			vs.AddUniform("mat4", "view");
			vs.AddOutput("vec3", "fragColor", 2);
			vs.AddOutput("vec2", "fragTexCoord", 1);
			vs.AddLine("gl_Position = proj * view * vec4(pos, 1.0);");

			Anemone::ShaderBuilder fs(330);
			fs.AddUniform("sampler2D", "texture_id");
			fs.AddInput("vec3", "fragColor");
			fs.AddInput("vec2", "fragTexCoord");
			fs.AddOutput("vec4", "color");
			fs.AddVariable(true, "float", "width", "0.49");
			fs.AddVariable(true, "float", "edge", "0.23");
			fs.AddLine("float distance = 1.0 - texture(texture_id, fragTexCoord).a; float alpha = 1.0 - smoothstep(width, width+edge, distance); color = vec4(fragColor, alpha);");

			shader.LoadFromShaderBuilder(vs, fs);
		}

		void FontManager::update()
		{
			std::vector<FontVertex> vertices;
			std::vector<Anemone::vec3> color;
			std::vector<unsigned int> indices;
			unsigned int index_offset = 0;
			index_count = 0;

			for (auto t : texts)
			{
				if (t->display)
				{
					Anemone::vec3 start_position = t->position;
					Anemone::vec3 position = t->position;
					unsigned int xadvance = 0;
					for (auto s : t->text)
					{
						auto info = loader.getCharacter(s);
						if (info.id == 10)
						{
							position.y -= 87 * t->fontSize;
							position.x = start_position.x;
						}
						info.add(position, t->fontSize, vertices, indices, index_offset);
						position.x += (info.id == 10 ? 0 : info.xadvance * t->fontSize);

						color.push_back(t->color);
						color.push_back(t->color);
						color.push_back(t->color);
						color.push_back(t->color);
					}
				}
			}

			index_count = indices.size();

			vao.bind();
			vbo[0].setData(vertices.size() * sizeof(FontVertex), &vertices[0]);
			vbo[1].setData(color.size() * sizeof(Anemone::vec3), &color[0]);
			vbo[2].setData(indices.size() * sizeof(unsigned int), &indices[0]);
		}

		void FontManager::render()
		{
			glDisable(GL_DEPTH_TEST);

			shader.bind();

			loader.getTexture()->bind();

			vao.bind();

			glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);

			vao.unbind();

			loader.getTexture()->unbind();

			shader.unbind();

			glEnable(GL_DEPTH_TEST);
		}

		void FontManager::loadFont(std::string texture_file, std::string bm_font_file)
		{
			loader.Load(texture_file, bm_font_file);
		}

		void FontManager::addText(std::shared_ptr<Text> text)
		{
			texts.push_back(text);
			update();
		}

		void FontManager::removeText(std::shared_ptr<Text> text)
		{
			texts.erase(std::remove(std::begin(texts), std::end(texts), text), std::end(texts));
			update();
		}
	};
};