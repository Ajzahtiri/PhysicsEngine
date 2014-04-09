/*
 * File name:	worldData.cpp
 * Description:	World data module.
 *
 * Author: 			Claude C. Chibelushi
 * Date:			04/10/04
 *					Modified 27/09/06, by CCC: addition of function for setting object shape
 *					Modified 19/01/09 by CCC: porting to C++
 *							 06/02/09 by CCC: additional functionality required  
 *                           for illustrative examples of GDI drawing functionality.
 *
 */
 

#include "worldData.h"
#include "particleModel.h"
#include "snowball.h"
#include "definitions.h"

GraphicsM gm;

WorldData::WorldData()
{
	gravity.x = 0;
	gravity.y = 9;
	isSnowing = true;

	Point2D emptyAcc;
	emptyAcc.x = 0;
	emptyAcc.y = 0;

	for (int i = 0; i < 1000; i++)
	{
		Point2D sp;
		int x = rand() % ((VIEWPORT_RIGHT * 2) + 1);
		int y = rand() % (VIEWPORT_DOWN + 1);
		sp.x = x - VIEWPORT_RIGHT / 2;
		sp.y = y - VIEWPORT_DOWN;

		float mass = rand() % 4 + 1;
		mass /= 2;
		Point2D vel;
		vel.x = 0;
		vel.y = 1;

		s = new snowball(sp, vel, emptyAcc, true, mass, gravity); 
		snowfall.push_back(*s);
	}
}

int WorldData::worldDataModuleInit()
{	
	tickBefore = GetTickCount();
	std::list<snowball>::iterator s = snowfall.begin();

	while (s != snowfall.end())
	{
		s->setShape2Square();
		s++;
	}

	return 1;	
}

WorldData::~WorldData()
{
	worldCleanUp();

	return;			
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
		
int WorldData::update(keyEvent kEvent, GraphicsM * pGraphicsModule, float time)
{
	double tickNow = GetTickCount();
	double difference = (double) (tickNow - tickBefore);
	difference /= 1000;
	tickBefore = tickNow;

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
	return 1;
}

