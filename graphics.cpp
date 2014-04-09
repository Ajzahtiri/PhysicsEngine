#include		"graphics.h"
#include		"definitions.h"

GraphicsM::GraphicsM()
{
			
}

int GraphicsM::graphicsModuleInit(HWND hWnd)
{
	setViewport();
	initMemDC(hWnd);
	return 1;
}

int GraphicsM::setViewport()
{	
	viewport.left = VIEWPORT_LEFT; viewport.top = VIEWPORT_UP; viewport.right = VIEWPORT_RIGHT; viewport.bottom = VIEWPORT_DOWN;	
	return 1;
}

RECT GraphicsM::getViewport()
{
	return viewport;
}

void GraphicsM::initMemDC(HWND hWnd)
{
	HBITMAP		hBitMap;					/* handle to bitmap */
	HDC			hdc = GetDC(hWnd); 			/* get handle to device context */

	backBufWidth = viewport.right;
	backBufHeight = viewport.bottom;

	hMdc = CreateCompatibleDC(hdc);			/* get handle to memory device context
        									(which will hold bitmap prior to actual display) */
	/* create bitmap (back buffer) which is compatible with display device context */
	hBitMap = CreateCompatibleBitmap(hdc, backBufWidth, backBufHeight);
	SelectObject(hMdc, hBitMap);			/* select bitmap into memory device context */
	PatBlt(hMdc, 0, 0, backBufWidth, backBufHeight, PATCOPY);	/* Erase current content
        					of bitmap-buffer by setting bitmap to background colour of window */

	ReleaseDC(hWnd, hdc); 					/* release device context */
}

void GraphicsM::graphicsCleanUp()
{
	return;
}

int GraphicsM::displayBackBuffer(HWND hWnd)
	{
	HDC         	hdc ;			/* handle to device context */

	// Display back-buffer bitmap (transfer it from memory to display) 
	hdc = GetDC(hWnd);	// get handle to device context
	// dipslay back-buffer bitmap (i.e. transfer it from memory to display) */
	BitBlt(hdc, 0, 0, backBufWidth, backBufHeight, hMdc, 0, 0, SRCCOPY);

	/* release device context */
	ReleaseDC (hWnd, hdc);

	return 1;
	}

int GraphicsM::drawHUD()
	{
	/* GDI variables */
	HGDIOBJ		hPreviousBrush;		// handle for previous brush
	HBRUSH		hBlueBrush;			// handle for blue custom brush
	HBRUSH		hWhiteBrush;		// handle for white custom brush

	/* TO DO: add relevant code */

	// sky (blue colour)
	hBlueBrush = CreateSolidBrush(RGB(0,192,255));	// blue brush
	hPreviousBrush = SelectObject(hMdc, hBlueBrush);
	Rectangle(hMdc, viewport.left, viewport.top, viewport.right, viewport.bottom);
	SelectObject(hMdc, hPreviousBrush);	// restore previous brush
    // free resources which are no longer needed
    DeleteObject(hBlueBrush);

	// ground (brown colour)
	hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	hPreviousBrush = SelectObject(hMdc, hWhiteBrush);
	Rectangle(hMdc, viewport.left, viewport.bottom - 40, viewport.right, viewport.bottom);
	SelectObject(hMdc, hPreviousBrush);	// restore previous brush
    // free resources which are no longer needed
    DeleteObject(hWhiteBrush);

	return 1;
	}


/*
    Draws a polygon.

	Parameter list
		polygon       array containing vertices of polygon to be drawn.
		vertexCount   number of vertices.
		closed        flag indicating whether polygon is closed or not.
  */
int GraphicsM::drawPolygon(Point2D polygon[], int vertexCount, bool closed)
{
	/* display polygon */
	// draw outline shape using current pen
	MoveToEx(hMdc, (int)(polygon[0].x + 0.5), (int)(polygon[0].y + 0.5), NULL);
	for (int i = 1; i < vertexCount; ++i)
		LineTo(hMdc, (int)(polygon[i].x + 0.5), (int)(polygon[i].y + 0.5));

	if (closed == true)	// closed polygon
		LineTo(hMdc, (int)(polygon[0].x + 0.5), (int)(polygon[0].y + 0.5));

	return 1;
}

int GraphicsM::drawText()
{
	RECT tr1;
	RECT tr2;
	tr1.left = 10;
	tr1.top = 10;
	tr1.right = 100;
	tr1.bottom = 100;
	tr2.left = 10;
	tr2.top = 30;
	tr2.right = 100;
	tr2.bottom = 100;

	SetTextColor(hMdc, 0x0000000);
	SetBkMode(hMdc, TRANSPARENT);

	DrawText(hMdc, "A - Buggy Left | D Buggy Right", -1, &tr1, DT_SINGLELINE | DT_NOCLIP);
	DrawText(hMdc, "Z - Start Snow | X - Stop Snow | C - Left Wind | V - Right Wind", -1, &tr2, DT_SINGLELINE | DT_NOCLIP);

	return 1;
}

int GraphicsM::drawBuggy(Point2D tp)
{
	HGDIOBJ		hpb;	
	
	HBRUSH		bodyB;
	HBRUSH		wheel1B;
	HBRUSH		wheel2B;

	// left - top - right - bottom
	bodyB = CreateSolidBrush(RGB(255, 204, 204));	
	hpb = SelectObject(hMdc, bodyB);
	Rectangle(hMdc, tp.x, tp.y - 25, tp.x + 40, tp.y - 1);
	SelectObject(hMdc, hpb);
    DeleteObject(bodyB);

	wheel1B = CreateSolidBrush(RGB(0, 0, 0));
	hpb = SelectObject(hMdc, wheel1B);
	Rectangle(hMdc, tp.x - 2, tp.y - 8, tp.x + 6, tp.y);
	SelectObject(hMdc, hpb);
    DeleteObject(wheel1B);

	wheel2B = CreateSolidBrush(RGB(0, 0, 0));
	hpb = SelectObject(hMdc, wheel1B);
	Rectangle(hMdc, tp.x + 34, tp.y - 8, tp.x + 42, tp.y);
	SelectObject(hMdc, wheel1B);
    DeleteObject(wheel2B);
	
	

	

	return 1;
}



