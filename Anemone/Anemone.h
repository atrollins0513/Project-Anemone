#pragma once

#ifdef ANEMONE_PATH
#pragma comment(lib, ANEMONE_PATH + "Anemone/lib/OpenGL32.lib")
#pragma comment(lib, ANEMONE_PATH + "Anemone/lib/glew/x86/glew32s.lib")
#pragma comment(lib, ANEMONE_PATH + "Anemone/lib/glfw3.lib")
#pragma comment(lib, ANEMONE_PATH + "Anemone/lib/Project Anemone.lib")
#else
#pragma comment(lib, "Anemone/lib/OpenGL32.lib")
#pragma comment(lib, "Anemone/lib/glew/x86/glew32s.lib")
#pragma comment(lib, "Anemone/lib/glfw3.lib")
#pragma comment(lib, "Anemone/lib/Project Anemone.lib")
#endif

namespace Anemone
{

	typedef bool AE_BOOL;

	typedef char AE_CHAR;

	typedef unsigned char AE_UCHAR;

	typedef wchar_t AE_WCHAR;

	typedef int AE_INT;

	typedef unsigned int AE_UINT;

	typedef short int AE_SHORT;

	typedef float AE_FLOAT;

	typedef long AE_LONG;

	typedef long long AE_2LONG;

	typedef unsigned long AE_ULONG;

	typedef double AE_DOUBLE;

	typedef long double AE_LDOUBLE;

};

#define AE Anemone
#define ae Anemone