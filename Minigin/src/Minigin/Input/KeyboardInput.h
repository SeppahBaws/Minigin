#pragma once

#include <SDL_scancode.h>

namespace dae
{
	enum class Key
	{
		A				= SDL_SCANCODE_A,
		B				= SDL_SCANCODE_B,
		C				= SDL_SCANCODE_C,
		D				= SDL_SCANCODE_D,
		E				= SDL_SCANCODE_E,
		F				= SDL_SCANCODE_F,
		G				= SDL_SCANCODE_G,
		H				= SDL_SCANCODE_H,
		I				= SDL_SCANCODE_I,
		J				= SDL_SCANCODE_J,
		K				= SDL_SCANCODE_K,
		L				= SDL_SCANCODE_L,
		M				= SDL_SCANCODE_M,
		N				= SDL_SCANCODE_N,
		O				= SDL_SCANCODE_O,
		P				= SDL_SCANCODE_P,
		Q				= SDL_SCANCODE_Q,
		R				= SDL_SCANCODE_R,
		S				= SDL_SCANCODE_S,
		T				= SDL_SCANCODE_T,
		U				= SDL_SCANCODE_U,
		V				= SDL_SCANCODE_V,
		W				= SDL_SCANCODE_W,
		X				= SDL_SCANCODE_X,
		Y				= SDL_SCANCODE_Y,
		Z				= SDL_SCANCODE_Z,

		/*
		 * Numbers row
		 */
		Num1			= SDL_SCANCODE_1,
		Num2			= SDL_SCANCODE_2,
		Num3			= SDL_SCANCODE_3,
		Num4			= SDL_SCANCODE_4,
		Num5			= SDL_SCANCODE_5,
		Num6			= SDL_SCANCODE_6,
		Num7			= SDL_SCANCODE_7,
		Num8			= SDL_SCANCODE_8,
		Num9			= SDL_SCANCODE_9,
		Num0			= SDL_SCANCODE_0,

		Enter			= SDL_SCANCODE_RETURN,
		Escape			= SDL_SCANCODE_ESCAPE,
		Backspace		= SDL_SCANCODE_BACKSPACE,
		Tab				= SDL_SCANCODE_TAB,
		Space			= SDL_SCANCODE_SPACE,

		Minus			= SDL_SCANCODE_MINUS,
		Equals			= SDL_SCANCODE_EQUALS,
		LeftBracket		= SDL_SCANCODE_LEFTBRACKET,
		RightBracket	= SDL_SCANCODE_RIGHTBRACKET,
		Backslash		= SDL_SCANCODE_BACKSLASH,

		Semicolon		= SDL_SCANCODE_SEMICOLON,
		Quote			= SDL_SCANCODE_APOSTROPHE,
		BackQuote		= SDL_SCANCODE_GRAVE,

		Comma			= SDL_SCANCODE_COMMA,
		Period			= SDL_SCANCODE_PERIOD,
		Slash			= SDL_SCANCODE_SLASH,

		F1				= SDL_SCANCODE_F1,
		F2				= SDL_SCANCODE_F2,
		F3				= SDL_SCANCODE_F3,
		F4				= SDL_SCANCODE_F4,
		F5				= SDL_SCANCODE_F5,
		F6				= SDL_SCANCODE_F6,
		F7				= SDL_SCANCODE_F7,
		F8				= SDL_SCANCODE_F8,
		F9				= SDL_SCANCODE_F9,
		F10				= SDL_SCANCODE_F10,
		F11				= SDL_SCANCODE_F11,
		F12				= SDL_SCANCODE_F12,

		PrintScreen		= SDL_SCANCODE_PRINTSCREEN,
		CapsLock		= SDL_SCANCODE_CAPSLOCK,
		ScrollLock		= SDL_SCANCODE_SCROLLLOCK,
		Pause			= SDL_SCANCODE_PAUSE,
		Insert			= SDL_SCANCODE_INSERT,

		PageUp			= SDL_SCANCODE_PAGEUP,
		PageDown		= SDL_SCANCODE_PAGEDOWN,
		Home			= SDL_SCANCODE_HOME,
		End				= SDL_SCANCODE_END,
		Delete			= SDL_SCANCODE_DELETE,
		Right			= SDL_SCANCODE_RIGHT,
		Left			= SDL_SCANCODE_LEFT,
		Down			= SDL_SCANCODE_DOWN,
		Up				= SDL_SCANCODE_UP,

		/*
		 * Keypad
		 */
		KP_Divide		= SDL_SCANCODE_KP_DIVIDE,
		KP_Multiply		= SDL_SCANCODE_KP_MULTIPLY,
		KP_Minus		= SDL_SCANCODE_KP_MINUS,
		KP_Plus			= SDL_SCANCODE_KP_PLUS,
		KP_Enter		= SDL_SCANCODE_KP_ENTER,
		KP_1			= SDL_SCANCODE_KP_1,
		KP_2			= SDL_SCANCODE_KP_2,
		KP_3			= SDL_SCANCODE_KP_3,
		KP_4			= SDL_SCANCODE_KP_4,
		KP_5			= SDL_SCANCODE_KP_5,
		KP_6			= SDL_SCANCODE_KP_6,
		KP_7			= SDL_SCANCODE_KP_7,
		KP_8			= SDL_SCANCODE_KP_8,
		KP_9			= SDL_SCANCODE_KP_9,
		KP_0			= SDL_SCANCODE_KP_0,
		KP_Period		= SDL_SCANCODE_KP_PERIOD,

		/*
		 * Modifier Keys
		 */
		L_Ctrl			= SDL_SCANCODE_LCTRL,
		L_Shift			= SDL_SCANCODE_LSHIFT,
		L_Alt			= SDL_SCANCODE_LALT,
		L_Win			= SDL_SCANCODE_LGUI,
		R_Ctrl			= SDL_SCANCODE_RCTRL,
		R_Shift			= SDL_SCANCODE_RSHIFT,
		R_Alt			= SDL_SCANCODE_RALT,
		R_Win			= SDL_SCANCODE_RGUI,
	};

	// Used for internal state storing
#define KEYS_REGION_1_BEGIN 4   // First keyboard region start
#define KEYS_REGION_2_BEGIN 68  // Second keyboard region start
#define KEYS_REGION_2_END 99    // Second keyboard region end
#define KEYS_REGION_3_BEGIN 224 // Modifier keys
}
