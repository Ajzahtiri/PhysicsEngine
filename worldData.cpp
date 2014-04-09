#include "worldData.h"
#include "particleModel.h"
#include "snowball.h"
#include "definitions.h"

WorldData::WorldData()
{
	gravity.x = 0;
	gravity.y = 9;
	isSnowing = true;

	Point2D emptyAcc;
	emptyAcc.x = 0;
	emptyAcc.y = 0;

	//setup snowfall
	for (int i = 0; i < 1000; i++)
	{
		Point2D sp;
		int x = rand() % (VIEWPORT_RIGHT * 2) + (0 - (VIEWPORT_RIGHT / 2));
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
	tp.x = 500;
	tp.y = 450;
	t = new buggy(tp);

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
				s->checkSnow();
			}
			s++;
		}
	}	

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
		if (t->getBuggyX() > VIEWPORT_LEFT)
		{
			t->moveLeft();
		}
		break;
	case D:
		if (t->getBuggyX() < VIEWPORT_RIGHT)
		{
			t->moveRight();
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

	t->initBuggy(pGraphicsModule);
	pGraphicsModule->drawText();

	return 1;
}

