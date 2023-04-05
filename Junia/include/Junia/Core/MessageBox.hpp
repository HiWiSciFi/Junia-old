#pragma once

#include <cstdint>
#include <string>

namespace Junia
{
	enum class MessageBoxButtons : uint8_t
	{
		NONE,
		ABORT_RETRY_IGNORE,
		CANCEL_TRYAGAIN_CONTINUE,
		OK,
		OK_CANCEL,
		RETRY_CANCEL,
		YES_NO,
		YES_NO_CANCEL
	};

	enum class MessageBoxIcon : uint8_t
	{
		NONE        = 0,
		INFORMATION = 1,
		QUESTION    = 2,
		WARNING     = 3,
		ERROR       = 4
	};

	enum class MessageBoxResult : uint8_t
	{
		NONE     = 0,
		YES      = 1,
		OK       = 2,
		RETRY    = 3,
		TRYAGAIN = 4,
		CONTINUE = 5,
		IGNORE   = 6,
		NO       = 7,
		CANCEL   = 8,
		ABORT    = 9
	};

	MessageBoxResult ShowBlockingMessageBox(const std::string& title, const std::string& msg, MessageBoxIcon icon, MessageBoxButtons buttons, uint8_t defaultBtn = 1, bool topmost = false);
} // namespace Junia
