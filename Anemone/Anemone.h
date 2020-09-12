#pragma once

#if defined(_WIN32) && defined(AE_INCLUDE_LIBRARIES)
	#if defined(_M_IX86) || defined(__i386__)
			#pragma comment(lib, "Anemone/lib/x86/OpenGL32.lib")
			#pragma comment(lib, "Anemone/lib/x86/glew32s.lib")
			#pragma comment(lib, "Anemone/lib/x86/glfw3.lib")
			#pragma comment(lib, "Anemone/lib/x86/Project Anemone.lib")
	#elif defined(_M_X64) || defined(__x86_64__)
			#pragma comment(lib, "Anemone/lib/x64/OpenGL32.lib")
			#pragma comment(lib, "Anemone/lib/x64/glew32s.lib")
			#pragma comment(lib, "Anemone/lib/x64/glfw3.lib")
			#pragma comment(lib, "Anemone/lib/x64/Project Anemone.lib")
	#endif
#endif

/* Includes */

#include "Base.h"
#include "BufferObject.h"
#include "Font.h"
#include "Math.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "State.h"
#include "Texture.h"
#include "Utilities.h"
#include "Renderer.h"
#include "Window.h"
#include "Manager.h"
#include "Camera.h"
#include "Particle.h"

/* Smart Pointer References */
namespace ae
{
	using BufferHandleRef	= sptr<BufferHandle>;
	using ShaderRef			= sptr<Shader>;
	using TextureRef		= sptr<Texture>;
	using TextureArrayRef	= sptr<TextureArray>;
	using WindowRef			= sptr<Window>;
};
