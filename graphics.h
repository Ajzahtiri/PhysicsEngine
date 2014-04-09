#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include	<windows.h>
#include	"dataTypes.h"		/* include file for custom data types */
#include	<gdiplus.h>
using namespace Gdiplus;
//#pragma comment(lib, "gdiplus.lib")


class GraphicsM
	{

	protected:
		HDC hMdc;					/* handle for device context of back buffer */
		int	backBufWidth;			/* width of back buffer */
		int	backBufHeight;			/* height of back buffer */
		RECT viewport;				/* display viewport */

	public:
		GraphicsM();
		~GraphicsM(){};

		void	initMemDC(HWND hWnd);				// Initialise the memory device context (for double buffering)
		int		graphicsModuleInit(HWND hWnd);		// Initialise the graphics module
		void	graphicsCleanUp();					// Release graphics objects

		int		setViewport();						// Set the viewport
		RECT	getViewport();

		int		drawHUD();							// Draw a basic HUD
   		int		drawPolygon(Point2D polygon[], int vertexCount, bool closed);	// Draw a polygon
		int		displayBackBuffer(HWND hWnd);		// display backBuffer
		
		int		drawText();
		int		drawBuggy(Point2D tp);

	};


#endif /* _GRAPHICS_H */

