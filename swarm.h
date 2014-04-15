#ifndef SWARM_H
#define SWARM_H

#include "particleModel.h"
#include "swarmee.h"
#include <list>

class swarm : public particleModel
{
protected:
	boundingBox * b;
	std::list<swarmee> swarmees;
	bool intersect;

public:
	swarm(Point2D p, Point2D v, Point2D a, bool m, float m2, Point2D f, Point2D sp, float ww, float hh);
	~swarm(){};	
	
	void update(boundingBox bBox);
	void updateSwarmees(GraphicsM * pGraphicsModule);
	void chaseBuggy(boundingBox bBox);

	bool collisionTank(boundingBox bBox);
	//bool collisionMissile(boundingBox mBox);	

	void swarmAway();
};

#endif