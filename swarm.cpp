#include "swarm.h"

swarm::swarm(Point2D p, Point2D v, Point2D a, bool m, float m2, Point2D f, Point2D sp, float ww, float hh)
	: particleModel(p, v, a, m, m2, f, sp, ww, hh)
{
	for (int i = 0; i < 30; i++)
	{
		Point2D swP;
		Point2D swV;
		Point2D swF;
		boundingBox swB;
		intersect = false;

		swP.x = rand() % 100 + 25;
		swP.y = rand() % 100 + 25;

		swV.x = rand() % 10 + 5;
		swV.y = rand() % 10 + 5;

		swF.x = 0;
		swF.y = 0;

		swB.initBox(swP.x, swP.y, 2, 2);

		swarmee * swee = new swarmee(swP, swV, swV, false, 1, swF, swP, swB, 2, 2);
		swarmees.push_back(*swee);
	}
}

void swarm::swarmAway()
{
	std::list<swarmee>::iterator si = swarmees.begin();
	while(si != swarmees.end())
	{
		if(si->getUpdateMe())
		{
			if (si->getPosX() >= b->getRight())
			{
				si->setPosX(si->getPosX() - 1);
				si->setVelX(-si->getVelX());
			}

			if (si->getPosX() <= b->getLeft())
			{
				si->setPosX(si->getPosX() + 1);
				si->setVelX(-si->getVelX());
			}

			if (si->getPosY() >= b->getBottom())
			{
				si->setPosY(si->getPosY() - 1);
				si->setVelY(-si->getVelY());
			}

			if (si->getPosY() <= b->getTop())
			{
				si->setPosY(si->getPosY() + 1);
				si->setVelY(-si->getVelY());
			}

			si->updateAcc();
			si->moveConstAcc(0.2);
			si->getBb().initBox(si->getPosX(), si->getPosY(), 2, 2);
		}
		si++;
	}
}

void swarm::update(boundingBox bBox)
{
	b->checkWallCollisions();
	chaseBuggy(bBox);
	b->initBox(getPosX(), getPosY(), b->getWidth(), b->getHeight());
	moveConstAcc(0.2);
	swarmAway();
}

void swarm::updateSwarmees(GraphicsM * pGraphicsModule)
{
	std::list<swarmee>::iterator sw = swarmees.begin();
	while (sw != swarmees.end())
	{
		if (sw->getUpdateMe())
		{
			sw->setShape2Square();
			sw->draw(pGraphicsModule);
		}
		sw++;
	}	
}

void swarm::chaseBuggy(boundingBox bBox)
{
	boundingBox * tb = new boundingBox();
	tb->initBox(b->getX() - 250, b->getY() - 250, b->getWidth() + 350, b->getHeight() + 350);

	if (tb->checkIntersect(bBox))
	{
		intersect = true;

		if (b->getLeft() < bBox.getLeft() && b->getRight() > bBox.getRight() && b->getY() < bBox.getY())
		{
			setVelY(2);
		}

		if (b->getLeft() < bBox.getLeft() && b->getRight() > bBox.getRight() && b->getY() > bBox.getY())
		{
			setVelY(-2);
		}

		if (b->getTop() < bBox.getTop() && b->getBottom() > bBox.getBottom() && b->getX() > bBox.getX())
		{
			setVelX(-2);
		}

		if (b->getTop() < bBox.getTop() && b->getBottom() > bBox.getBottom() && b->getRight() < bBox.getX())
		{
			setVelX(2);
		}
	}
	else
	{
		intersect = false;
	}

	if (!intersect)
	{
		if (getPosY() > VIEWPORT_UP + 40)
		{
			setVelY(-2);
		}
		else
		{
			setVelX(0);
		}
	}
}

bool swarm::collisionTank(boundingBox bBox)
{
	if (b->checkIntersect(bBox))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

