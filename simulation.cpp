/*
 * File name:		simulation.cpp
 * Description:		Simulation module
 *
 * Author: 			Claude C. Chibelushi
 * Date:			04/10/04
 *					Modified 02/10/05, by CCC: addition of calls to flow-control module
 *					Modified 19/01/09 by CCC: porting to C++
 *					Modified 06/02/09 by CCC: implementation of double buffering
 *							(functions changed: simInit) and of changes required for 
 *							illustrative examples of drawing functionality  
 *							(e.g. worldDataModuleInit()).
 *					Modified 22/01/10 by CCC: flow-control functionality integrated into Simulation class
 *
 */



#include		"simulation.h"		/* include file for simulation */



/* Convention on function return value: 0 means error; 1 means OK */


		/*----------------------------------------------------------------------------\
		 *                                                                            |
		 *                       INITIALISATION AND CLEAN UP           				  |
		 *                                                                            |
		 *----------------------------------------------------------------------------*/

Simulation::Simulation()
	{
		timeSpeed = 5;		//affects speed! lower = faster
	}

Simulation::~Simulation()
	{
	simCleanUp();

	return;			
	}

int Simulation::simMain(HWND hWnd, MSG * msg)
{
	if ( simInit(hWnd) )
	{
		simLoop(hWnd, msg);
		simCleanUp();

		return 1;
	}

	return 0;
}

int Simulation::simInit(HWND hWnd)
{
	/* TO DO: add relevant code */

	// Initialise:	world data module,
	//				graphics module,
	//				dynamics / behaviour module,
	//				flow control module
    if( world.worldDataModuleInit() && 
		graphics.graphicsModuleInit(hWnd) )	
	{
		ShowCursor(TRUE);  /* hide mouse cursor */
		return 1;
	}

	return 0;

}

int Simulation::simCleanUp()
{
	world.worldCleanUp();			// release world objects
	graphics.graphicsCleanUp();		// release graphics objects

	ShowCursor(TRUE);				// show mouse cursor

	return 1;
}

		/*----------------------------------------------------------------------------\
		 *                                                                            |
		 *									GAME LOOP			    				  |
		 *                                                                            |
		 *----------------------------------------------------------------------------*/

int Simulation::simLoop(HWND hWnd, MSG * msg)
{
	/* TO DO: add relevant code */

	/* Main loop  */

	ZeroMemory( msg, sizeof(*msg) );
	/* retrieve messages (for e.g. user interaction devices) */
	while( msg->message != WM_QUIT ) 	/* drop out of loop if "quit" message received */
	{
		/* Windows-part of loop body */
		if( PeekMessage( msg, NULL, 0U, 0U, PM_REMOVE ) )
      	/* Note: PeekMessage() does not wait for message to be placed in queue
         before returning (whereas GetMessage() does wait) */
		{
			TranslateMessage( msg ); 	/* translate keyboard message */
			DispatchMessage( msg );		/* dispatch message to window procedure (via Windows) */
		}

		/* Simulation-part of loop body */
		simProc(hWnd);
		
	}

   return 1;
}


int Simulation::simProc(HWND hWnd)
{
	keyEvent		event;
	event = kbd.checkUserInput(hWnd);
	timeNow = GetTickCount();
	timeSinceLastFrame = (timeNow - timePrev) / timeSpeed; 
	simControlLogic(hWnd, event, timeSinceLastFrame);
	timePrev = timeNow;
	

   return 1;
}


/*----------------------------------------------------------------------------\
 *                                                                            |
 *						CONTROL LOGIC BASED ON USER INPUT             		  |
 *                                                                            |
 *----------------------------------------------------------------------------*/

int Simulation::simControlLogic(HWND hWnd, keyEvent event, float timeSinceLastFrame)
{
	/* TO DO: add relevant code */

	if (event != QUIT)
	{
		world.update(event, &graphics, timeSinceLastFrame);					// update parameters of virtual world
		//gameLoopDelay(frameStartTime);
  		simDisplayFrame(hWnd);			// display frame
	}

   return 1;
}

int Simulation::simDisplayFrame(HWND hWnd)
{
	/* TO DO: add relevant code */


	/* Use double buffering:
			(i) first draw into bitmap used as back-buffer
			(ii) then display back buffer 
	  */
	// (i.1) display HUD
	graphics.drawHUD();			// draw HUD

	// (i.2) display world on HUD
	world.draw(&graphics);		// update display of virtual world

	// (ii) display back buffer 
	graphics.displayBackBuffer(hWnd);

	return 1;
}

/*
void Simulation::gameLoopDelay(float floatStartTime)
{
	presentFrameInterval = 40;

	frameProcessingTime = GetTickCount() - frameStartTime;

	if (frameProcessingTime < presentFrameInterval)
	{
		Sleep(presentFrameInterval - frameProcessingTime);
	}
}
*/