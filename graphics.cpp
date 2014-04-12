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
	HGDIOBJ		hpb;				// handle for previous brush
	HBRUSH		hBlueBrush;			// handle for blue custom brush
	HBRUSH		hWhiteBrush;		// handle for white custom brush
	HBRUSH		hBunkerBrush;
	POINT		groundShape[10];	
	POINT		bunkerShape[4];

	// sky (blue colour)
	hBlueBrush = CreateSolidBrush(RGB(0,192,255));	// blue brush
	hpb = SelectObject(hMdc, hBlueBrush);
	Rectangle(hMdc, viewport.left, viewport.top, viewport.right, viewport.bottom);
	SelectObject(hMdc, hpb);
    DeleteObject(hBlueBrush);

	// ground (white colour)
	hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	hpb = SelectObject(hMdc, hWhiteBrush);
	groundShape[0].x = 0;
	groundShape[0].y = VIEWPORT_DOWN - 20;
	groundShape[1].x = 100;
	groundShape[1].y = VIEWPORT_DOWN - 20;
	groundShape[2].x = 180;
	groundShape[2].y = VIEWPORT_DOWN - 120;
	groundShape[3].x = 260;
	groundShape[3].y = VIEWPORT_DOWN - 120;
	groundShape[4].x = 290;
	groundShape[4].y = VIEWPORT_DOWN - 80;
	groundShape[5].x = 460;
	groundShape[5].y = VIEWPORT_DOWN - 80;
	groundShape[6].x = 530;
	groundShape[6].y = VIEWPORT_DOWN - 180;
	groundShape[7].x = VIEWPORT_RIGHT;
	groundShape[7].y = VIEWPORT_DOWN - 180;
	groundShape[8].x = VIEWPORT_RIGHT;
	groundShape[8].y = VIEWPORT_DOWN;
	groundShape[9].x = VIEWPORT_LEFT;
	groundShape[9].y = VIEWPORT_DOWN;
	Polygon(hMdc, groundShape, 10);	
    DeleteObject(hWhiteBrush);

	hpb = SelectObject(hMdc, hWhiteBrush);
	bunkerShape[0].x = 0;
	bunkerShape[0].y = VIEWPORT_DOWN - 350;
	bunkerShape[1].x = 150;
	bunkerShape[1].y = VIEWPORT_DOWN - 350;
	bunkerShape[2].x = 150;
	bunkerShape[2].y = VIEWPORT_DOWN - 345;
	bunkerShape[3].x = 0;
	bunkerShape[3].y = VIEWPORT_DOWN - 345;
	Polygon(hMdc, bunkerShape, 4);
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

	DrawText(hMdc, "A - Buggy Left | S - Buggy Shoot/Reload | D - Buggy Right", -1, &tr1, DT_SINGLELINE | DT_NOCLIP);
	DrawText(hMdc, "Z - Start Snow | X - Stop Snow | C - Left Wind | V - Right Wind", -1, &tr2, DT_SINGLELINE | DT_NOCLIP);

	return 1;
}

int GraphicsM::drawBuggy(Point2D bp)
{
	HGDIOBJ		hpb;	
	
	HBRUSH		bodyB;
	HBRUSH		wheel1B;
	HBRUSH		wheel2B;

	// left - top - right - bottom
	bodyB = CreateSolidBrush(RGB(255, 204, 204));	
	hpb = SelectObject(hMdc, bodyB);
	Rectangle(hMdc, bp.x + 2, bp.y, bp.x + 38, bp.y + 18);
	SelectObject(hMdc, hpb);
    DeleteObject(bodyB);

	wheel1B = CreateSolidBrush(RGB(0, 0, 0));
	hpb = SelectObject(hMdc, wheel1B);
	Rectangle(hMdc, bp.x, bp.y + 12, bp.x + 8, bp.y + 20);
	SelectObject(hMdc, hpb);
    DeleteObject(wheel1B);

	wheel2B = CreateSolidBrush(RGB(0, 0, 0));
	hpb = SelectObject(hMdc, wheel1B);
	Rectangle(hMdc, bp.x + 32, bp.y + 12, bp.x + 40, bp.y + 20);
	SelectObject(hMdc, wheel1B);
    DeleteObject(wheel2B);

	return 1;
}