#pragma once

#include "Error.h"
#include "Base.h"
#include "Math.h"
#include "utilities/Animation.h"
#include "BufferObject.h"
#include "Shader.h"
#include "Utilities.h"

namespace ae
{
	struct Particle
	{
		vec2 pos;
		vec2 vel;
		vec2 accel;
		vec2 tex;
		vec3 color;
		float angle		{ 0.0f };
		float speed		{ 0.0f };
		float life		{ 0.0f };
		float max_life	{ 0.0f };
		bool rotate		{ false };
		float size		{ 0.0f };
		float scale		{ 0.0f };
		Animation ani;

		virtual bool update(float s, float c, double dt) { return true; }
	};

	class ParticleSystem;

	class Emitter
	{
	public:

		virtual void emit(ae::ParticleSystem* system) = 0;

		// Getters and Setters
		void setEmitRate(double _emit_rate) { emit_rate = _emit_rate; }
		ae::vec2& getPos() { return pos; }
		void pause() { disabled = true; }
		void unpause() { disabled = false; }
		const bool isPaused() const { return disabled; }
		const double getClock() const { return clock; }
		void resetClock() { clock = 0.0; }

		friend class ParticleSystem;

	protected:

		ae::vec2 pos;

		bool update(double dt);

	private:

		double timer		{ 0.0 };
		double emit_rate	{ 0.0 };
		double clock		{ 0.0 };
		bool disabled		{ false };

	};

	class ParticleSystem : public Base
	{
	public:

		struct ParticleVertex
		{
			ae::vec2 pos;
			ae::vec2 tex;
			ae::vec3 color;

			ParticleVertex() = default;

			ParticleVertex(const ae::vec2& _pos, const ae::vec2& _tex, const ae::vec3& _color)
			{
				set(_pos, _tex, _color);
			}

			void set(const ae::vec2& _pos, const ae::vec2& _tex, const ae::vec3& _color)
			{
				pos = _pos;
				tex = _tex;
				color = _color;
			}
		};

		const float offsets[4][2] = {
			{-0.5f, -0.5f},
			{-0.5f, 0.5f},
			{0.5f, 0.5f},
			{0.5f, -0.5f},
		};

		const float tex_offsets[4][2] = {
			{0.0f, 0.0f},
			{0.0f, 1.0f},
			{1.0f, 1.0f},
			{1.0f, 0.0f},
		};

		ParticleSystem() = default;

		ParticleSystem(unsigned int _max_particles);

		void add(Particle* p);

		void attach(Emitter* emitter);

		void remove(Emitter* emitter);

		void update(double dt);

		void render();

		const unsigned int getParticleCount() const { return (unsigned int)particles.size(); }

		const unsigned int getMaxParticleCount() const { return max_particles; }

		ParticleSystem(const ParticleSystem& other);

		~ParticleSystem();

	protected:

		ParticleVertex* base		{ nullptr };
		ParticleVertex* ptr			{ nullptr };

	private:

		BufferObject buffer;
		VertexBuffer index_buffer;

		unsigned int max_particles	{ 100 };
		unsigned int* indices		{ nullptr };

		std::vector<Particle*> particles;
		std::vector<Particle*> queue;
		std::vector<Emitter*> emitters;

	};

	class ParticleShader : public Shader
	{
	public:
		void load(const ae::mat4& proj, const ae::mat4& view)
		{
			ae::ShaderBuilder vs;
			vs.addAttribute(0, "vec2", "pos");
			vs.addAttribute(1, "vec2", "tex", "_tex");
			vs.addAttribute(2, "vec3", "color", "_color");
			vs.addUniform("mat4", "proj");
			vs.addUniform("mat4", "view");
			vs.addLine("gl_Position = proj * view * vec4(pos, 0.0, 1.0);");

			ae::ShaderBuilder fs;
			fs.addUniform("sampler2D", "texture");
			fs.addUniform("bool", "disableTexture");
			fs.addOutput("vec4", "color");
			fs.addLine("if(disableTexture){ color = vec4(_color, 1.0); } else {");
			fs.addLine("ivec2 texSize = textureSize(texture, 0);");
			fs.addLine("vec4 texel = texture2D(texture, _tex / texSize);");
			fs.addLine("if (texel.a < 0.01) { discard; }");
			fs.addLine("color = texel * vec4(_color, 1.0); }");

			loadFromShaderBuilder(vs, fs);
			bind();
			setUniformMatrix("proj", 1, true, proj);
			setUniformMatrix("view", 1, true, view);
			setUniform("texture", 0);
			setUniform("disableTexture", false);
			unbind();
		}
	};
};