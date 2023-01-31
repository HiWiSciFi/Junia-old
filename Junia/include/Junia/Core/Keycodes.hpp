#pragma once
#include <string>

namespace Junia
{
	/**
	 * @brief Codes for mouse buttons
	*/
	enum class MouseButton : unsigned char
	{
		Left = 0,  /** @brief The primary mouse button */
		Right = 1, /** @brief The secondary mouse button */
		Middle = 2 /** @brief The middle mouse button */
	};

	/**
	 * @brief Codes for keys
	*/
	enum class KeyCode : unsigned char
	{
		HOME           = 2, /** @brief The POS1 or HOME key */
		END            = 3,
		PRINT_SCREEN   = 4,
		NUM_LOCK       = 5,
		CAPS_LOCK      = 6,
		SCROLL_LOCK    = 7,
		BACKSPACE      = 8,
		TAB            = 9,
		ENTER          = 10,
		MENU           = 12,
		PAGE_UP        = 14,
		PAGE_DOWN      = 15,
		PAUSE          = 22,
		INSERT         = 26,
		ESCAPE         = 27,

		SPACE          = 32,

		APOSTROPHE     = 39,  /* ' */
		COMMA          = 44,  /* , */
		MINUS          = 45,  /* - */
		PERIOD         = 46,  /* . */
		SLASH          = 47,  /* / */

		KEY_0          = 48,
		KEY_1          = 49,
		KEY_2          = 50,
		KEY_3          = 51,
		KEY_4          = 52,
		KEY_5          = 53,
		KEY_6          = 54,
		KEY_7          = 55,
		KEY_8          = 56,
		KEY_9          = 57,

		SEMICOLON      = 59,  /* ; */
		EQUAL          = 61,  /* = */

		A              = 65,
		B              = 66,
		C              = 67,
		D              = 68,
		E              = 69,
		F              = 70,
		G              = 71,
		H              = 72,
		I              = 73,
		J              = 74,
		K              = 75,
		L              = 76,
		M              = 77,
		N              = 78,
		O              = 79,
		P              = 80,
		Q              = 81,
		R              = 82,
		S              = 83,
		T              = 84,
		U              = 85,
		V              = 86,
		W              = 87,
		X              = 88,
		Y              = 89,
		Z              = 90,

		LEFT_BRACKET   = 91,  /* [ */
		BACKSLASH      = 92,  /* \ */
		RIGHT_BRACKET  = 93,  /* ] */
		GRAVE_ACCENT   = 96,  /* ^ */

		ARROW_LEFT     = 97,  /* <- */
		ARROW_UP       = 98,  /* /\ */
		ARROW_RIGHT    = 99,  /* -> */
		ARROW_DOWN     = 100, /* \/ */

		F1             = 101,
		F2             = 102,
		F3             = 103,
		F4             = 104,
		F5             = 105,
		F6             = 106,
		F7             = 107,
		F8             = 108,
		F9             = 109,
		F10            = 110,
		F11            = 111,
		F12            = 112,
		F13            = 113,
		F14            = 114,
		F15            = 115,
		F16            = 116,
		F17            = 117,
		F18            = 118,
		F19            = 119,
		F20            = 120,
		F21            = 121,
		F22            = 122,
		F23            = 123,
		F24            = 124,
		F25            = 125,

		DEL            = 127, /* Delete */

		LEFT_SHIFT     = 128,
		RIGHT_SHIFT    = 129,
		LEFT_CONTROL   = 130,
		RIGHT_CONTROL  = 131,
		LEFT_ALT       = 132,
		RIGHT_ALT      = 133,
		LEFT_SUPER     = 134, /** @brief The left Windows Key or platform equivalent */
		RIGHT_SUPER    = 135, /** @brief The right Windows Key or platform equivalent */

		NUM_ENTER      = 202, /* 0xa | 192 */
		NUM_MULTIPLY   = 234, /* '*' | 192 */
		NUM_ADD        = 235, /* '+' | 192 */
		NUM_SUBTRACT   = 237, /* '-' | 192 */
		NUM_DECIMAL    = 238, /* '.' | 192 */
		NUM_DIVIDE     = 239, /* '/' | 192 */
		NUM_0          = 240, /* '0' | 192 */
		NUM_1          = 241, /* '1' | 192 */
		NUM_2          = 242, /* '2' | 192 */
		NUM_3          = 243, /* '3' | 192 */
		NUM_4          = 244, /* '4' | 192 */
		NUM_5          = 245, /* '5' | 192 */
		NUM_6          = 246, /* '6' | 192 */
		NUM_7          = 247, /* '7' | 192 */
		NUM_8          = 248, /* '8' | 192 */
		NUM_9          = 249, /* '9' | 192 */
		NUM_EQUAL      = 253  /* '=' | 192 */
	};

	/**
	 * @brief Converts a mouse button code to a string
	 * @param button the button code to get a string representation for
	 * @return a human readable string representing the MouseButton
	*/
	std::string MouseButtonToString(MouseButton button);

	/**
	 * @brief Converts a KeyCode to a string
	 * @param code the key code to get a string representation for
	 * @return a human readable string representing the KeyCode
	*/
	std::string KeyToString(KeyCode code);

	static constexpr unsigned char JeToGlfwButton[3] = {
		0, 1, 2
	};

	static constexpr unsigned char GlfwToJeButton[8] = {
		0, 1, 2, 0, 0, 0, 0, 0
	};

	static constexpr unsigned short JeToGlfwKey[254] = {
		  0,   0, 268, 269, 283, 282, 280, 281, 259, 258, 257,   0, 348,   0, 266, 267,   0,   0,   0,   0,   0,   0,
		284,   0,   0,   0, 260, 256,   0,   0,   0,   0,  32,   0,   0,   0,   0,   0,   0,  39,   0,   0,   0,   0,
		 44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,   0,  59,   0,  61,   0,   0,   0,  65,
		 66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,
		 88,  89,  90,  91,  92,  93,   0,   0,  96, 263, 265, 262, 264, 290, 291, 292, 293, 294, 295, 296, 297, 298,
		299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314,   0, 261, 340, 344, 341, 345,
		342, 346, 343, 347,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0, 335,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 332, 334,   0, 333, 330, 331, 320, 321,
		322, 323, 324, 325, 326, 327, 328, 329,   0,   0,   0, 336
	};

	static constexpr unsigned short GlfwToJeKey[349] = {
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  32,   0,   0,   0,   0,   0,   0,  39,   0,   0,   0,   0,
		 44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,   0,  59,   0,  61,   0,   0,   0,  65,
		 66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,
		 88,  89,  90,  91,  92,  93,   0,   0,  96,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  27,  10,   9,   8,  26, 127,  99,  97,
		100,  98,  14,  15,   2,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   6,   7,   5,   4,  22,   0,
		  0,   0,   0,   0, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118,
		119, 120, 121, 122, 123, 124, 125,   0,   0,   0,   0,   0, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249,
		238, 239, 234, 237, 235, 202, 253,   0,   0,   0, 128, 130, 132, 134, 129, 131, 133, 135,  12
	};
}
