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

	for (int i = 1; i < 25; i++)
	{
		Point2D pos, vel, acc, dis, fo;

		if (i == 23)
		{
			pos.x = x;
			pos.y = y - 6;
		}

		if (i < 12)
		{
			pos.x = x + 3;
			pos.y = y - (3 * i);
		}

		if (i < 23 && i > 11)
		{
			pos.x = x + 6;
			pos.y = y - (3 * (i - 11));
		}				

		if (i == 24)
		{
			pos.x = x + 9;
			pos.y = y - 6;
		}
		
		dis.x = 0;
		dis.y = 0;
		vel.x = 0;
		vel.y = 0;
		acc.x = 0;
		acc.y = 0;
		fo.x  = 0;
		fo.y  = 9;

		m = new mote(pos, vel, acc, true, 0.1f, fo, pos);
		moteSplosion.push_back(*m);

		isFired	= isBoomed = isHit = 0;
	}
}

void missile::squareTheMotes()
{
	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		moi->setShape2Square();
		moi++;
	}
}

void missile::drawMissile(GraphicsM * pGraphicsModule)
{
	mB.initBox(mP.x, mP.y, 12, -33);

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
	mB.initBox(mP.x, mP.y, 12, -33);

	if (isFired == true)
	{
		moveConstAcc(t);
		mB.initBox(mP.x, mP.y, 12, -33);
		std::vector<mote>::iterator moi = moteSplosion.begin();
		while (moi != moteSplosion.end())
		{
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

	mB.initBox(mP.x, mP.y, 12, -33);
}

void missile::checkCollision()
{
	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		if (isBoomed == false)
		{
			mB.initBox(mP.x, mP.y, 12, -33);
			if (mB.checkFlatsCollision())
			{
				explodeMissile();
			}
		}
		else 
		{

		}
		moi++;
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
		float y = rand() % 300 + 1;
		float n = rand() % 2 + 1;

		if (n == 1)
		{
			moi->setVelX(-x);
		}
		else if (n == 2)
		{
			moi->setVelX(x);
		}
		moi->setVelY(y);
		moi++;
	}
}

void missile::setMissileShape(int x, int y)
{
	isBoomed = true;
	isFired = false;

	x += 12;
	y -= 20;

	reMissile(x, y);

	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		moi->resetParticle();
		moi->setMoving(false);

		moi->setVelX(-50);
		moi->setVelY(-200);

		moi++;
	}

	mP.x = x;
	mP.y = y;
	mA.x = 0;
	mA.y = 0;
	mV.x = -100;
	mV.y = -200;

	isBoomed = false;
}

void missile::reMissile(int x, int y)
{
	int t = 0;
	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{ 
		Point2D pos, vel, acc, dis, fo;

		x = mP.x;
		y = mP.y;

		if (t < 10)
		{
			pos.x = x;
			pos.y = y - 13 - t * 3;
		}

		if (t < 20 && t > 9)
		{
			pos.x = x + 3;
			pos.y = y + 17 - t * 3;
		}

		if (t == 20)
		{
			pos.x = x + 6;
			pos.y = y + 20 - t * 3;
		}
		
		if (t == 21)
		{
			pos.x = x - 3;
			pos.y = y + 23 - t * 3;
		}

		if (t == 22)
		{
			pos.x = x;
			pos.y = y + 23 - t * 3;
		}

		if (t == 23)
		{
			pos.x = x + 3;
			pos.y = y + 26 - t * 3;
		}
		
		t++;
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