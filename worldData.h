#ifndef _WORLDDATA_H
#define _WORLDDATA_H

#include	<windows.h>
#include	"dataTypes.h"		/* include file for custom data types */
#include	"graphics.h"		/* include file for graphics module */
#include	"snowball.h"
#include	"buggy.h"
#include	<list>
#include	"input.h"			/* include file for user input module */


class WorldData
{
private:
	//world
	Point2D gravity;

	//time
	double tickBefore;

	//snow
	std::list<snowball> snowfall;
	bool isSnowing;
	snowball * s;

	//buggy
	buggy * veh;

	//slopes
	Point2D leftSlopeOneLeft, leftSlopeOneTop, leftSlopeOneRight;
	Point2D rightSlopeTwoLeft, rightSlopeTwoTop, rightSlopeTwoRight;

	
	// Dynamics parameters (for physics simulation) 
	Point2D		shape[4];			// array to store a polygonal shape consisting of four vertices (e.g. a square) 
	Point2D		dispBuffObj[4];		// array to store display coordinates of a polygonal object
	Point2D 	pos;				// position of particle used as physics model of game object

public:
	WorldData();
	~WorldData(){};
	int		worldDataModuleInit();						
	void	worldCleanUp();							
	int		update(keyEvent kEvent, GraphicsM * pGraphicsModule, float time);					// Update the world's dynamics state
	int		draw(GraphicsM * pGraphicsModule);	

	//snow
	void	startSnow();
	void	stopSnow();
	void	setSnowing(bool b)
	{
		isSnowing = true;
	}
	bool	getSnowing()
	{
		return isSnowing;
	}

	//wind
	void	windLeft();
	void	windRight();
};

#endif /* _WORLDDATA_H */
