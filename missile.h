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
	void	updateAcc();
	void	updateMissile(double t);
	void	moveConstAcc(double t);
	void	drawMissile(GraphicsM * pGraphicsModule);	

	void	checkCollision(Point2D lsl, Point2D lsr, Point2D lst, Point2D rsl, Point2D rsr, Point2D rst, Point2D csl, Point2D csr, Point2D cst);
	void	explodeMissile();

	void	moveMissileLeft();
	void	moveMissileRight();
	bool	isMissileGone();
	void	reMissile(int x, int y);
	Point2D	getPos()
	{
		return mP;
	}

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