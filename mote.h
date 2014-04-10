#pragma once

#include "dataTypes.h"
#include "graphics.h";
#include "definitions.h"
#include "particleModel.h"
#include "Windows.h"

class mote: public particleModel
{
private:
	Point2D		shape[4];
	Point2D		dispBuffObj[4];

public:
	mote(Point2D p, Point2D v, Point2D a, bool m, float m2, Point2D f, Point2D sp);
	~mote(){};
	
	void	setShape2Square();
	int		dispBufUpdate();
	int		draw(GraphicsM * pGraphicsModule);
};