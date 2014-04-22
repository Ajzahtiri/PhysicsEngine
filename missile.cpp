#include "missile.h"

missile::missile(Point2D p, Point2D v, Point2D a, float m, Point2D f, boundingBox b)
{
	mP = p;
	mV = v;
	mA = a;
	mM = m;
	mF = f;
	mB = b;
}

void missile::initMissile()
{
	x = mP.x;
	y = mP.y;

	for (int i = 0; i < 24; i++)
	{
		Point2D pos, vel, acc, dis, fo;

		if (i == 22)
		{
			pos.x = x;
			pos.y = y + 27;
		}

		if (i < 11)
		{
			pos.x = x + 3;
			pos.y = y + (3 * i);
		}

		if (i < 22 && i > 10)
		{
			pos.x = x + 6;
			pos.y = y + (3 * (i - 11));
		}				

		if (i == 23)
		{
			pos.x = x + 9;
			pos.y = y + 27;
		}
		
		dis.x = 0;
		dis.y = 0;
		vel.x = 40;
		vel.y = -200;
		acc.x = 0;
		acc.y = 0;
		fo.x  = 0;
		fo.y  = 9;

		m = new mote(pos, vel, acc, true, 0.1f, fo, pos);
		moteSplosion.push_back(*m);

		isFired	= isBoomed = isHit = 0;
	}
}

void missile::drawMissile(GraphicsM * pGraphicsModule)
{
	mB.initBox(mP.x, mP.y, 12, 33);

	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		moi->draw(pGraphicsModule);
		moi++;
	}
}

void missile::updateAcc()
{
	mA.x = mF.x / mM;
	mA.y = mF.y / mM;

	if (mF.x > 0)
	{
		mF.x -= 1;
	}
	else if (mF.x < 0)
	{
		mF.x += 1;
	}
}

void missile::moveConstAcc(double t)
{
	updateAcc();
	mP.x += mV.x * t + 0.5 * mA.x * t;
	mP.x += mV.y * t + 0.5 * mA.y * t;

	mV.x += mA.x * t;
	mV.y += mA.y * t;
}

void missile::updateMissile(double t)
{
	if (isFired == true)
	{
		moveConstAcc(t);
		mB.initBox(mP.x, mP.y, 12, 33);
		std::vector<mote>::iterator moi = moteSplosion.begin();
		while (moi != moteSplosion.end())
		{
			moi->updateBox();
			moi->updateAcc();
			moi->moveConstAcc(t);
			moi++;
		}
	}
	else 
	{
		std::vector<mote>::iterator moi = moteSplosion.begin();
		while (moi != moteSplosion.end())
		{
			moi->setMoving(false);
			moi++;
		}
	}

	mB.initBox(mP.x, mP.y, 12, 33);
}

void missile::checkCollision(Point2D lsl, Point2D lsr, Point2D lst, Point2D rsl, Point2D rsr, Point2D rst, Point2D csl, Point2D csr, Point2D cst)
{	
	if (isBoomed == false)
	{
		std::vector<mote>::iterator moi = moteSplosion.begin();
	
		while (moi != moteSplosion.end())
		{
			moi->updateBox();

			if (moi->getBb().checkFlats()
				|| moi->getBb().checkSlopes(lst, lsl, lsr)
				|| moi->getBb().checkSlopes(rst, rsl, rsr)
				|| moi->getBb().checkSlopes(cst, csl, csr))
			{
				explodeMissile();
			}
			else 
			{

			}
			moi++;
		}			
	}
}

void missile::explodeMissile()
{
	mP.x = 2000;
	isBoomed = true;

	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		float x = rand() % 300 + 1;
		float y = rand() % 200 + 1;
		float n = rand() % 2 + 1;

		if (n == 1)
		{
			moi->setVelX(-x);
		}
		else if (n == 2)
		{
			moi->setVelX(x);
		}

		moi->setVelY(-y);
		moi++;
	}
}

void missile::setMissileShape(int x, int y)
{
	isBoomed = true;
	isFired = false;
		
	reMissile(x, y);
	
	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		moi->resetParticle();
		moi->setMoving(false);

		moi->setVelX(40);
		moi->setVelY(-200);

		moi++;
	}

	mP.x = x;
	mP.y = y;
	mA.x = 0;
	mA.y = 0;
	mV.x = 0;
	mV.y = 0;	

	isBoomed = false;
}

void missile::reMissile(int x, int y)
{
	int count = 0;
	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{ 
		Point2D pos, vel, acc, dis, fo;

		if (count == 22)
		{
			moi->setStartPosX(x);
			moi->setStartPosY(y + 27);
		}

		if (count < 11)
		{
			moi->setStartPosX(x + 3);
			moi->setStartPosY(y + (3 * count));
		}

		if (count < 22 && count > 10)
		{
			moi->setStartPosX(x + 6);
			moi->setStartPosY(y + (3 * (count - 11)));
		}
		
		if (count == 23)
		{
			moi->setStartPosX(x + 9);
			moi->setStartPosY(y + 27);
		}
		
		count++;
		moi++;		
	}
}

void missile::moveMissileLeft()
{
	mP.x -= 1;
	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		moi->setPosX(moi->getPosX() - 1);
		moi++;
	}
}

void missile::moveMissileRight()
{
	mP.x += 1;
	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		moi->setPosX(moi->getPosX() + 1);
		moi++;
	}
}
