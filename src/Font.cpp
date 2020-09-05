#include "..\Anemone\Font.h"

namespace ae
{

	// Font

	Font::Font(const std::string& _name, const std::string& _font_file, FontTextureID _texture_id) : Font()
	{
		load(_name, _font_file, _texture_id);
	}

	void Font::load(const std::string& _name, const std::string& _font_file, FontTextureID _texture_id)
	{
		name = _name;
		texture_id = _texture_id;

		std::ifstream font_file(_font_file);

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
					info.dim = vec4((float)info.x, (float)info.y, (float)info.width, (float)info.height);
					character_info[info.id] = info;
				}
				else if (line.substr(0, 4) == "info")
				{
					auto strings = explode(line, ' ');
					for (auto s : strings)
					{
						if (s.find("=") != std::string::npos)
						{
							auto values = explode(s, '=');
							if (values.size() == 2)
							{
								if (values[0] == "size")
								{
									size = std::stoi(values[1]);
								}
							}
						}
					}
				}
				else if (line.substr(0, 6) == "common")
				{
					auto strings = explode(line, ' ');
					for (auto s : strings)
					{
						if (s.find("=") != std::string::npos)
						{
							auto values = explode(s, '=');
							if (values.size() == 2)
							{
								if (values[0] == "lineHeight")
								{
									lineHeight = std::stoi(values[1]);
								}
								else if (values[0] == "base")
								{
									base = std::stoi(values[1]);
								}
								else if (values[0] == "scaleW")
								{
									scaleW = std::stoi(values[1]);
								}
								else if (values[0] == "scaleH")
								{
									scaleH = std::stoi(values[1]);
								}
							}
						}
					}
				}
				else if (line.substr(0, 7) == "kerning")
				{
					short first = 0, second = 0, amount = 0;
					auto strings = explode(line, ' ');
					for (auto s : strings)
					{
						if (s.find("=") != std::string::npos)
						{
							auto values = explode(s, '=');
							if (values.size() == 2)
							{
								if (values[0] == "first")
								{
									first = std::stoi(values[1]);
								}
								else if (values[0] == "second")
								{
									second = std::stoi(values[1]);
								}
								else if (values[0] == "amount")
								{
									amount = std::stoi(values[1]);
								}
							}
						}
					}
					character_info[first].kernings[second] = (char)amount;
				}
			}

			font_file.close();
		}
		else
		{
			log("Font", "Failed to load font file.");
		}
	}

	const Font::FontCharInfo& Font::getCharacter(unsigned int index)
	{
		return character_info[index];
	}

	const int Font::getSize() const
	{
		return size;
	}

	const int Font::getLineHeight() const
	{
		return lineHeight;
	}

	const int Font::getBase() const
	{
		return base;
	}

	const int Font::getScaleW() const
	{
		return scaleW;
	}

	const int Font::getScaleH() const
	{
		return scaleH;
	}

	const FontTextureID Font::getTextureID() const
	{
		return texture_id;
	}

	// Text

	void Text::setString(const std::string& _str)
	{
		needs_updating = true;
		str_changed = true;
		old_str_size = (unsigned int)str.size();
		str = _str;
		update();
	}

	const vec2& Text::getPos()
	{
		return pos;
	}

	const vec2 Text::getAdjustedPos()
	{
		return pos - (dim * offset_pos);
	}

	void Text::setColor(const vec4& _color)
	{
		needs_updating = true;
		color = _color;
		update();
	}

	const vec4& Text::getColor()
	{
		return color;
	}

	void Text::setScale(const float _scale)
	{
		needs_updating = true;
		scale = _scale;
		update();
	}

	const float Text::getScale()
	{
		return scale;
	}

	void Text::setVisibility(bool _visible)
	{
		needs_updating = true;
		visible = _visible;
		update();
	}

	const bool Text::isVisible() const
	{
		return visible;
	}

	void Text::setFont(FontRef _font)
	{
		needs_updating = true;
		font = _font;
		update();
	}

	FontRef Text::getFont()
	{
		return font;
	}

	unsigned int Text::getWidth()
	{
		return (unsigned int)dim.x;
	}

	unsigned int Text::getHeight()
	{
		return (unsigned int)dim.y;
	}

	const unsigned long Text::getByteSize() const
	{
		return (unsigned long)(sizeof(Text) + str.length());
	}

	void Text::setOffset(TextOffset _offset)
	{
		offset = _offset;
		switch (offset)
		{
		case TextOffset::top_left: {		offset_pos = vec2(0.0f, 1.0f); break; }
		case TextOffset::middle_left: {		offset_pos = vec2(0.0f, 0.5f); break; }
		case TextOffset::bottom_left: {		offset_pos = 0.0f; break; }
		case TextOffset::center_top: {		offset_pos = vec2(0.5f, 1.0f); break; }
		case TextOffset::center: {			offset_pos = vec2(0.5f, 0.5f); break; }
		case TextOffset::center_bottom: {	offset_pos = vec2(0.5f, 0.0f); break; }
		case TextOffset::top_right: {		offset_pos = vec2(1.0f, 1.0f); break; }
		case TextOffset::middle_right: {	offset_pos = vec2(1.0f, 0.5f); break; }
		case TextOffset::bottom_right: {	offset_pos = vec2(1.0f, 0.0f); break; }
		}
	}

	void Text::update()
	{
		characters.clear();
		dim.x = 0;
		unsigned int newLineWidth = 0;
		unsigned int lineCount = 1;
		int minYOffset = INT_MAX;
		for (auto it = str.begin(); it != str.end(); it++)
		{
			const Font::FontCharInfo& info = font->getCharacter((*it));

			if (info.id == 10)
			{
				if (dim.x > newLineWidth)
				{
					newLineWidth = (unsigned int)dim.x;
				}
				dim.x = 0;
				lineCount++;
			}
			else if (info.id != 32)
			{
				if (info.yoffset < minYOffset)
				{
					minYOffset = info.yoffset;
				}
			}

			int kerning = ((it + 1) != str.end() ? info.kernings[(int)(*(it + 1))] : 0);
			dim.x += (info.id == 10 ? 0 : (info.xadvance + info.xoffset + kerning) * scale);
		}

		dim.y = (font->getBase() - minYOffset) * scale * lineCount;
		dim.x = (newLineWidth > dim.x ? newLineWidth : dim.x);

		vec2 local_pos = pos - (dim * offset_pos);

		local_pos.y += (font->getBase() - minYOffset) * scale * (lineCount - 1.0f);

		for (auto it = str.begin(); it != str.end(); it++)
		{
			const Font::FontCharInfo& info = font->getCharacter((*it));

			if (info.id == '\n')
			{
				local_pos.y -= (font->getBase() - minYOffset) * scale;
				local_pos.x = pos.x - (dim.x * offset_pos.x);
			}

			float y_offset = (font->getBase() * scale) - (info.yoffset * scale) - (info.height * scale);
			characters.push_back(CharVertex(
				info.dim,
				{ local_pos.x + (info.xoffset * scale), local_pos.y + y_offset },
				color,
				scale,
				font->getTextureID()
			));

			int kerning = ((it + 1) != str.end() ? info.kernings[(int)(*(it + 1))] : 0);
			local_pos.x += (info.id == 10 ? 0 : (info.xadvance + info.xoffset + kerning) * scale);
		}
	}

	// TextManager

	void TextManager::init(unsigned int _block_character_limit, unsigned int _character_limit, unsigned int texture_array_size, unsigned int texture_array_depth)
	{
		block_count = 0;
		block_character_limit = _block_character_limit;
		block_capacity = block_character_limit * sizeof(CharVertex);
		character_limit = _character_limit;
		textArray = makeShared<TextureArray>(texture_array_size, texture_array_size, texture_array_depth, 32);
		textArray->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		textArray->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		ShaderBuilder vs(330);
		vs.addAttribute(0, "vec2", "pos");
		vs.addAttribute(1, "vec2", "tex");
		vs.addAttribute(2, "vec4", "iTex");
		vs.addAttribute(3, "vec2", "offset");
		vs.addAttribute(4, "vec4", "color", "_color");
		vs.addAttribute(5, "float", "scale", "_scale");
		vs.addAttribute(6, "float", "layer", "_layer");
		vs.addOutput("vec2", "_tex");
		vs.addUniform("mat4", "proj");
		vs.addLine("_tex = tex.xy * iTex.zw + iTex.xy;");
		vs.addLine("gl_Position = proj * vec4((pos * scale * iTex.zw) + offset, 0.0, 1.0);");

		ShaderBuilder fs(330);
		fs.addUniform("sampler2DArray", "texture_id");
		fs.addUniform("float", "texture_size");
		fs.addUniform("float", "smoothFactor");
		fs.addOutput("vec4", "color");
		fs.addVariable(false, "float", "width", "0.55f");
		fs.addVariable(false, "float", "edge", "0.1f");
		fs.addLine("float s2 = _scale * _scale;");
		fs.addLine("width = -0.3021*s2 + 0.5486*_scale + 0.1537;");
		fs.addLine("edge = 1.0752*s2 - 1.7575*_scale + 0.8132;");
		fs.addLine("float distance = 1.0 - texture(texture_id, vec3(_tex / texture_size, _layer)).a;");
		fs.addLine("float alpha = 1.0 - smoothstep(width, width + edge, distance);");
		fs.addLine("if(alpha < 0.001) { discard; }");
		fs.addLine("color = vec4(_color.rgb, _color.a * alpha);");

		shader = makeShared<Shader>(vs, fs);

		glActiveTexture(GL_TEXTURE0);
		shader->bind();
		shader->setUniformMatrix4fv("proj", 1, GL_TRUE, Ortho(0.0f, 1280.0f, 0.0f, 720.0f, 1.0f, -1.0f).get());
		shader->setUniform("texture_id", 0);
		shader->setUniform("texture_size", 1024.0f);
		shader->unbind();

		float verts[] = {
			0.0f, 0.0f,	0.0f, 1.0f,
			0.0f, 1.0f,	0.0f, 0.0f,
			1.0f, 1.0f,	1.0f, 0.0f,
			1.0f, 0.0f,	1.0f, 1.0f
		};

		unsigned int indices[] = { 0, 2, 1, 0, 3, 2 };

		db = ae::makeShared<DynamicBuffer>();
		db->init();
		db->add(new VertexBuffer({ { 0, 2 }, {1, 2} }, 4 * sizeof(float), 4, verts));
		db->add(new VertexBuffer(sizeof(unsigned int), 6, indices, GL_ELEMENT_ARRAY_BUFFER, GL_UNSIGNED_INT));
		db->add(new VertexBuffer({ {2, 4}, {3, 2}, {4, 4}, {5, 1}, {6,1} }, sizeof(CharVertex), character_limit, nullptr));
		db->setDivisors({ {0,0},{1,0},{2,1},{3,1},{4,1},{5,1},{6,1} });

		base = new CharVertex[character_limit];

	}

	void TextManager::updateAll()
	{
		for (auto text : texts)
		{
			updateTextBuffer(text);
		}

		db->getBuffer(1)->setSubData(0, (unsigned int)(buffer_ptr_back + block_capacity), base);
	}

	void TextManager::updateText(TextRef text)
	{
		if (textExists(text))
		{
			if (text->needs_updating)
			{
				if (text->str_changed)
				{
					unsigned int new_block_count = blockCount((unsigned int)text->str.size());
					unsigned int old_block_count = (unsigned int)getTextBlocks(text).size();

					if (new_block_count > old_block_count)
					{
						createNewBlock(text);
					}
					else if (new_block_count < old_block_count)
					{
						clearBlock(blocks[text].back());
						blocks[text].pop_back();
					}

					//updateTextBuffer(text);
					text->str_changed = false;
				}

				updateTextBuffer(text);
				updateBlocks(text);
				text->needs_updating = false;

			}
		}
	}

	void TextManager::updateText(std::initializer_list<TextRef> text_list)
	{
		for (auto t : text_list)
		{
			updateText(t);
		}
	}

	void TextManager::render()
	{
		shader->bind();
		textArray->bind();
		db->bind();

		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, (GLsizei)(block_count * block_capacity));

		db->unbind();
		textArray->unbind();
		shader->unbind();
	}

	TextRef TextManager::addText(const std::string& str, const vec2& pos, const vec4& color, float scale, bool visible, const std::string& font_name, const TextOffset offset)
	{
		assert(fonts.find(font_name) != fonts.end(), "Failed to find the specificed font, check the spelling possibly.");

		auto newText = makeShared<Text>(str, pos, color, scale, visible, offset, fonts.at(font_name));

		for (unsigned int i = 0; i < blockCount((unsigned int)str.size()); i++)
		{
			createNewBlock(newText);
		}

		texts.push_back(newText);

		return newText;

	}

	void TextManager::removeText(TextRef text)
	{
		if (textExists(text))
		{
			clearTextBlocks(text);
			texts.erase(std::find(texts.begin(), texts.end(), text));
		}
	}

	void TextManager::addFont(const std::string& name, const std::string& font_file, const std::string& font_texture)
	{
		if (fonts.find(name) == fonts.end())
		{
			FontTextureID id = textArray->load(font_texture, false);
			fonts.emplace(name, makeShared<Font>(name, font_file, id));
		}
		else
		{
			log("TextManager", "Failed to load font " + name + ".");
		}
	}

	bool TextManager::textExists(TextRef text)
	{
		return (std::find(texts.begin(), texts.end(), text) != texts.end());
	}

	unsigned int TextManager::stringWidth(const std::string& str, float scale, const std::string& font_name)
	{

		unsigned int width = 0, newlineWidth = 0;

		auto font = fonts.at(font_name);

		for (auto it = str.begin(); it != str.end(); it++)
		{
			const Font::FontCharInfo& info = font->getCharacter((*it));
			if (info.id == 10)
			{
				if (width > newlineWidth)
				{
					newlineWidth = width;
				}
				width = 0;
			}
			int kerning = ((it + 1) != str.end() ? info.kernings[(int)(*(it + 1))] : 0);
			width += (unsigned int)(info.id == 10 ? 0 : (info.xadvance + info.xoffset + kerning) * scale);
		}

		return (newlineWidth > width ? newlineWidth : width);

	}

	unsigned int TextManager::stringHeight(const std::string& str, float scale, const std::string& font_name)
	{

		unsigned int lineCount = 1;

		int minYOffset = INT_MAX;

		for (auto it = str.begin(); it != str.end(); it++)
		{
			const Font::FontCharInfo& info = fonts.at(font_name)->getCharacter((*it));

			if (info.id == 10)
			{
				lineCount++;
			}
			else if (info.id != 32)
			{
				if (info.yoffset < minYOffset)
				{
					minYOffset = info.yoffset;
				}
			}
		}

		return (unsigned int)((fonts.at(font_name)->getBase() - minYOffset) * scale * lineCount);

	}

	void TextManager::setTextProjection(mat4& _proj)
	{
		shader->bind();
		shader->setUniformMatrix4fv("proj", 1, GL_TRUE, _proj);
		shader->unbind();
	}

	const std::vector<TextManager::MemoryBlock>& TextManager::getTextBlocks(TextRef text)
	{
		return blocks[text];
	}

	void TextManager::updateBlocks(const std::vector<TextManager::MemoryBlock>& blocks)
	{
		for (auto b : blocks)
		{
			db->getBuffer(1)->setSubData((unsigned int)b.start, (unsigned int)block_capacity, (base + (b.start / sizeof(CharVertex))));
		}
	}

	void TextManager::updateBlocks(TextRef text)
	{
		for (auto b : blocks[text])
		{
			db->getBuffer(1)->setSubData((unsigned int)b.start, (unsigned int)block_capacity, (base + (b.start / sizeof(CharVertex))));
		}
	}

	void TextManager::createNewBlock(TextRef text)
	{
		TextManager::MemoryBlock b;

		if (block_pool.size() > 0)
		{
			b = block_pool.front();
			block_pool.pop_front();
		}
		else
		{
			b.start = buffer_ptr_back;
			buffer_ptr_back += block_capacity;
		}

		block_count++;
		blocks[text].push_back(b);
	}

	void TextManager::clearBlock(const TextManager::MemoryBlock& b)
	{
		BufferPtr loc = b.start / sizeof(CharVertex);
		for (BufferPtr i = loc; i < block_character_limit + loc; i++)
		{
			(base + i)->zero();
		}
		db->getBuffer(1)->setSubData((unsigned int)b.start, (unsigned int)block_capacity, base + loc);
		block_pool.push_back(b);
		block_count--;
	}

	void TextManager::clearTextBlocks(TextRef text)
	{
		for (auto b : blocks[text])
		{
			clearBlock(b);
		}
	}

	void TextManager::updateTextBuffer(TextRef text)
	{
		auto& textBlocks = getTextBlocks(text);
		unsigned int block_character_offset = 0;
		for (auto& b : textBlocks)
		{
			BufferPtr loc = b.start / sizeof(CharVertex);
			for (BufferPtr i = loc; i < loc + block_character_limit; i++)
			{
				if (block_character_offset + (i - loc) >= text->characters.size() || !text->visible)
				{
					(base + i)->zero();
				}
				else
				{
					(base + i)->set(text->characters[block_character_offset + (i - loc)]);
				}
			}
			block_character_offset += block_character_limit;
		}
	}

	const unsigned int TextManager::blockCount(unsigned int str_size) const
	{
		return (unsigned int)std::ceil((float)str_size / (float)block_character_limit);
	}

	TextManager::~TextManager()
	{
		delete[] base;
	}

};