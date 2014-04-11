#include "particleModel.h"
#include "definitions.h"
#include "appearance.h"

particleModel::particleModel(Point2D pos, Point2D vel, Point2D acc, bool mov, float mas, Point2D f, Point2D sp, float ww, float hh)
{
	position = pos;
	velocity = vel;
	acceleration = acc;
	isMoving = mov;
	mass = mas;
	totalForce = f;
	startPos = sp;
	w = ww;
	h = hh;

	b.initBox(pos.x, pos.y, w, h);
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

void particleModel::updateBox()
{
	b.initBox(position.x, position.y, w, h);
}