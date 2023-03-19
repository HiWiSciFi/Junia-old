#include <Junia/Core/MessageBox.hpp>

#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cstring>
#include <stdexcept>

#include <iostream>

namespace Junia
{
	// TODO: rework

	typedef struct
	{
		const wchar_t* label;
		MessageBoxResult result;
	} Button;

	static const Button OK_BUTTON       = { L"Ok",        MessageBoxResult::OK       };
	static const Button YES_BUTTON      = { L"Yes",       MessageBoxResult::YES      };
	static const Button NO_BUTTON       = { L"No",        MessageBoxResult::NO       };
	static const Button CANCEL_BUTTON   = { L"Cancel",    MessageBoxResult::CANCEL   };
	static const Button RETRY_BUTTON    = { L"Retry",     MessageBoxResult::RETRY    };
	static const Button ABORT_BUTTON    = { L"Abort",     MessageBoxResult::ABORT    };
	static const Button IGNORE_BUTTON   = { L"Ignore",    MessageBoxResult::IGNORE   };
	static const Button TRYAGAIN_BUTTON = { L"Try Again", MessageBoxResult::TRYAGAIN };
	static const Button CONTINUE_BUTTON = { L"Continue",  MessageBoxResult::CONTINUE };

	typedef struct
	{
		const Button* button;
		GC* gc;
		XRectangle rect;
	} ButtonData;

	typedef struct
	{
		unsigned int winMinWidth;
		unsigned int winMinHeight;
		unsigned int lineSpacing;
		unsigned int barHeight;
		unsigned int pad_up;
		unsigned int pad_down;
		unsigned int pad_left;
		unsigned int pad_right;
		unsigned int btSpacing;
		unsigned int btMinWidth;
		unsigned int btMinHeight;
		unsigned int btLateralPad;
	} Dimensions;

	Dimensions dim = { 40, 0, 5, 50, 30, 10, 30, 30, 20, 75, 25, 8 };

	static void setWindowTitle(const char* title, const Window* win, Display* dpy)
	{
		Atom wm_Name = XInternAtom(dpy, "_NET_WM_NAME", False);
		Atom utf8Str = XInternAtom(dpy, "UTF8_STRING", False);
		XChangeProperty(dpy, *win, wm_Name, utf8Str, 8, PropModeReplace, (const unsigned char*)title, (int)strlen(title));

		Atom winType = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", False);
		Atom typeDialog = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DIALOG", False);
		XChangeProperty(dpy, *win, winType, XA_ATOM, 32, PropModeReplace, (unsigned char*)&typeDialog, 1);
	}

	static void split(const wchar_t* text, const wchar_t* seps, wchar_t*** str, int* count)
	{
		wchar_t* last;
		wchar_t* tok;
		wchar_t* data;
		int i;
		*count = 0;
		data = wcsdup(text);

		for (tok = wcstok(data, seps, &last); tok != NULL; tok = wcstok(NULL, seps, &last)) (*count)++;

		free(data);
		fflush(stdout);

		data = wcsdup(text);
		*str = (wchar_t**)malloc((size_t)(*count) * sizeof(wchar_t*));

		for (i = 0, tok = wcstok(data, seps, &last); tok != NULL; tok = wcstok(NULL, seps, &last), i++)
			(*str)[i] = wcsdup(tok);

		free(data);
	}

	static void computeTextSize(XFontSet* fs, wchar_t** texts, int size, unsigned int spaceBetweenLines, unsigned int* w, unsigned int* h)
	{
		int i;
		XRectangle rect = { 0, 0, 0, 0 };
		*h = 0;
		*w = 0;
		for (i = 0; i < size; i++)
		{
			XwcTextExtents(*fs, texts[i], (int)wcslen(texts[i]), &rect, NULL);
			*w = (rect.width > *w) ? rect.width : *w;
			*h +=rect.height + spaceBetweenLines;
			fflush(stdin);
		}
	}

	static void createGC(GC* gc, const Colormap* cmap, Display* dpy, const Window* win, unsigned char red, unsigned char green, unsigned char blue)
	{
		float colorratio = (float) 65535 / 255;
		XColor color;
		*gc = XCreateGC(dpy, *win, 0, 0);
		memset(&color, 0, sizeof(color));
		color.red   = (unsigned short)(colorratio * red  );
		color.green = (unsigned short)(colorratio * green);
		color.blue  = (unsigned short)(colorratio * blue );
		color.flags = DoRed | DoGreen | DoBlue;
		XAllocColor(dpy, *cmap, &color);
		XSetForeground(dpy, *gc, color.pixel);
	}

	static bool isInside(int x, int y, XRectangle rect)
	{
		if (x < rect.x || x > (rect.x + rect.width) || y < rect.y || y > (rect.y + rect.height))
			return false;
		return true;
	}

