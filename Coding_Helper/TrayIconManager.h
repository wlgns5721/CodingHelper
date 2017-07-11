#include "stdafx.h"

#define MAKE_TRAY_MESSAGE WM_APP + 1
#define ACTIVE_MESSAGE WM_USER + 2
#define EXIT_MESSAGE WM_USER + 3

class CTrayIconManager {
public:
	void MakePopUpMenu(HWND hWnd, int x, int y);
	
};
