#pragma once

#ifdef _WIN32
	#ifdef ANEMONE_INCLUDE_LIBRARIES_X86
		#ifdef ANEMONE_PATH
			#pragma comment(lib, ANEMONE_PATH + "/x86/OpenGL32.lib")
			#pragma comment(lib, ANEMONE_PATH + "/x86/glew32s.lib")
			#pragma comment(lib, ANEMONE_PATH + "/x86/glfw3.lib")
			#pragma comment(lib, ANEMONE_PATH + "/x86/Project Anemone.lib")
		#else
			#pragma comment(lib, "Anemone/lib/x86/OpenGL32.lib")
			#pragma comment(lib, "Anemone/lib/x86/glew32s.lib")
			#pragma comment(lib, "Anemone/lib/x86/glfw3.lib")
			#pragma comment(lib, "Anemone/lib/x86/Project Anemone.lib")
		#endif
	#elif ANEMONE_INCLUDE_LIBRARIES_X64
		#ifdef ANEMONE_PATH
		#pragma comment(lib, ANEMONE_PATH + "/x64/OpenGL32.lib")
		#pragma comment(lib, ANEMONE_PATH + "/x64/glew32s.lib")
		#pragma comment(lib, ANEMONE_PATH + "/x64/glfw3.lib")
		#pragma comment(lib, ANEMONE_PATH + "/x64/Project Anemone.lib")
		#else
		#pragma comment(lib, "Anemone/lib/x64/OpenGL32.lib")
		#pragma comment(lib, "Anemone/lib/x64/glew32s.lib")
		#pragma comment(lib, "Anemone/lib/x64/glfw3.lib")
		#pragma comment(lib, "Anemone/lib/x64/Project Anemone.lib")
		#endif
	#endif

	#ifndef ANEMONE_DISABLE_MAIN_ENTRY_POINT
	#pragma comment(linker, "/ENTRY:mainCRTStartup")
	#endif
#endif

#define ae Anemone
#define Anemone Anemone

#include "Animation.h"
#include "BufferObject.h"
#include "Error.h"
#include "Font.h"
#include "Math.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "State.h"
#include "Texture.h"
#include "Utilities.h"
#include "Window.h"