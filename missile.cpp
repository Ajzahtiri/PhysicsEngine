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

	for (int i = 0; i < 20; i++)
	{
		Point2D pos, vel, acc, dis, fo;

		if (i < 10)
		{
			pos.x = x;
			pos.y = y - 13 - i * 3;
		}

		if (i > 9)
		{
			pos.x = x + 3;
			pos.y = y + 17 - i * 3;
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
	mB.initBox(mP.x - 5, mP.y, 20, 8);
}

void missile::drawMissileMotes(GraphicsM * pGraphicsModule)
{
	mB.initBox(mP.x - 5, mP.y, 20, 8);

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
	mB.initBox(mP.x - 5, mP.y, 20, 8);

	if (isFired == true)
	{
		moveConstAcc(t);
		mB.initBox(mP.x, mP.y, 30, 20);
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

	mB.initBox(mP.x - 5, mP.y, 20, 8);
}

void missile::checkCollision()
{
	if (isBoomed == false)
	{
		std::vector<mote>::iterator moi = moteSplosion.begin();
		while (moi != moteSplosion.end())
		{
			if (mP.y >= VIEWPORT_DOWN - 20 && (mP.x >= VIEWPORT_LEFT && mP.x <= 100) 
			|| (mP.y >= VIEWPORT_DOWN - 80 && (mP.x >= 290 && mP.x <= 460))
			|| (mP.y  >= VIEWPORT_DOWN - 120 && (mP.x  >= 180 && mP.x <= 260))
			|| (mP.y >= VIEWPORT_DOWN - 180 && (mP.x  >= 530 && mP.x <= VIEWPORT_RIGHT))
			|| ((mP.y >= VIEWPORT_DOWN - 350 && mP.y <= VIEWPORT_DOWN - 345) && (mP.x  >= 0 && mP.x <= 150)))
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

	x += 3;
	y -= 25;

	reMissile(x, y);

	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		moi->resetParticle();
		moi->setMoving(false);

		moi->setVelX(-100);
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
		if (t <= 10)
		{
			moi->setStartPosX(x + 1 + t * 2);
			moi->setStartPosY(y);
		}
		else if (t < 20)
		{
			moi->setStartPosX(x + 3 + t * 2);
			moi->setStartPosY(y + 2);
		}
		else if (t < 30)
		{
			moi->setStartPosX(x + 6 + t * 2);
			moi->setStartPosY(y + 4);
		}
		else if (t < 40)
		{
			moi->setStartPosX(x + 10 + t * 2);
			moi->setStartPosY(y + 6);
		}
		else if (t < 50)
		{
			moi->setStartPosX(x + 15 + t * 2);
			moi->setStartPosY(y + 8);
		}
		else if (t < 60)
		{
			moi->setStartPosX(x + 20 + t * 2);
			moi->setStartPosY(y + 10);
		}
		else if (t < 70)
		{
			moi->setStartPosX(x + 25 + t * 2);
			moi->setStartPosY(y + 12);
		}
		else if (t < 80)
		{
			moi->setStartPosX(x + 35 + t * 2);
			moi->setStartPosY(y + 14);
		}
		else if (t < 90)
		{
			moi->setStartPosX(x + 50 + t * 2);
			moi->setStartPosY(y + 16);
		}
		else if (t < 100)
		{
			moi->setStartPosX(x + 75 + t * 2);
			moi->setStartPosY(y + 20);
		}
		t++;
		moi++;
	}
}

void missile::moveMissileLeft()
{
	mP.x -= 3;
	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		moi->setPosX(moi->getPosX() - 3);
		moi++;
	}
}

void missile::moveMissileRight()
{
	mP.x += 3;
	std::vector<mote>::iterator moi = moteSplosion.begin();
	while (moi != moteSplosion.end())
	{
		moi->setPosX(moi->getPosX() + 3);
		moi++;
	}
}