	MessageBoxResult ShowMessageBox(const std::string& title, const std::string& msg, MessageBoxIcon icon, MessageBoxButtons buttons, uint8_t defaultBtn, bool topmost)
	{
		setlocale(LC_ALL, "");

		std::wstring wmsg(msg.begin(), msg.end());

// -------------------------------- convert the text in list (to draw in muliple lines) --------------------------------
		wchar_t** tex_splitted = NULL;
		int textLines = 0;
		split(wmsg.c_str(), L"\n", &tex_splitted, &textLines);
// ---------------------------------------------------------------------------------------------------------------------

		Display* dpy = NULL;
		dpy = XOpenDisplay(0);
		if (dpy == NULL) throw std::runtime_error("failed to open display");

		int ds = DefaultScreen(dpy);
		Window win = XCreateSimpleWindow(dpy, RootWindow(dpy, ds), 0, 0, 800, 100, 1, BlackPixel(dpy, ds), WhitePixel(dpy, ds));
		XSelectInput(dpy, win, ExposureMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask);
		XMapWindow(dpy, win);

// ---------------------------- allow windows to be closed by pressing cross (but it won't) ----------------------------
		Atom WM_DELETE_WINDOW = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(dpy, win, &WM_DELETE_WINDOW, 1);

// ------------------------------------------- create the gc for drawing text ------------------------------------------
		XGCValues gcValues;
		gcValues.font = XLoadFont(dpy, "7x13");
		gcValues.foreground = BlackPixel(dpy, 0);
		GC textGC = XCreateGC(dpy, win, GCFont | GCForeground, &gcValues);
		XUnmapWindow(dpy, win);
// ---------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------- create fontset --------------------------------------------------
		char** missingCharset_list = NULL;
		int missingCharset_count = 0;
		XFontSet fs;
		fs = XCreateFontSet(dpy, "-*-*-medium-r-normal-*-12-*-*-*-*-*-*-*", &missingCharset_list, &missingCharset_count, NULL);
		if (missingCharset_count > 0)
		{
			std::string errorString("missing charsets: \n");
			for (int i = 0; i < missingCharset_count; i++)
			{
				errorString += missingCharset_list[i];
				if (i != missingCharset_count - 1) errorString += "\n";
			}
			XFreeStringList(missingCharset_list);
			missingCharset_list = NULL;
			//throw std::runtime_error(errorString.c_str());
		}
// ---------------------------------------------------------------------------------------------------------------------

		Colormap cmap = DefaultColormap(dpy, ds);

// -------------------------------------- resite the window according to text size -------------------------------------
		unsigned int winW, winH;
		unsigned int textW, textH;

		// calculate the ideal window's size
		computeTextSize(&fs, tex_splitted, textLines, dim.lineSpacing, &textW, &textH);
		unsigned int newWidth = textW + dim.pad_left + dim.pad_right;
		unsigned int newHeight = textH + dim.pad_up + dim.pad_down + dim.barHeight;
		winW = (newWidth > dim.winMinWidth) ? newWidth : dim.winMinWidth;
		winH = (newHeight > dim.winMinHeight) ? newHeight : dim.winMinHeight;

		// set window hints
		XSizeHints hints{ };
		hints.flags = PSize | PMinSize | PMaxSize;
		hints.min_width = winW;
		hints.max_width = winW;
		hints.base_width = winW;
		hints.min_height = winH;
		hints.max_height = winH;
		hints.base_height = winH;

		std::cout << "Size: " << winW << "x" << winH << std::endl;

		XSetWMNormalHints(dpy, win, &hints);
		XMapRaised(dpy, win);
// ---------------------------------------------------------------------------------------------------------------------

		GC barGC;
		GC buttonGC;
		GC buttonGC_underPointer;
		GC buttonGC_onClick;
		createGC(&barGC,                 &cmap, dpy, &win, 242, 242, 242);
		createGC(&buttonGC,              &cmap, dpy, &win, 202, 202, 202);
		createGC(&buttonGC_underPointer, &cmap, dpy, &win, 192, 192, 192);
		createGC(&buttonGC_onClick,      &cmap, dpy, &win, 182, 182, 182);

// ----------------------------------------------- setup the buttons data ----------------------------------------------

		ButtonData* btsData;
		int numButtons = 0;
		switch (buttons)
		{
		case Junia::MessageBoxButtons::OK:                       numButtons = 1; break;
		case Junia::MessageBoxButtons::YES_NO:                   numButtons = 2; break;
		case Junia::MessageBoxButtons::OK_CANCEL:                numButtons = 2; break;
		case Junia::MessageBoxButtons::RETRY_CANCEL:             numButtons = 2; break;
		case Junia::MessageBoxButtons::YES_NO_CANCEL:            numButtons = 3; break;
		case Junia::MessageBoxButtons::ABORT_RETRY_IGNORE:       numButtons = 3; break;
		case Junia::MessageBoxButtons::CANCEL_TRYAGAIN_CONTINUE: numButtons = 3; break;
		default: break;
		}
		btsData = (ButtonData*)malloc((size_t)numButtons * sizeof(ButtonData));

		int pass = 0;
		switch (buttons)
		{
		case Junia::MessageBoxButtons::OK:
			{
				btsData[0].button = &OK_BUTTON;
			}
			break;
		case Junia::MessageBoxButtons::YES_NO:
			{
				btsData[0].button = &YES_BUTTON;
				btsData[1].button = &NO_BUTTON;
			}
			break;
		case Junia::MessageBoxButtons::OK_CANCEL:
			{
				btsData[0].button = &OK_BUTTON;
				btsData[1].button = &CANCEL_BUTTON;
			}
			break;
		case Junia::MessageBoxButtons::RETRY_CANCEL:
			{
				btsData[0].button = &RETRY_BUTTON;
				btsData[1].button = &CANCEL_BUTTON;
			}
			break;
		case Junia::MessageBoxButtons::YES_NO_CANCEL:
			{
				btsData[0].button = &YES_BUTTON;
				btsData[1].button = &NO_BUTTON;
				btsData[2].button = &CANCEL_BUTTON;
			}
			break;
		case Junia::MessageBoxButtons::ABORT_RETRY_IGNORE:
			{
				btsData[0].button = &ABORT_BUTTON;
				btsData[1].button = &RETRY_BUTTON;
				btsData[2].button = &IGNORE_BUTTON;
			}
			break;
		case Junia::MessageBoxButtons::CANCEL_TRYAGAIN_CONTINUE:
			{
				btsData[0].button = &CANCEL_BUTTON;
				btsData[1].button = &TRYAGAIN_BUTTON;
				btsData[2].button = &CONTINUE_BUTTON;
			}
			break;
		default: break;
		}
		for (int i = 0; i < numButtons; i++)
		{
			btsData[i].gc = &buttonGC;
			XRectangle btTextDim;
			XwcTextExtents(fs, btsData[i].button->label, (int)wcslen(btsData[i].button->label), &btTextDim, NULL);
			btsData[i].rect.width = (btTextDim.width < dim.btMinWidth) ? dim.btMinWidth : (btTextDim.width + 2 * dim.btLateralPad);
			btsData[i].rect.height = (dim.btMinHeight);
			btsData[i].rect.x = winW - dim.pad_left - btsData[i].rect.width - pass;
			btsData[i].rect.y = textH + dim.pad_up + dim.pad_down + ((dim.barHeight - dim.btMinHeight) / 2);
			pass += btsData[i].rect.width + dim.btSpacing;
		}
// ---------------------------------------------------------------------------------------------------------------------

		setWindowTitle(title.c_str(), &win, dpy);
		XFlush(dpy);

		bool quit = false;
		MessageBoxResult result = MessageBoxResult::NONE;

		while (!quit)
		{
			XEvent e;
			XNextEvent(dpy, &e);

			switch (e.type)
			{
			case MotionNotify:
			case ButtonPress:
			case ButtonRelease:
				for (int i = 0; i < numButtons; i++)
				{
					btsData[i].gc = &buttonGC;
					if (isInside(e.xmotion.x, e.xmotion.y, btsData[i].rect))
					{
						btsData[i].gc = &buttonGC_underPointer;
						if (e.type == ButtonPress && e.xbutton.button == Button1)
						{
							btsData[i].gc = &buttonGC_onClick;
							result = btsData[i].button->result;
							quit = true;
							break;
						}
					}
				}
				break;

			case Expose:
				// draw the text in multiple lines
				for (int i = 0; i < textLines; i++)
					XwcDrawString(dpy, win, fs, textGC, dim.pad_left, dim.pad_up + i * (dim.lineSpacing + 18), tex_splitted[i], (int)wcslen(tex_splitted[i]));

				XFillRectangle(dpy, win, barGC, 0, textH + dim.pad_up + dim.pad_down, winW, dim.barHeight);

				for (int i = 0; i < numButtons; i++)
				{
					XFillRectangle(dpy, win, *btsData[i].gc, btsData[i].rect.x, btsData[i].rect.y, btsData[i].rect.width, btsData[i].rect.height);
					XRectangle btTextDim;
					XwcTextExtents(fs, btsData[i].button->label, (int)wcslen(btsData[i].button->label), &btTextDim, NULL);
					XwcDrawString(dpy, win, fs, textGC,
						btsData[i].rect.x + (btsData[i].rect.width - btTextDim.width) / 2,
						btsData[i].rect.y + (btsData[i].rect.height - btTextDim.height) / 2,
						btsData[i].button->label, (int)wcslen(btsData[i].button->label)
					);
				}
				XFlush(dpy);
				break;

			case ClientMessage:
				//if window's cross button pressed does nothing
				/*if((unsigned int)(e.xclient.data.l[0]) == WM_DELETE_WINDOW)
					quit = true;*/
				break;

			default: break;
			}
		}

		for (int i = 0; i < textLines; i++)
			free(tex_splitted[i]);
		free(tex_splitted);
		free(btsData);
		if (missingCharset_list)
			XFreeStringList(missingCharset_list);
		XDestroyWindow(dpy, win);
		XFreeFontSet(dpy, fs);
		XFreeGC(dpy, textGC);
		XFreeGC(dpy, barGC);
		XFreeGC(dpy, buttonGC);
		XFreeGC(dpy, buttonGC_underPointer);
		XFreeGC(dpy, buttonGC_onClick);
		XFreeColormap(dpy, cmap);
		XCloseDisplay(dpy);

		return result;
	}
}

#endif
