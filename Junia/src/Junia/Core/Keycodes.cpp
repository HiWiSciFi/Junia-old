#include "Core.hpp"
#include <Junia/Core/Keycodes.hpp>
#include <sstream>

namespace Junia
{
	std::string ButtonToString(MouseButton button)
	{
		switch (button)
		{
		case Junia::MouseButton::Left:   return   "Mouse Primary"; break;
		case Junia::MouseButton::Right:  return "Mouse Secondary"; break;
		case Junia::MouseButton::Middle: return    "Mouse Middle"; break;
		default: return "Unknown Button";
		}
	}

	std::string KeyToString(KeyCode code)
	{
		std::stringstream ss{ };
		unsigned char keycode = static_cast<unsigned char>(code);
		// keycodes that are ascii codes
		if (keycode == 39 || (keycode >= 44 && keycode <= 57) || keycode == 59
			|| keycode == 61 || (keycode >= 65 && keycode <= 93) || keycode == 96)
		{
			ss << static_cast<char>(keycode);
		}
		else if (keycode >= 202) // NUMPAD
		{
			ss << "Numpad ";
			if ((keycode >= 237 && keycode <= 249) || keycode == 234 || keycode == 235 || keycode == 253)
				ss << static_cast<char>(keycode & ~static_cast<unsigned char>(192));
			else if (keycode == 202) ss << "Enter";
			else return "Unknown Key";
		}
		else if (keycode >= 101 && keycode <= 125) // F-Keys
		{
			ss << "F" << static_cast<int>(keycode - 100);
		}
		else
		{
			switch (keycode)
			{
			case   2: ss << "Home"; break;
			case   3: ss << "End"; break;
			case   4: ss << "Print Screen"; break;
			case   5: ss << "Num Lock"; break;
			case   6: ss << "Caps Lock"; break;
			case   7: ss << "Scroll Lock"; break;
			case   8: ss << "Backspace"; break;
			case   9: ss << "Tab"; break;
			case  10: ss << "Enter"; break;
			case  12: ss << "Menu"; break;
			case  14: ss << "Page Up"; break;
			case  15: ss << "Page Down"; break;
			case  22: ss << "Pause"; break;
			case  26: ss << "Insert"; break;
			case  27: ss << "Escape"; break;
			case  32: ss << "Space"; break;
			case  97: ss << "Arrow Left"; break;
			case  98: ss << "Arrow Up"; break;
			case  99: ss << "Arrow Right"; break;
			case 100: ss << "Arrow Down"; break;
			case 127: ss << "Delete"; break;
			case 128: ss << "Left Shift"; break;
			case 129: ss << "Right Shift"; break;
			case 130: ss << "Left Control"; break;
			case 131: ss << "Right Control"; break;
			case 132: ss << "Left Alt"; break;
			case 133: ss << "Right Alt"; break;
			case 134: ss << "Left Super"; break;
			case 135: ss << "Right Super"; break;
			default:   return "Unknown Key";
			}
		}
		return ss.str();
	}
}
