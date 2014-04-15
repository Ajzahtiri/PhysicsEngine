#pragma once

#include "dataTypes.h"
#include "graphics.h"
#include "boundingBox.h"

class buggy 
{
private:
	Point2D position;
	boundingBox b;

public:
	buggy(Point2D p);
	~buggy(){};
	
	void	setPos(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	void	initBuggy(GraphicsM * pGraphicsModule);
	boundingBox getBb()
	{
		return b;
	}
	void updateBox();

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