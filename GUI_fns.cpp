#include "GUI_fns.h"

SIZE GetWindowSize(HWND window) {
	RECT rc;
	GetClientRect(window, &rc);
	SIZE sz = {
		.cx = rc.right - rc.left,
		.cy = rc.bottom - rc.top
	};
	return sz;
}