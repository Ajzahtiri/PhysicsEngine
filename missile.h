#pragma once

#include <vector>
#include "mote.h"
#include "particleModel.h"
#include "definitions.h"
#include "graphics.h"
#include "boundingBox.h"
#include "dataTypes.h"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

class missile
{
private:
	mote * m;
	std::vector<mote>	moteSplosion;
	bool isFired, isBoomed, isHit;

	Point2D mP, mV, mA, mF;
	float mM;

	int x, y;

	boundingBox mB;

public:
	missile(Point2D pos, Point2D vel, Point2D acc, float mas, Point2D fo, boundingBox b);
	~missile(){};

	void	initMissile();
	void	setMissileShape(int x, int y);
	void	squareTheMotes();
	void	updateAcc();
	void	updateMissile(double t);
	void	moveConstAcc(double t);
	void	drawMissile(GraphicsM * pGraphicsModule);	
	void	drawMissileMotes(GraphicsM * pGraphicsModule);

	void	checkCollision();
	void	explodeMissile();

	void	moveMissileLeft();
	void	moveMissileRight();
	bool	isMissileGone();
	void	reMissile(int x, int y);

	boundingBox getBb()
	{
		return mB;
	}
	
	bool		getBoomed()
	{
		return isBoomed;
	}
	void		setFired(bool b)
	{
		isFired = b;
	}
	bool		getFired()
	{
		return isFired;
	}

	void		setVelX(float x)
	{
		mV.x = x;
	}
	float		getVelX()
	{
		return mV.x;
	}
	void		setVelY(float y)
	{
		mV.y = y;
	}
	float		getVelY()
	{
		return mV.y;
	}
};