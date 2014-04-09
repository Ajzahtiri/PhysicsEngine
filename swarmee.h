#pragma once

#include "particleModel.h"
#include "boundingBox.h"
#include "dataTypes.h"
#include <windows.h>

class swarmee : public particleModel
{
private:
	Point2D		shape[4];
	Point2D		dispBuffObj[4];
	boundingBox b;

	int			state;
	bool		ip;
	bool		updateMe;

public:
	swarmee(Point2D p, Point2D v, Point2D a, bool m, float m2, Point2D f, Point2D s, boundingBox b);
	~swarmee(){};

	void	setShape2Square();
	int		dispBuffObj();
	int		draw(GraphicsM * pGraphicsModule);

	bool	getUpdateMe()
	{
		return updateMe;
	}
	void	setUpdateMe(bool b)
	{
		updateMe = b;
	}
	
	//void	updateSwarmee

};
