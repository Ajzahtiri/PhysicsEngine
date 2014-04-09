#include		"graphics.h"
#include		"definitions.h"

GraphicsM::GraphicsM()
	{
	/* TO DO: add relevant code */

	return;			
	}

/*
	Destructs graphics module

	Parameter list
		none
 */
GraphicsM::~GraphicsM()
	{
	/* TO DO: add relevant code */

	graphicsCleanUp();

	return;			
	}


/*
	Initialises the graphics module.

	Parameter list
		hWnd:			handle of window
 */
int GraphicsM::graphicsModuleInit(HWND hWnd)
	{
	/* TO DO: add relevant code */
	

	/* Set viewport */
	setViewport();

	/* Initialise back buffer */
	initMemDC(hWnd);

	return 1;
	}


/*
	Sets the viewport.

	Parameter list
		none.
 */
int GraphicsM::setViewport()
	{
	/* TO DO: add relevant code */
	
	/* Set viewport */
		viewport.left = 0; viewport.top = 0; viewport.right = VIEWPORT_RIGHT; viewport.bottom = VIEWPORT_DOWN;
	
	return 1;
	}

RECT GraphicsM::getViewport()
{
	return viewport;
}


/*
	Initialises the memory device context (i.e. back buffer for double buffering)

	Parameter list
		hWnd:			handle of window
 */
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


/*
 Releases graphics objects

 Parameter list
 	none
 */
void GraphicsM::graphicsCleanUp()
{
	/* TO DO: add relevant code */


	return;
}



/*----------------------------------------------------------------------------\
 *                                                                            |
 *					     		GRAPHICS RENDERING 	                   		  |
 *                                                                            |
 *----------------------------------------------------------------------------*/

	
/*
 Displays the back buffer.
		  
 Parameter list
	hWnd:			handle of window
 */
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



/*
  Draws a basic HUD.

  Parameter list
	 none
  */
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

