#pragma once

#include "particleModel.h"
#include "boundingBox.h"
#include "dataTypes.h"
#include "definitions.h"
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
	swarmee(Point2D p, Point2D v, Point2D a, bool m, float m2, Point2D f, Point2D s, boundingBox bb, float w, float h);
	~swarmee(){};

	void	setShape2Square();
	int		dispBufUpdate();

	int		draw(GraphicsM * pGraphicsModule);

	bool	getUpdateMe()
	{
		return updateMe;
	}
	void	setUpdateMe(bool b)
	{
		updateMe = b;
	}
	
	void	updateSwarmee(boundingBox bBox);
	void	stateManagement(boundingBox bBox, boundingBox * swBox);
	void	swarmeeAway(boundingBox swBox);
	void	stanceChange(boundingBox * swBox, boundingBox bBox, boundingBox * pBox);

};
