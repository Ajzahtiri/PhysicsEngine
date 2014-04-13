#include "worldData.h"
#include "particleModel.h"
#include "snowball.h"
#include "definitions.h"
#include <time.h>

WorldData::WorldData()
{
	//do some things
	srand(time(NULL));

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
	Point2D bp;
	bp.x = 400;
	bp.y = VIEWPORT_DOWN - 100;
	veh = new buggy(bp);

	//setup slopes
	leftSlopeLeft.x = 100;
	leftSlopeLeft.y = VIEWPORT_DOWN - 20;
	leftSlopeRight.x = 180;
	leftSlopeRight.y = VIEWPORT_DOWN - 20;
	leftSlopeTop.x = 180;
	leftSlopeTop.y = VIEWPORT_DOWN - 120;

	rightSlopeLeft.x = 260;
	rightSlopeLeft.y = VIEWPORT_DOWN - 80;
	rightSlopeRight.x = 290;
	rightSlopeRight.y = VIEWPORT_DOWN - 80;
	rightSlopeTop.x = 260;
	rightSlopeTop.y = VIEWPORT_DOWN - 120;

	castleSlopeLeft.x = 460;
	castleSlopeLeft.y = VIEWPORT_DOWN - 80;
	castleSlopeRight.x = 530;
	castleSlopeRight.y = VIEWPORT_DOWN - 80;
	castleSlopeTop.x = 530;
	castleSlopeTop.y = VIEWPORT_DOWN - 180;

	//setup missile/motes
	fired = false;

	Point2D mP;
	mP.x = bp.x + 14;
	mP.y = bp.y - 33;

	Point2D mV;
	mV.x = 0;
	mV.y = -200;

	mB.initBox(mP.x, mP.y, 12, 33);
	mi = new missile(mP, mV, emptyAcc, 0.1f, gravity, mB);
	mi->initMissile();
}

int WorldData::worldDataModuleInit()
{	
	tickBefore = GetTickCount();

	set = false;

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
				s->updateBox();
				s->updateAcc();
				s->moveConstAcc(difference);
				
				if (s->getBb().checkFlats() 
					|| s->getBb().checkSlopes(leftSlopeTop, leftSlopeLeft, leftSlopeRight)
					|| s->getBb().checkSlopes(rightSlopeTop, rightSlopeLeft, rightSlopeRight)
					|| s->getBb().checkSlopes(castleSlopeTop, castleSlopeLeft, castleSlopeRight))
				{
					s->resetParticle();
					s->setAccX(0);
					s->setAccY(0);
					s->setVelY(1);
				}
			}
			s++;
		}
	}	

	//update buggy

	
	//update missile
	if (mi->getFired() == true)
	{
		mi->updateMissile(difference);
		mi->checkCollision(leftSlopeLeft, leftSlopeRight, leftSlopeTop, rightSlopeLeft, rightSlopeRight,
			rightSlopeTop, castleSlopeLeft, castleSlopeRight, castleSlopeTop);
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
		if (veh->getBuggyX() > VIEWPORT_LEFT)
		{
			veh->moveLeft();

			if (mi->getFired() == false)
			{
				mi->moveMissileLeft();
			}
		}
		break;		
	case D:
		if (veh->getBuggyX() + veh->getBb().getWidth() < VIEWPORT_RIGHT)
		{
			veh->moveRight();

			if (mi->getFired() == false)
			{
				mi->moveMissileRight();
			}
		}		
		break;
	case S_DOWN:
		if (isFiring == false)
		{
			isFiring = true;
			
			if (mi->getFired() == true && mi->getBoomed() == true)
			{
				mi->setMissileShape(veh->getBuggyX() + 14, veh->getBuggyY() - 33);
			}
			else
			{
				mi->setFired(true);
			}
		}
		break;
	case S_UP:
		isFiring = false;
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

	mi->drawMissile(pGraphicsModule);

	veh->initBuggy(pGraphicsModule);
	pGraphicsModule->drawText();

	return 1;
}

