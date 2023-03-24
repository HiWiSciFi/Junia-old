#include <Junia/Core/MessageBox.hpp>

#ifdef _WIN32

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>
#undef WIN32_MEAN_AND_LEAN
#undef IGNORE
#undef ERROR

namespace Junia
{
	MessageBoxResult ShowBlockingMessageBox(const std::string& title, const std::string& msg, MessageBoxIcon icon, MessageBoxButtons buttons, uint8_t defaultBtn, bool topmost)
	{
		UINT flags = MB_SETFOREGROUND;

		if (topmost) flags |= MB_TOPMOST;

		switch (icon)
		{
		case Junia::MessageBoxIcon::INFORMATION: flags |= MB_ICONINFORMATION; break;
		case Junia::MessageBoxIcon::QUESTION:    flags |= MB_ICONQUESTION;    break;
		case Junia::MessageBoxIcon::WARNING:     flags |= MB_ICONWARNING;     break;
		case Junia::MessageBoxIcon::ERROR:       flags |= MB_ICONERROR;       break;
		default: break;
		}

		switch (buttons)
		{
		case Junia::MessageBoxButtons::ABORT_RETRY_IGNORE:       flags |= MB_ABORTRETRYIGNORE;  break;
		case Junia::MessageBoxButtons::CANCEL_TRYAGAIN_CONTINUE: flags |= MB_CANCELTRYCONTINUE; break;
		case Junia::MessageBoxButtons::OK:                       flags |= MB_OK;                break;
		case Junia::MessageBoxButtons::OK_CANCEL:                flags |= MB_OKCANCEL;          break;
		case Junia::MessageBoxButtons::RETRY_CANCEL:             flags |= MB_RETRYCANCEL;       break;
		case Junia::MessageBoxButtons::YES_NO:                   flags |= MB_YESNO;             break;
		case Junia::MessageBoxButtons::YES_NO_CANCEL:            flags |= MB_YESNOCANCEL;       break;
		default: break;
		}

		switch (defaultBtn)
		{
		case 1: flags |= MB_DEFBUTTON1; break;
		case 2: flags |= MB_DEFBUTTON2; break;
		case 3: flags |= MB_DEFBUTTON3; break;
		case 4: flags |= MB_DEFBUTTON4; break;
		default: break;
		}

		int msgboxReturn = MessageBox(NULL, msg.c_str(), title.c_str(), flags);

		switch (msgboxReturn)
		{
		case IDOK:       return MessageBoxResult::OK;
		case IDCANCEL:   return MessageBoxResult::CANCEL;
		case IDABORT:    return MessageBoxResult::ABORT;
		case IDRETRY:    return MessageBoxResult::RETRY;
		case IDIGNORE:   return MessageBoxResult::IGNORE;
		case IDYES:      return MessageBoxResult::YES;
		case IDNO:       return MessageBoxResult::NO;
		case IDTRYAGAIN: return MessageBoxResult::TRYAGAIN;
		case IDCONTINUE: return MessageBoxResult::CONTINUE;
		default:         return MessageBoxResult::NONE;
		}
	}
}

#endif
