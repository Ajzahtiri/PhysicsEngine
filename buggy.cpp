#include "buggy.h"

buggy::buggy(Point2D p)
{
	position = p;
}

void buggy::initBuggy(GraphicsM * pGraphicModule)
{
	pGraphicModule->drawBuggy(position);
}

void buggy::moveLeft()
{
	position.x -= 1;
}

void buggy::moveRight()
{
	position.x += 1;
}
