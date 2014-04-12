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

public:
	swarm(Point2D p, Point2D v, Point2D a, bool m, float m2, Point2D f, Point2D sp);
	~swarm(){};

	

#endif