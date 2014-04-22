#include "swarmee.h"

swarmee::swarmee(Point2D p, Point2D v, Point2D a, bool m, float m2, Point2D f, Point2D s, boundingBox bb, float w, float h)
	: particleModel(p, v, a, m, m2, f, s, w, h)
{
	b = bb;
	ip = false;
	updateMe = true;
}

void swarmee::setShape2Square() 
{
	shape[0].x = 0.0f;	shape[0].y = 1.0f;
	shape[1].x = 1.0f;	shape[1].y = 2.0f;
	shape[2].x = 2.0f;	shape[2].y = 1.0f;
	shape[3].x = 1.0f;	shape[3].y = 0.0f;
}

int swarmee::dispBufUpdate()
{
	for (int v = 0; v < 4; v++)
	{
		dispBuffObj[v].x = shape[v].x + getPosX();
		dispBuffObj[v].y = shape[v].y + getPosY();
	}

	return 1;
}

int swarmee::draw(GraphicsM * pGraphicsModule)
{
	dispBufUpdate();
	pGraphicsModule->drawPolygon(dispBuffObj, 4, true);

	return 1;
}

void swarmee::updateSwarmee(boundingBox bBox)
{
	b.initBox(getPosX(), getPosY(), 2, 2);
	float tblx, tbly, tbrx, tbry, ttlx, ttly, ttrx, ttry;

	tblx = bBox.getBlcX() - getPosX();
	tbly = bBox.getBlcY() - getPosY();

	if (tblx <= 20 && tbly <= 20)
	{
		state = CHASE;
	}
	else 
	{
		state = PATROL;
	}

	if (bBox.getTop() < getPosY())
	{
		setVelY(20);
		setVelY(-getVelY());
	}

	if (bBox.getTop() > getPosY())
	{
		setVelY(20);
		setVelY(+getVelY());
	}

	if (bBox.getTlcX() > getPosX())
	{
		setVelX(20);
		setVelX(+getVelX());
	}

	if (bBox.getTlcX() < getPosX())
	{
		setVelX(20);
		setVelX(-getVelX());
	}

	b.initBox(getPosX(), getPosY(), 2, 2);
}

void swarmee::stateManagement(boundingBox bBox, boundingBox * swBox)
{
	if (state == CHASE)
	{
		if (swBox->getLeft() < bBox.getLeft() && swBox->getRight() > bBox.getRight())
		{

		}
		else if (swBox->getLeft() < bBox.getLeft())
		{
			int t;
			t = swBox->getX() + 5;
			swBox->initBox(t, swBox->getY(), swBox->getWidth(), swBox->getHeight());
		}
		else if (swBox->getRight() < bBox.getRight())
		{
			int t;
			t = swBox->getX() - 5;
			swBox->initBox(t, swBox->getY(), swBox->getWidth(), swBox->getHeight());
		}
		else if (swBox->getY() < bBox.getY())
		{
			int t;
			t = swBox->getX() + 5;
			swBox->initBox(t, swBox->getY(), swBox->getWidth(), swBox->getHeight());
		}
		else if (swBox->getY() > bBox.getY())
		{
			int t;
			t = swBox->getX() - 5;
			swBox->initBox(t, swBox->getY(), swBox->getWidth(), swBox->getHeight());
		}
	}
}

void swarmee::swarmeeAway(boundingBox swBox)
{
	b.initBox(getPosX(), getPosY(), 2, 2);

	if (getPosX() >= swBox.getRight())
	{
		setVelX(-getVelX());
	}
	
	if (getPosX() <= swBox.getLeft())
	{
		setVelX(-getVelX());
	}

	if (getPosY() <= swBox.getTop())
	{
		setVelY(-getVelX());
	}

	if (getPosY() >= swBox.getBottom())
	{
		setVelY(-getVelX());
	}	
}
