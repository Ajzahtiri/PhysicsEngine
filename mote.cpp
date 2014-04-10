#include "mote.h"

mote::mote(Point2D p, Point2D v, Point2D a, bool m, float m2, Point2D f, Point2D sp)
	: particleModel(p, v, a, m, m2, f, sp)
{

}

void mote::setShape2Square()
{
	shape[0].x = 0.0f;	shape[0].y = 0.0f;
	shape[1].x = 2.0f;	shape[1].y = 0.0f;
	shape[2].x = 2.0f;	shape[2].y = 2.0f;
	shape[3].x = 0.0f;	shape[3].y = 2.0f;
}

int mote::dispBufUpdate()
{
	for (int v = 0; v < 4; v++)
	{
		dispBuffObj[v].x = shape[v].x + getPosX();
		dispBuffObj[v].y = shape[v].y + getPosY();
	}
	return 1;
}

int mote::draw(GraphicsM * pGraphicsModule)
{
	dispBufUpdate();
	pGraphicsModule->drawPolygon(dispBuffObj, 4, true);
	return 1;
}
