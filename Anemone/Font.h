#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include "Error.h"
#include "Base.h"
#include "Utilities.h"
#include "BufferObject.h"
#include "Shader.h"
#include "Texture.h"

namespace ae
{
	// Font

	using FontTextureID = unsigned int;

	class Font
	{
	public:

		struct FontCharInfo
		{
			int id				{ 0 };
			int x				{ 0 };
			int y				{ 0 };
			int width			{ 0 };
			int height			{ 0 };
			int xoffset			{ 0 };
			int yoffset			{ 0 };
			int xadvance		{ 0 };
			char kernings[128]	{ 0 };
			vec4 dim			{ 0.0f };
		};

		Font() = default;

		Font(const std::string& _name, const std::string& _font_file, FontTextureID _texture_id);

		void load(const std::string& _name, const std::string& _font_file, FontTextureID _texture_id);

		const FontCharInfo& getCharacter(unsigned int index);

		const int getSize() const;

		const int getLineHeight() const;

		const int getBase() const;

		const int getScaleW() const;

		const int getScaleH() const;

		const FontTextureID getTextureID() const;

	private:

		int size					{ 0 };
		int lineHeight				{ 0 };
		int base					{ 0 };
		int scaleW					{ 0 };
		int scaleH					{ 0 };
		FontTextureID texture_id	{ 0 };
		std::string name			{ "" };
		FontCharInfo character_info[256];

	};

	using FontRef = sptr<Font>;

	// Text

	struct CharVertex
	{
		vec4 tex;
		vec2 pos;
		vec4 color;
		float scale					{ 0.0f };
		unsigned int texture_layer	{ 0 };

		CharVertex() = default;

		CharVertex(vec4 _tex, vec2 _pos, vec4 _color, float _scale, unsigned int _texture_layer)
		{
			set(_tex, _pos, _color, _scale, _texture_layer);
		}

		void set(vec4 _tex, vec2 _pos, vec4 _color, float _scale, unsigned int _texture_layer)
		{
			tex = _tex;
			pos = _pos;
			color = _color;
			scale = _scale;
			texture_layer = _texture_layer;
		}

		void set(const CharVertex& p2)
		{
			tex = p2.tex;
			pos = p2.pos;
			color = p2.color;
			scale = p2.scale;
			texture_layer = p2.texture_layer;
		}

		void zero()
		{
			tex = 0.0f;
			pos = 0.0f;
			color = 0.0f;
			scale = 0.0f;
			texture_layer = 0;
		}

		CharVertex(const CharVertex& p2)
		{
			set(p2);
		}
	};

	enum class TextOffset
	{
		top_left = 0,
		middle_left,
		bottom_left,
		center_top,
		center,
		center_bottom,
		top_right,
		middle_right,
		bottom_right
	};

	class Text
	{
	public:

		Text() = default;
		
		Text(const std::string& _str, const vec2& _pos, const vec4& _color, float _scale, bool _visible, TextOffset _offset, FontRef _font) :
			str(_str), pos(_pos), color(_color), scale(_scale), visible(_visible), font(_font)
		{
			needs_updating = true;
			str_changed = true;
			old_str_size = 0;
			setOffset(_offset);
			update();
		}

		void setString(const std::string& _str);

		const vec2& getPos();

		const vec2 getAdjustedPos();

		void setColor(const vec4& _color);

		const vec4& getColor();

		void setScale(const float _scale);

		const float getScale();

		void setVisibility(bool _visible);

		const bool isVisible() const;

		void setFont(FontRef _font);

		FontRef getFont();

		unsigned int getWidth();

		unsigned int getHeight();

		const unsigned long getByteSize() const;

		void setOffset(TextOffset _offset);

		void update();

		friend class TextManager;

	private:

		std::string str				{ "" };
		sptr<Font> font				{ nullptr };
		TextOffset offset			{ TextOffset::center };
		bool visible				{ false };
		bool needs_updating			{ true };
		bool str_changed			{ true };
		float scale					{ 1.0f };
		unsigned int old_str_size	{ 0 };
		vec2 dim;
		vec2 pos;
		vec2 offset_pos;
		vec4 color;
		std::vector<CharVertex> characters;

	};

	using TextRef = sptr<Text>;

	// TextManager

	class TextManager : public Base
	{
	public:

		TextManager() = default;

		TextManager(unsigned int _block_character_limit, unsigned int _character_limit, unsigned int texture_array_size = 1024, unsigned int texture_array_depth = 16);

		//void init(unsigned int _block_character_limit = 4, unsigned int _character_limit = 100000, unsigned int texture_array_size = 1024, unsigned int texture_array_depth = 16);

		void updateAll();

		void updateText(TextRef text);

		void updateText(std::initializer_list<TextRef> text_list);

		void render();

		TextRef addText(const std::string& _str, const vec2& _pos, const vec4& _color, float _scale, bool _visible, const std::string& font_name, const TextOffset offset = TextOffset::center);

		void removeText(TextRef text);

		void addFont(const std::string& name, const std::string& font_file, const std::string& font_texture);

		bool textExists(TextRef text);

		unsigned int stringWidth(const std::string& str, float scale, const std::string& font_name);

		unsigned int stringHeight(const std::string& str, float scale, const std::string& font_name);

		void setTextProjection(mat4& _proj);

		sptr<Shader> getShader()
		{
			return shader;
		}

		~TextManager();

	private:

		using BufferPtr = unsigned long long;
		struct MemoryBlock
		{
			BufferPtr start	{ 0 };
		};

		const std::vector<MemoryBlock>& getTextBlocks(TextRef text);

		void updateBlocks(const std::vector<MemoryBlock>& blocks);

		void updateBlocks(TextRef text);

		void createNewBlock(TextRef text);

		void clearBlock(const MemoryBlock& b);

		void clearTextBlocks(TextRef text);

		void updateTextBuffer(TextRef text);

		const unsigned int blockCount(unsigned int str_size) const;

		CharVertex* base					{ nullptr };
		sptr<Shader> shader					{ nullptr };
		sptr<TextureArray> textArray		{ nullptr };
		sptr<DynamicBuffer> db				{ nullptr };
		BufferPtr buffer_ptr_back			{ 0 };
		BufferPtr block_capacity			{ 0 };
		unsigned int block_count			{ 0 };
		unsigned int character_limit		{ 0 };
		unsigned int block_character_limit	{ 0 };
		std::vector<TextRef> texts;
		std::unordered_map<std::string, FontRef> fonts;
		std::unordered_map<TextRef, std::vector<MemoryBlock>> blocks;
		std::list<MemoryBlock> block_pool;

	};

};