/*
 * File name:		winApp.cpp
 * Description:		Basic functions for simple Windows application
 *
 * Author: 			Claude C. Chibelushi
 * Date:			04/10/04
 *					Modified 02/10/05, by CCC: change from BMGVR to PPEG
 *					Modified 19/01/09 by CCC: porting to C++
 *					Modified 06/02/09, by CCC: addition of set-up and shut-down code for GDI+.
 */



#include		"winApp.h"  	/* include file for main-window initialisation and display */
#include		"simulation.h"  /* include file for simulation module */


/*
 Application entry point

 Parameter list
	hThisAppInstance:			handle to current instance of application
   hPreviousAppInstance: 		handle to previous instance of application
   lpszCmdArguments:			pointer to command line for application
   nWindowShowState: 			show-state of window
 */

int WINAPI WinMain(	HINSTANCE hThisAppInstance, HINSTANCE hPreviousAppInstance,
 							LPSTR lpszCmdArguments, int nWindowShowState)
 	{
   HWND			hWindowHandle;		/* window handle */
   WNDCLASSEX	windowClass;		/* window-class structure */
   MSG			message;			/* message structure */

   /*
    Start up GDI+
	*/
   GdiplusStartupInput	gdiplusStartupInput;
   ULONG_PTR			gdiplusToken;

   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

   /* 
	Create and display application window
    */
   /* Define main-window class */
   fnDefineWindowClass(&windowClass, hThisAppInstance);

   /*	Register main-window class */
   if ( !RegisterClassEx(&windowClass) )
   	return 0;

   /*	Create main window */
	hWindowHandle = fnCreateWindow(hThisAppInstance);

   /*	Display main window */
   fnDisplayWindow(hWindowHandle, nWindowShowState);

	/* 
	 Create simulation object and execute simulation code
	 */
	Simulation sim;
	sim.simMain(hWindowHandle, &message);	/* Execute simulation code */

   /*
    Shut-down GDI+
	*/
   GdiplusShutdown(gdiplusToken);

   return message.wParam;

   }


/*
 Window procedure: function to which Windows sends messages

 Parameter list
 	hWnd:			handle of window
	message:		message identifier
 	wParam:			first message parameter
	lParam:			second message parameter
 */

 LRESULT CALLBACK fnWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
 	{
   static HDC         	hdc ;
   PAINTSTRUCT 			ps ;


   /* message processing */
   switch(message)
   	{
      case WM_PAINT:  /* the following effectively removes WM_PAINT message from queue */
      		hdc = BeginPaint (hWnd, &ps) ;

			EndPaint (hWnd, &ps) ;
			break;

		case WM_DESTROY:				/* program termination */
			PostQuitMessage(0);
			break;

      default:
      	/* messages not specified above are processed by Windows */
      	return DefWindowProc(hWnd, message, wParam, lParam);

      }

   return 0;
   }



/*----------------------------------------------------------------------------|
 |  		Functions for main-window initialisation and display              |
 ----------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
	Function to define window class
\*-------------------------------------------------------------------------*/

void fnDefineWindowClass(WNDCLASSEX * windowClass, HINSTANCE hThisAppInstance)
 	{

   windowClass->cbSize = sizeof(WNDCLASSEX); 				/* size in bytes of window-class structure */

   windowClass->hInstance = hThisAppInstance;				/* handle to this application instance */
   windowClass->lpszClassName = szWinName;					/* window class name */
   windowClass->lpfnWndProc = fnWindowProcedure;			/* window procedure */
   windowClass->style = CS_HREDRAW | CS_VREDRAW /* 0 */;	/* repaint window after size changed */

   windowClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);	/* use standard icon */
   windowClass->hIconSm = LoadIcon(NULL, IDI_WINLOGO);		/* use Windows logo as small icon */
   windowClass->hCursor = LoadCursor(NULL, IDC_ARROW);		/* use arrow cursor */

   windowClass->lpszMenuName = NULL;						/* no menu */
   windowClass->cbClsExtra = 0;								/* allocate 0 bytes after window-class structure */
   windowClass->cbWndExtra = 0;								/* allocate 0 bytes after window instance */

   windowClass->hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	/* use white window background */

   }

/*-------------------------------------------------------------------------*\
	Function to create a window
\*-------------------------------------------------------------------------*/

HWND fnCreateWindow(HINSTANCE hThisAppInstance)
	{

   return CreateWindow
   						(
                     szWinName,						/* window class name */
                     "PPAIEG Tutorials",				/* window title */
                     WS_POPUP | WS_VISIBLE,			/* window style: normal */
                     0,								/* x coordinate (top left corner) */
                     0,								/* Y coordinate (top left corner) */
                     GetSystemMetrics(SM_CXSCREEN),	/* window width */
                     GetSystemMetrics(SM_CYSCREEN),	/* window height */
                     HWND_DESKTOP /* NULL */ ,		/* no parent window */
                     NULL,                      	/* no menu or child-window */
                     hThisAppInstance,				/* handle of this instance of application */
                     NULL							/* no additional arguments */
                     );
   }

/*-------------------------------------------------------------------------*\
	Function to display a window
\*-------------------------------------------------------------------------*/

void fnDisplayWindow(HWND hWindowHandle, int nWindowMode)
	{
	ShowWindow(hWindowHandle, nWindowMode);	/* set window's show state, and display window */
	UpdateWindow(hWindowHandle);              /* update client area of window */
	}







