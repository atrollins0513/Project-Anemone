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

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "includes\glew.h"
#include "includes\glfw3.h"

/* GLFW Redefinitions */

#define AE_VERSION_MAJOR					GLFW_VERSION_MAJOR
#define AE_VERSION_MINOR					GLFW_VERSION_MINOR
#define AE_VERSION_REVISION 				GLFW_VERSION_REVISION 
#define AE_TRUE 							GLFW_TRUE 
#define AE_FALSE							GLFW_FALSE
#define AE_RELEASE							GLFW_RELEASE
#define AE_PRESS							GLFW_PRESS
#define AE_REPEAT 							GLFW_REPEAT 
#define AE_HAT_CENTERED 					GLFW_HAT_CENTERED 
#define AE_HAT_UP 							GLFW_HAT_UP 
#define AE_HAT_RIGHT						GLFW_HAT_RIGHT
#define AE_HAT_DOWN 						GLFW_HAT_DOWN 
#define AE_HAT_LEFT 						GLFW_HAT_LEFT 
#define AE_HAT_RIGHT_UP 					GLFW_HAT_RIGHT_UP 
#define AE_HAT_RIGHT_DOWN 					GLFW_HAT_RIGHT_DOWN 
#define AE_HAT_LEFT_UP						GLFW_HAT_LEFT_UP
#define AE_HAT_LEFT_DOWN					GLFW_HAT_LEFT_DOWN
#define AE_KEY_UNKNOWN						GLFW_KEY_UNKNOWN
#define AE_KEY_SPACE						GLFW_KEY_SPACE
#define AE_KEY_APOSTROPHE 					GLFW_KEY_APOSTROPHE 
#define AE_KEY_COMMA						GLFW_KEY_COMMA
#define AE_KEY_MINUS						GLFW_KEY_MINUS
#define AE_KEY_PERIOD 						GLFW_KEY_PERIOD 
#define AE_KEY_SLASH						GLFW_KEY_SLASH
#define AE_KEY_0							GLFW_KEY_0
#define AE_KEY_1							GLFW_KEY_1
#define AE_KEY_2							GLFW_KEY_2
#define AE_KEY_3							GLFW_KEY_3
#define AE_KEY_4							GLFW_KEY_4
#define AE_KEY_5							GLFW_KEY_5
#define AE_KEY_6							GLFW_KEY_6
#define AE_KEY_7							GLFW_KEY_7
#define AE_KEY_8							GLFW_KEY_8
#define AE_KEY_9							GLFW_KEY_9
#define AE_KEY_SEMICOLON					GLFW_KEY_SEMICOLON
#define AE_KEY_EQUAL						GLFW_KEY_EQUAL
#define AE_KEY_A							GLFW_KEY_A
#define AE_KEY_B							GLFW_KEY_B
#define AE_KEY_C							GLFW_KEY_C
#define AE_KEY_D							GLFW_KEY_D
#define AE_KEY_E							GLFW_KEY_E
#define AE_KEY_F							GLFW_KEY_F
#define AE_KEY_G							GLFW_KEY_G
#define AE_KEY_H							GLFW_KEY_H
#define AE_KEY_I							GLFW_KEY_I
#define AE_KEY_J							GLFW_KEY_J
#define AE_KEY_K							GLFW_KEY_K
#define AE_KEY_L							GLFW_KEY_L
#define AE_KEY_M							GLFW_KEY_M
#define AE_KEY_N							GLFW_KEY_N
#define AE_KEY_O							GLFW_KEY_O
#define AE_KEY_P							GLFW_KEY_P
#define AE_KEY_Q							GLFW_KEY_Q
#define AE_KEY_R							GLFW_KEY_R
#define AE_KEY_S							GLFW_KEY_S
#define AE_KEY_T							GLFW_KEY_T
#define AE_KEY_U							GLFW_KEY_U
#define AE_KEY_V							GLFW_KEY_V
#define AE_KEY_W							GLFW_KEY_W
#define AE_KEY_X							GLFW_KEY_X
#define AE_KEY_Y							GLFW_KEY_Y
#define AE_KEY_Z							GLFW_KEY_Z
#define AE_KEY_LEFT_BRACKET 				GLFW_KEY_LEFT_BRACKET 
#define AE_KEY_BACKSLASH					GLFW_KEY_BACKSLASH
#define AE_KEY_RIGHT_BRACKET				GLFW_KEY_RIGHT_BRACKET
#define AE_KEY_GRAVE_ACCENT 				GLFW_KEY_GRAVE_ACCENT 
#define AE_KEY_WORLD_1						GLFW_KEY_WORLD_1
#define AE_KEY_WORLD_2						GLFW_KEY_WORLD_2
#define AE_KEY_ESCAPE 						GLFW_KEY_ESCAPE 
#define AE_KEY_ENTER						GLFW_KEY_ENTER
#define AE_KEY_TAB							GLFW_KEY_TAB
#define AE_KEY_BACKSPACE					GLFW_KEY_BACKSPACE
#define AE_KEY_INSERT 						GLFW_KEY_INSERT 
#define AE_KEY_DELETE 						GLFW_KEY_DELETE 
#define AE_KEY_RIGHT						GLFW_KEY_RIGHT
#define AE_KEY_LEFT 						GLFW_KEY_LEFT 
#define AE_KEY_DOWN 						GLFW_KEY_DOWN 
#define AE_KEY_UP 							GLFW_KEY_UP 
#define AE_KEY_PAGE_UP						GLFW_KEY_PAGE_UP
#define AE_KEY_PAGE_DOWN					GLFW_KEY_PAGE_DOWN
#define AE_KEY_HOME 						GLFW_KEY_HOME 
#define AE_KEY_END							GLFW_KEY_END
#define AE_KEY_CAPS_LOCK					GLFW_KEY_CAPS_LOCK
#define AE_KEY_SCROLL_LOCK					GLFW_KEY_SCROLL_LOCK
#define AE_KEY_NUM_LOCK 					GLFW_KEY_NUM_LOCK 
#define AE_KEY_PRINT_SCREEN 				GLFW_KEY_PRINT_SCREEN 
#define AE_KEY_PAUSE						GLFW_KEY_PAUSE
#define AE_KEY_F1 							GLFW_KEY_F1 
#define AE_KEY_F2 							GLFW_KEY_F2 
#define AE_KEY_F3 							GLFW_KEY_F3 
#define AE_KEY_F4 							GLFW_KEY_F4 
#define AE_KEY_F5 							GLFW_KEY_F5 
#define AE_KEY_F6 							GLFW_KEY_F6 
#define AE_KEY_F7 							GLFW_KEY_F7 
#define AE_KEY_F8 							GLFW_KEY_F8 
#define AE_KEY_F9 							GLFW_KEY_F9 
#define AE_KEY_F10							GLFW_KEY_F10
#define AE_KEY_F11							GLFW_KEY_F11
#define AE_KEY_F12							GLFW_KEY_F12
#define AE_KEY_F13							GLFW_KEY_F13
#define AE_KEY_F14							GLFW_KEY_F14
#define AE_KEY_F15							GLFW_KEY_F15
#define AE_KEY_F16							GLFW_KEY_F16
#define AE_KEY_F17							GLFW_KEY_F17
#define AE_KEY_F18							GLFW_KEY_F18
#define AE_KEY_F19							GLFW_KEY_F19
#define AE_KEY_F20							GLFW_KEY_F20
#define AE_KEY_F21							GLFW_KEY_F21
#define AE_KEY_F22							GLFW_KEY_F22
#define AE_KEY_F23							GLFW_KEY_F23
#define AE_KEY_F24							GLFW_KEY_F24
#define AE_KEY_F25							GLFW_KEY_F25
#define AE_KEY_KP_0 						GLFW_KEY_KP_0 
#define AE_KEY_KP_1 						GLFW_KEY_KP_1 
#define AE_KEY_KP_2 						GLFW_KEY_KP_2 
#define AE_KEY_KP_3 						GLFW_KEY_KP_3 
#define AE_KEY_KP_4 						GLFW_KEY_KP_4 
#define AE_KEY_KP_5 						GLFW_KEY_KP_5 
#define AE_KEY_KP_6 						GLFW_KEY_KP_6 
#define AE_KEY_KP_7 						GLFW_KEY_KP_7 
#define AE_KEY_KP_8 						GLFW_KEY_KP_8 
#define AE_KEY_KP_9 						GLFW_KEY_KP_9 
#define AE_KEY_KP_DECIMAL 					GLFW_KEY_KP_DECIMAL 
#define AE_KEY_KP_DIVIDE					GLFW_KEY_KP_DIVIDE
#define AE_KEY_KP_MULTIPLY					GLFW_KEY_KP_MULTIPLY
#define AE_KEY_KP_SUBTRACT					GLFW_KEY_KP_SUBTRACT
#define AE_KEY_KP_ADD 						GLFW_KEY_KP_ADD 
#define AE_KEY_KP_ENTER 					GLFW_KEY_KP_ENTER 
#define AE_KEY_KP_EQUAL 					GLFW_KEY_KP_EQUAL 
#define AE_KEY_LEFT_SHIFT 					GLFW_KEY_LEFT_SHIFT 
#define AE_KEY_LEFT_CONTROL 				GLFW_KEY_LEFT_CONTROL 
#define AE_KEY_LEFT_ALT 					GLFW_KEY_LEFT_ALT 
#define AE_KEY_LEFT_SUPER 					GLFW_KEY_LEFT_SUPER 
#define AE_KEY_RIGHT_SHIFT					GLFW_KEY_RIGHT_SHIFT
#define AE_KEY_RIGHT_CONTROL				GLFW_KEY_RIGHT_CONTROL
#define AE_KEY_RIGHT_ALT					GLFW_KEY_RIGHT_ALT
#define AE_KEY_RIGHT_SUPER					GLFW_KEY_RIGHT_SUPER
#define AE_KEY_MENU 						GLFW_KEY_MENU 
#define AE_KEY_LAST 						GLFW_KEY_LAST 
#define AE_MOD_SHIFT						GLFW_MOD_SHIFT
#define AE_MOD_CONTROL						GLFW_MOD_CONTROL
#define AE_MOD_ALT							GLFW_MOD_ALT
#define AE_MOD_SUPER						GLFW_MOD_SUPER
#define AE_MOD_CAPS_LOCK					GLFW_MOD_CAPS_LOCK
#define AE_MOD_NUM_LOCK 					GLFW_MOD_NUM_LOCK 
#define AE_MOUSE_BUTTON_1 					GLFW_MOUSE_BUTTON_1 
#define AE_MOUSE_BUTTON_2 					GLFW_MOUSE_BUTTON_2 
#define AE_MOUSE_BUTTON_3 					GLFW_MOUSE_BUTTON_3 
#define AE_MOUSE_BUTTON_4 					GLFW_MOUSE_BUTTON_4 
#define AE_MOUSE_BUTTON_5 					GLFW_MOUSE_BUTTON_5 
#define AE_MOUSE_BUTTON_6 					GLFW_MOUSE_BUTTON_6 
#define AE_MOUSE_BUTTON_7 					GLFW_MOUSE_BUTTON_7 
#define AE_MOUSE_BUTTON_8 					GLFW_MOUSE_BUTTON_8 
#define AE_MOUSE_BUTTON_LAST				GLFW_MOUSE_BUTTON_LAST
#define AE_MOUSE_BUTTON_LEFT				GLFW_MOUSE_BUTTON_LEFT
#define AE_MOUSE_BUTTON_RIGHT 				GLFW_MOUSE_BUTTON_RIGHT 
#define AE_MOUSE_BUTTON_MIDDLE				GLFW_MOUSE_BUTTON_MIDDLE
#define AE_JOYSTICK_1 						GLFW_JOYSTICK_1 
#define AE_JOYSTICK_2 						GLFW_JOYSTICK_2 
#define AE_JOYSTICK_3 						GLFW_JOYSTICK_3 
#define AE_JOYSTICK_4 						GLFW_JOYSTICK_4 
#define AE_JOYSTICK_5 						GLFW_JOYSTICK_5 
#define AE_JOYSTICK_6 						GLFW_JOYSTICK_6 
#define AE_JOYSTICK_7 						GLFW_JOYSTICK_7 
#define AE_JOYSTICK_8 						GLFW_JOYSTICK_8 
#define AE_JOYSTICK_9 						GLFW_JOYSTICK_9 
#define AE_JOYSTICK_10						GLFW_JOYSTICK_10
#define AE_JOYSTICK_11						GLFW_JOYSTICK_11
#define AE_JOYSTICK_12						GLFW_JOYSTICK_12
#define AE_JOYSTICK_13						GLFW_JOYSTICK_13
#define AE_JOYSTICK_14						GLFW_JOYSTICK_14
#define AE_JOYSTICK_15						GLFW_JOYSTICK_15
#define AE_JOYSTICK_16						GLFW_JOYSTICK_16
#define AE_JOYSTICK_LAST					GLFW_JOYSTICK_LAST
#define AE_GAMEPAD_BUTTON_A 				GLFW_GAMEPAD_BUTTON_A 
#define AE_GAMEPAD_BUTTON_B 				GLFW_GAMEPAD_BUTTON_B 
#define AE_GAMEPAD_BUTTON_X 				GLFW_GAMEPAD_BUTTON_X 
#define AE_GAMEPAD_BUTTON_Y 				GLFW_GAMEPAD_BUTTON_Y 
#define AE_GAMEPAD_BUTTON_LEFT_BUMPER 		GLFW_GAMEPAD_BUTTON_LEFT_BUMPER 
#define AE_GAMEPAD_BUTTON_RIGHT_BUMPER		GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER
#define AE_GAMEPAD_BUTTON_BACK				GLFW_GAMEPAD_BUTTON_BACK
#define AE_GAMEPAD_BUTTON_START 			GLFW_GAMEPAD_BUTTON_START 
#define AE_GAMEPAD_BUTTON_GUIDE 			GLFW_GAMEPAD_BUTTON_GUIDE 
#define AE_GAMEPAD_BUTTON_LEFT_THUMB		GLFW_GAMEPAD_BUTTON_LEFT_THUMB
#define AE_GAMEPAD_BUTTON_RIGHT_THUMB 		GLFW_GAMEPAD_BUTTON_RIGHT_THUMB 
#define AE_GAMEPAD_BUTTON_DPAD_UP 			GLFW_GAMEPAD_BUTTON_DPAD_UP 
#define AE_GAMEPAD_BUTTON_DPAD_RIGHT		GLFW_GAMEPAD_BUTTON_DPAD_RIGHT
#define AE_GAMEPAD_BUTTON_DPAD_DOWN 		GLFW_GAMEPAD_BUTTON_DPAD_DOWN 
#define AE_GAMEPAD_BUTTON_DPAD_LEFT 		GLFW_GAMEPAD_BUTTON_DPAD_LEFT 
#define AE_GAMEPAD_BUTTON_LAST				GLFW_GAMEPAD_BUTTON_LAST
#define AE_GAMEPAD_BUTTON_CROSS 			GLFW_GAMEPAD_BUTTON_CROSS 
#define AE_GAMEPAD_BUTTON_CIRCLE			GLFW_GAMEPAD_BUTTON_CIRCLE
#define AE_GAMEPAD_BUTTON_SQUARE			GLFW_GAMEPAD_BUTTON_SQUARE
#define AE_GAMEPAD_BUTTON_TRIANGLE			GLFW_GAMEPAD_BUTTON_TRIANGLE
#define AE_GAMEPAD_AXIS_LEFT_X				GLFW_GAMEPAD_AXIS_LEFT_X
#define AE_GAMEPAD_AXIS_LEFT_Y				GLFW_GAMEPAD_AXIS_LEFT_Y
#define AE_GAMEPAD_AXIS_RIGHT_X 			GLFW_GAMEPAD_AXIS_RIGHT_X 
#define AE_GAMEPAD_AXIS_RIGHT_Y 			GLFW_GAMEPAD_AXIS_RIGHT_Y 
#define AE_GAMEPAD_AXIS_LEFT_TRIGGER		GLFW_GAMEPAD_AXIS_LEFT_TRIGGER
#define AE_GAMEPAD_AXIS_RIGHT_TRIGGER 		GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER 
#define AE_GAMEPAD_AXIS_LAST				GLFW_GAMEPAD_AXIS_LAST
#define AE_NO_ERROR 						GLFW_NO_ERROR 
#define AE_NOT_INITIALIZED					GLFW_NOT_INITIALIZED
#define AE_NO_CURRENT_CONTEXT 				GLFW_NO_CURRENT_CONTEXT 
#define AE_INVALID_ENUM 					GLFW_INVALID_ENUM 
#define AE_INVALID_VALUE					GLFW_INVALID_VALUE
#define AE_OUT_OF_MEMORY					GLFW_OUT_OF_MEMORY
#define AE_API_UNAVAILABLE					GLFW_API_UNAVAILABLE
#define AE_VERSION_UNAVAILABLE				GLFW_VERSION_UNAVAILABLE
#define AE_PLATFORM_ERROR 					GLFW_PLATFORM_ERROR 
#define AE_FORMAT_UNAVAILABLE 				GLFW_FORMAT_UNAVAILABLE 
#define AE_NO_WINDOW_CONTEXT				GLFW_NO_WINDOW_CONTEXT
#define AE_FOCUSED							GLFW_FOCUSED
#define AE_ICONIFIED						GLFW_ICONIFIED
#define AE_RESIZABLE						GLFW_RESIZABLE
#define AE_VISIBLE							GLFW_VISIBLE
#define AE_DECORATED						GLFW_DECORATED
#define AE_AUTO_ICONIFY 					GLFW_AUTO_ICONIFY 
#define AE_FLOATING 						GLFW_FLOATING 
#define AE_MAXIMIZED						GLFW_MAXIMIZED
#define AE_CENTER_CURSOR					GLFW_CENTER_CURSOR
#define AE_TRANSPARENT_FRAMEBUFFER			GLFW_TRANSPARENT_FRAMEBUFFER
#define AE_HOVERED							GLFW_HOVERED
#define AE_FOCUS_ON_SHOW					GLFW_FOCUS_ON_SHOW
#define AE_RED_BITS 						GLFW_RED_BITS 
#define AE_GREEN_BITS 						GLFW_GREEN_BITS 
#define AE_BLUE_BITS						GLFW_BLUE_BITS
#define AE_ALPHA_BITS 						GLFW_ALPHA_BITS 
#define AE_DEPTH_BITS 						GLFW_DEPTH_BITS 
#define AE_STENCIL_BITS 					GLFW_STENCIL_BITS 
#define AE_ACCUM_RED_BITS 					GLFW_ACCUM_RED_BITS 
#define AE_ACCUM_GREEN_BITS 				GLFW_ACCUM_GREEN_BITS 
#define AE_ACCUM_BLUE_BITS					GLFW_ACCUM_BLUE_BITS
#define AE_ACCUM_ALPHA_BITS 				GLFW_ACCUM_ALPHA_BITS 
#define AE_AUX_BUFFERS						GLFW_AUX_BUFFERS
#define AE_STEREO 							GLFW_STEREO 
#define AE_SAMPLES							GLFW_SAMPLES
#define AE_SRGB_CAPABLE 					GLFW_SRGB_CAPABLE 
#define AE_REFRESH_RATE 					GLFW_REFRESH_RATE 
#define AE_DOUBLEBUFFER 					GLFW_DOUBLEBUFFER 
#define AE_CLIENT_API 						GLFW_CLIENT_API 
#define AE_CONTEXT_VERSION_MAJOR			GLFW_CONTEXT_VERSION_MAJOR
#define AE_CONTEXT_VERSION_MINOR			GLFW_CONTEXT_VERSION_MINOR
#define AE_CONTEXT_REVISION 				GLFW_CONTEXT_REVISION 
#define AE_CONTEXT_ROBUSTNESS 				GLFW_CONTEXT_ROBUSTNESS 
#define AE_OPENGL_FORWARD_COMPAT			GLFW_OPENGL_FORWARD_COMPAT
#define AE_OPENGL_DEBUG_CONTEXT 			GLFW_OPENGL_DEBUG_CONTEXT 
#define AE_OPENGL_PROFILE 					GLFW_OPENGL_PROFILE 
#define AE_CONTEXT_RELEASE_BEHAVIOR 		GLFW_CONTEXT_RELEASE_BEHAVIOR 
#define AE_CONTEXT_NO_ERROR 				GLFW_CONTEXT_NO_ERROR 
#define AE_CONTEXT_CREATION_API 			GLFW_CONTEXT_CREATION_API 
#define AE_SCALE_TO_MONITOR 				GLFW_SCALE_TO_MONITOR 
#define AE_COCOA_RETINA_FRAMEBUFFER 		GLFW_COCOA_RETINA_FRAMEBUFFER 
#define AE_COCOA_FRAME_NAME 				GLFW_COCOA_FRAME_NAME 
#define AE_COCOA_GRAPHICS_SWITCHING 		GLFW_COCOA_GRAPHICS_SWITCHING 
#define AE_X11_CLASS_NAME 					GLFW_X11_CLASS_NAME 
#define AE_X11_INSTANCE_NAME				GLFW_X11_INSTANCE_NAME
#define AE_NO_API 							GLFW_NO_API 
#define AE_OPENGL_API 						GLFW_OPENGL_API 
#define AE_OPENGL_ES_API					GLFW_OPENGL_ES_API
#define AE_NO_ROBUSTNESS					GLFW_NO_ROBUSTNESS
#define AE_NO_RESET_NOTIFICATION			GLFW_NO_RESET_NOTIFICATION
#define AE_LOSE_CONTEXT_ON_RESET			GLFW_LOSE_CONTEXT_ON_RESET
#define AE_OPENGL_ANY_PROFILE 				GLFW_OPENGL_ANY_PROFILE 
#define AE_OPENGL_CORE_PROFILE				GLFW_OPENGL_CORE_PROFILE
#define AE_OPENGL_COMPAT_PROFILE			GLFW_OPENGL_COMPAT_PROFILE
#define AE_CURSOR 							GLFW_CURSOR 
#define AE_STICKY_KEYS						GLFW_STICKY_KEYS
#define AE_STICKY_MOUSE_BUTTONS 			GLFW_STICKY_MOUSE_BUTTONS 
#define AE_LOCK_KEY_MODS					GLFW_LOCK_KEY_MODS
#define AE_RAW_MOUSE_MOTION 				GLFW_RAW_MOUSE_MOTION 
#define AE_CURSOR_NORMAL					GLFW_CURSOR_NORMAL
#define AE_CURSOR_HIDDEN					GLFW_CURSOR_HIDDEN
#define AE_CURSOR_DISABLED					GLFW_CURSOR_DISABLED
#define AE_ANY_RELEASE_BEHAVIOR 			GLFW_ANY_RELEASE_BEHAVIOR 
#define AE_RELEASE_BEHAVIOR_FLUSH 			GLFW_RELEASE_BEHAVIOR_FLUSH 
#define AE_RELEASE_BEHAVIOR_NONE			GLFW_RELEASE_BEHAVIOR_NONE
#define AE_NATIVE_CONTEXT_API 				GLFW_NATIVE_CONTEXT_API 
#define AE_EGL_CONTEXT_API					GLFW_EGL_CONTEXT_API
#define AE_OSMESA_CONTEXT_API 				GLFW_OSMESA_CONTEXT_API 
#define AE_ARROW_CURSOR 					GLFW_ARROW_CURSOR 
#define AE_IBEAM_CURSOR 					GLFW_IBEAM_CURSOR 
#define AE_CROSSHAIR_CURSOR 				GLFW_CROSSHAIR_CURSOR 
#define AE_HAND_CURSOR						GLFW_HAND_CURSOR
#define AE_HRESIZE_CURSOR 					GLFW_HRESIZE_CURSOR 
#define AE_VRESIZE_CURSOR 					GLFW_VRESIZE_CURSOR 
#define AE_CONNECTED						GLFW_CONNECTED
#define AE_DISCONNECTED 					GLFW_DISCONNECTED 
#define AE_JOYSTICK_HAT_BUTTONS 			GLFW_JOYSTICK_HAT_BUTTONS 
#define AE_COCOA_CHDIR_RESOURCES			GLFW_COCOA_CHDIR_RESOURCES
#define AE_COCOA_MENUBAR					GLFW_COCOA_MENUBAR
#define AE_DONT_CARE						GLFW_DONT_CARE

/* Includes */

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

/* Smart Pointer References */
using BufferHandleRef	= ae::sptr<ae::BufferHandle>;
using ShaderRef			= ae::sptr<ae::Shader>;
using TextureRef		= ae::sptr<ae::Texture>;
using TextureArrayRef	= ae::sptr<ae::TextureArray>;
using WindowRef			= ae::sptr<ae::Window>;
