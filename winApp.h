
#ifndef _WINAPP_H
#define _WINAPP_H

#include		<windows.h>   	/* master include file for Windows applications */

/* Set-up code for GDI+ */
#include		<gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

char szWinName[] = "PPAIEGwindow";		/* name of window class */

LRESULT CALLBACK fnWindowProcedure(HWND, UINT, WPARAM, LPARAM);
void fnDefineWindowClass(WNDCLASSEX * windowClass, HINSTANCE hThisAppInstance);
HWND fnCreateWindow(HINSTANCE hThisAppInstance);
void fnDisplayWindow(HWND hWindowHandle, int nWindowMode);

#endif /* _WINAPP_H */


