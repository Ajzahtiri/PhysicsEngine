#include "particleModel.h"
#include "definitions.h"
#include "appearance.h"

particleModel::particleModel(Point2D pos, Point2D vel, Point2D acc, bool mov, float mas, Point2D f)
{
	position = pos;
	velocity = vel;
	acceleration = acc;
	isMoving = mov;
	mass = mas;
	totalForce = f;
	startPos = pos;
}

particleModel::~particleModel()
{

}

int particleModel::worldDataModuleInit()
{
	return 1;
}

void particleModel::setPos(float x, float y)
{
	position.x = x;
	position.y = y;
}

Point2D particleModel::getPos()
{
	return position;
}

void particleModel::moveConstAcc(double t)
{
	position.x += velocity.x * t + 0.5 * acceleration.x * t;
	position.y += velocity.y * t + 0.5 * acceleration.y * t;

	velocity.x += acceleration.x * t;
	velocity.y += acceleration.y * t;
}

void particleModel::updateAcc()
{
	acceleration.x = totalForce.x / mass;
	acceleration.y = totalForce.y / mass;

	if (totalForce.x > 0)
	{
		totalForce.x -= 1;
	}

	if (totalForce.x < 0)
	{
		totalForce.x += 1;
	}
}

void particleModel::checkWallCollisions(boundingBox * b)
{
	Point2D pos = getPos();	

	if (pos.x <= VIEWPORT_LEFT)
	{
		position.x = VIEWPORT_LEFT;
		setVelX(-velocity.x);
	}

	if (pos.y <= VIEWPORT_UP)
	{
		position.y = VIEWPORT_UP;
		setVelY(-velocity.y);
	}

	if (pos.x + b->getWidth() >= VIEWPORT_RIGHT)
	{
		position.x = VIEWPORT_RIGHT - b->getWidth();
		setVelX(-velocity.x);
	}

	if (pos.y + b->getHeight() >= VIEWPORT_DOWN)
	{
		position.y = VIEWPORT_DOWN - b->getHeight();
		setVelY(-velocity.y);
	}	
}

/*
void particleModel::checkCollisions(boundingBox * b)
{
	for (int i = 0; i < 4; i++)
	{
		//checks right wall
		if ((getPos().x + 10) > gm->getViewport().right)
		{
			setPos(640, getPos().y);
			float xx = getVel().x;
			xx *= -1;
			setVel(xx, getVel().y);
		}

		//checks bottom		
		if ((getPos().y + 10) > gm->getViewport().bottom)
		{
			setPos(getPos().x, 480);
			float yy = getVel().y;
			yy *= -1;
			setVel(getVel().x, yy);
		}

		//check left wall
		if (getPos().x < gm->getViewport().left)
		{
			setPos(10, getPos().y);
			float xx = getVel().x;
			xx *= -1;
			setVel(xx, getVel().y);
		}

		//check top wall
		if (getPos().y < gm->getViewport().top)
		{
			setPos(getPos().x, 10);
			float yy = getVel().y;
			yy *= -1;
			setVel(getVel().x, yy);
		}

		//return true;
	}
	
}

*/
