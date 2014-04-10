
#ifndef _PARTICLEMODEL_H
#define _PARTICLEMODEL_H

#include	<windows.h>
#include	"dataTypes.h"		/* include file for custom data types */
#include	"graphics.h"		/* include file for graphics module */
#include	"input.h"			/* include file for user input module */
#include	"boundingBox.h"
#include	<vector>

class particleModel
{
	protected:		
		Point2D	position;
		Point2D	displacement;
		Point2D	velocity;
		Point2D	acceleration;
		Point2D	totalForce;
		Point2D	startPos;		
		bool	isMoving;
		float	mass;
		
		boundingBox b;

	public:		
		particleModel(Point2D pos, Point2D vel, Point2D acc, bool mov, float mas, Point2D f, Point2D sp);
		~particleModel(){};

		void	setPos(float x, float y);		
		void	checkWallCollisions(boundingBox *b);
		Point2D getPos();
		void	moveConstVel(double t);
		void	moveConstAcc(double t);
		void	updateAcc();

		boundingBox getBb()
		{
			return b;
		}
		void	setPosX(float x)
		{
			position.x = x;
		}
		void	setPosY(float y)
		{
			position.y = y;
		}
		float	getPosX()
		{
			return position.x;
		}
		float	getPosY()
		{
			return position.y;
		}

		void	setDisX(float x)
		{
			displacement.x = x;
		}
		void	setDisY(float y)
		{
			displacement.y = y;
		}
		float	getDisX()
		{
			return displacement.x;
		}
		float	getDisY()
		{
			return displacement.y;
		}

		void	setVel(float x, float y)
		{
			velocity.x = x;
			velocity.y = y;
		}
		void	setVelX(float x)
		{
			velocity.x = x;
		}
		void	setVelY(float y)
		{
			velocity.y = y;
		}
		float	getVelX()
		{
			return velocity.x;
		}
		float	getVelY()
		{
			return velocity.y;
		}

		void	setAccX(float x)
		{
			acceleration.x = x;
		}
		void	setAccY(float y)
		{
			acceleration.y = y;
		}
		float	getAccX()
		{
			return acceleration.x;
		}
		float	getAccY()
		{
			return acceleration.y;
		}

		void	setForceX(float x)
		{
			totalForce.x = x;
		}
		void	setForceY(float y)
		{
			totalForce.y = y;
		}
		float	getForceX()
		{
			return totalForce.x;
		}
		float	getForceY()
		{
			return totalForce.y;
		}

		void	setMass(float m)
		{
			mass = m;
		}
		float	getMass()
		{
			return mass;
		}

		void	moveRight()
		{
			position.x += displacement.x;
		}
		void	moveLeft()	
		{
			position.x -= displacement.x;
		}
		void	moveUp()
		{
			position.y -= displacement.y;
		}
		void	moveDown()
		{
			position.y += displacement.y;
		}

		void	setStartPos(Point2D sp)
		{
			startPos = sp;
		}
		void	setStartPosX(float x)
		{
			startPos.x = x;
		}
		void	setStartPosY(float y)
		{
			startPos.y = y;
		}

		void	resetParticle()
		{
			setPosX(startPos.x);
			setPosY(startPos.y);
		}
		void	setMoving(bool m)
		{
			isMoving = m;
		}
		bool	getMoving()
		{
			return isMoving;
		}
		
		int		worldDataModuleInit();
};

#endif