/*
 * File name:		simulation.h
 * Description:		Header file for simulation.cpp
 *
 * Author: 			Claude C. Chibelushi
 * Date:			04/10/04
 *					Modified 19/01/09 by CCC: porting to C++
 *					Modified 06/02/09 by CCC: implementation of double buffering
 *							(functions changed: simInit) and of changes required for 
 *							illustrative examples of drawing functionality 
 *							(e.g. worldDataModuleInit()).
 *					Modified 22/01/10 by CCC: flow-control functionality integrated into Simulation class
 *
 */
 

#ifndef _SIM_H
#define _SIM_H

#include		<windows.h>
#include		"worldData.h"		/* include file for world data module */
#include		"graphics.h"		/* include file for graphics module */
#include		"input.h"			/* include file for user input module */

class Simulation
	{
	public:

		// Constructor and destructor
		Simulation();
		~Simulation(){};

		// Simulation entry point
		int simMain(HWND hWnd, MSG * msg);

	private:

		// Member data
		WorldData       world;              // world data module
		GraphicsM       graphics;           // graphics module
		Input			kbd;				// input module

		float			timeSpeed;
		float			timeNow;
		float			timePrev;
		float			timeSinceLastFrame;

		// Member functions
		int simInit(HWND hWnd);				// Simulation initialisation
		int simCleanUp();					// Simulation clean-up prior to shut-down
		int simLoop(HWND hWnd, MSG * msg);	// Simulation loop
		int simProc(HWND hWnd);				// Simulation processing (i.e. input event reading, action, output) 
		int simControlLogic(HWND hWnd, keyEvent event, float timeSinceLastFrame);			// Simulation control logic
		int simDisplayFrame(HWND hWnd);			// Animation-frame display

		//void gameLoopDelay(float floatStartTime);

	};


#endif /* _SIM_H */

