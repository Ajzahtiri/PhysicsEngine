#include "snowball.h"

snowball::snowball(Point2D pos, Point2D vel, Point2D acc, bool mov, float mas, Point2D f)
	: particleModel(pos, vel, acc, mov, mas, f, pos)
{
	setShape2Square(mas);
}

void snowball::setShape2Square(float m)
{
    shape[0].x = 0.0F;	shape[0].y = 0.0F;
    shape[1].x = m + 1;	shape[1].y = 0.0F;
    shape[2].x = m + 1;	shape[2].y = m + 1;
    shape[3].x = 0.0F;	shape[3].y = m + 1;
}

void snowball::checkSnow(Point2D sl, Point2D sr, Point2D st)
{
	Point2D p = getPos();

	if((p.y + mass >= VIEWPORT_DOWN - 20 && (p.x + mass >= VIEWPORT_LEFT && p.x <= 100)) 
		|| (p.y + mass >= VIEWPORT_DOWN - 80 && (p.x + mass >= 290 && p.x <= 460))
		|| (p.y + mass >= VIEWPORT_DOWN - 120 && (p.x + mass >= 180 && p.x <= 260))
		|| (p.y + mass >= VIEWPORT_DOWN - 180 && (p.x + mass >= 530 && p.x <= VIEWPORT_RIGHT))
		|| ((p.y + mass >= VIEWPORT_DOWN - 350 && p.y <= VIEWPORT_DOWN - 345) && (p.x + mass >= 0 && p.x <= 150))
		|| p.y >= VIEWPORT_DOWN
		|| b.checkSlopeCollision(sl, sr, st))
	{		
		resetParticle();
		setAccX(0);
		setAccY(0);
		setVelY(1);
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

