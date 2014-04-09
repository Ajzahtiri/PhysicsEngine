#pragma once

#include "dataTypes.h"
#include "graphics.h"

class buggy 
{
private:
	Point2D position;

public:
	buggy(Point2D p);
	~buggy(){};
	
	void	initBuggy(GraphicsM * pGraphicsModule);

	void	moveLeft();
	void	moveRight();
	float	getBuggyX()
	{
		return position.x;
	}
	float	getBuggyY()
	{
		return position.y;
	}
};