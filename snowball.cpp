#include "snowball.h"

snowball::snowball(Point2D pos, Point2D vel, Point2D acc, bool mov, float mas, Point2D f)
	: particleModel(pos, vel, acc, mov, mas, f)
{
	setShape2Square(mas);
}

snowball::~snowball()
{

}

void snowball::setShape2Square(float m)
{
    shape[0].x = 0.0F;	shape[0].y = 0.0F;
    shape[1].x = m + 1;	shape[1].y = 0.0F;
    shape[2].x = m + 1;	shape[2].y = m + 1;
    shape[3].x = 0.0F;	shape[3].y = m + 1;
}

void snowball::checkSnow()
{
	Point2D p = getPos();

	if(p.y + 5 >= VIEWPORT_DOWN - 40)
	{		
		resetParticle();
		setAccX(0);
		setAccY(0);
		setVelY(1);
	}

	if(p.x >= VIEWPORT_RIGHT)
	{

	}

	if(p.x + 5 <= VIEWPORT_LEFT)
	{

	}
	
	if(p.y <= VIEWPORT_UP )
	{

	}
}

int snowball::update(keyEvent ke, GraphicsM * pGraphicsModule, float time)
{
	moveConstAcc(time);   
	updateAcc();

	return 1;
}

int snowball::draw(GraphicsM * gm)
{
	dispBuffUpdate();
	gm->drawPolygon(dispBuffObj, 4, true);

	return 1;
}

int snowball::dispBuffUpdate()
{
	for (int vert = 0; vert < 4; vert++)
	{
		dispBuffObj[vert].x = shape[vert].x + position.x;
		dispBuffObj[vert].y = shape[vert].y + position.y;
	}
	return 1;
}

