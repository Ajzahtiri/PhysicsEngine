#include "worldData.h"
#include "particleModel.h"
#include "snowball.h"
#include "definitions.h"

WorldData::WorldData()
{
	//setup some forces
	gravity.x = 0;
	gravity.y = 5;

	Point2D emptyForce;
	emptyForce.x = 0;
	emptyForce.y = 0;

	Point2D emptyAcc;
	emptyAcc.x = 0;
	emptyAcc.y = 0;

	Point2D emptyVel;
	emptyVel.x = 0;
	emptyVel.y = 0;

	//setup snowfall	
	isSnowing = true;
	for (int i = 0; i < 1000; i++)
	{
		Point2D sp;
		int x = rand() % 2600 - 1300;
		int y = rand() % VIEWPORT_DOWN + 1;
		sp.x = x;
		sp.y = y - VIEWPORT_DOWN - 10;

		float mass = rand() % 4 + 1;
		mass /= 2;
		Point2D vel;
		vel.x = 0;
		vel.y = 1;

		s = new snowball(sp, vel, emptyAcc, true, mass, gravity); 
		snowfall.push_back(*s);
	}

	//setup buggy
	Point2D tp;
	tp.x = 400;
	tp.y = VIEWPORT_DOWN - 80;
	veh = new buggy(tp);

	//setup slopes
	leftSlopeOneLeft.x = 100;
	leftSlopeOneLeft.y = VIEWPORT_DOWN - 20;
	leftSlopeOneRight.x = 180;
	leftSlopeOneRight.y = VIEWPORT_DOWN - 20;
	leftSlopeOneTop.x = 180;
	leftSlopeOneTop.y = VIEWPORT_DOWN - 120;

}

int WorldData::worldDataModuleInit()
{	
	tickBefore = GetTickCount();

	return 1;
}

void WorldData::worldCleanUp()
{
	return;			
}

void WorldData::startSnow()
{
	isSnowing = true;
	std::list<snowball>::iterator s = snowfall.begin();
	while (s != snowfall.end())
	{
		s->setAccX(0);
		s->setAccY(0);
		s->setVel(0, 1);
		s->setMoving(true);
		s++;
	}
}

void WorldData::stopSnow()
{
	isSnowing = false;
	std::list<snowball>::iterator s = snowfall.begin();
	while (s != snowfall.end())
	{
		s->resetParticle();
		s->setMoving(false);
		s++;
	}
}

void WorldData::windLeft()
{
	std::list<snowball>::iterator s = snowfall.begin();
	while(s != snowfall.end())
	{
		if (s->getMoving() == true)
		{
			s->setForceX(-25);
		}
		s++;
	}
}

void WorldData::windRight()
{
	std::list<snowball>::iterator s = snowfall.begin();
	while(s != snowfall.end())
	{
		if (s->getMoving() == true)
		{
			s->setForceX(25);
		}
		s++;
	}
}

int WorldData::update(keyEvent kEvent, GraphicsM * pGraphicsModule, float time)
{
	double tickNow = GetTickCount();
	double difference = (double) (tickNow - tickBefore);
	difference /= 1000;
	tickBefore = tickNow;

	//update snowballs
	if (isSnowing == true)
	{
		std::list<snowball>::iterator s = snowfall.begin();
		while (s != snowfall.end())
		{
			if (s->getMoving())
			{
				s->updateAcc();
				s->moveConstAcc(difference);
				s->checkSnow(leftSlopeOneLeft, leftSlopeOneRight, leftSlopeOneTop);
			}
			s++;
		}
	}	

	//update buggy


	//check keyboard for user input
	switch(kEvent)
	{
	case Z:
		startSnow();
		break;
	case X:
		stopSnow();
		break;
	case C:
		windLeft();
		break;
	case V:
		windRight();
		break;
	case A:
		if (veh->getBuggyX() > VIEWPORT_LEFT)
		{
			veh->moveLeft();
		}
		break;
	case D:
		if (veh->getBuggyY() < VIEWPORT_RIGHT)
		{
			veh->moveRight();
		}
		break;
	default:
		break;
	}
	return 1;
}

int WorldData::draw(GraphicsM * pGraphicsModule)
{		
	std::list<snowball>::iterator s = snowfall.begin();
	while (s != snowfall.end())
	{
		s->draw(pGraphicsModule);
		s++;
	}

	veh->initBuggy(pGraphicsModule);
	pGraphicsModule->drawText();

	return 1;
}

