#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include	<windows.h>
#include	"dataTypes.h"		/* include file for custom data types */
#include	"graphics.h"		/* include file for graphics module */
#include	"input.h"
#include	"particleModel.h"	
#include	"appearance.h"
#include	"definitions.h"

class snowball : public particleModel
{
	protected:
		Point2D		dispBuffObj[4];		// array to store display coordinates of a polygonal object		
		float		frameStartTime;
		float		frameProcessingTime;
		float		presentFrameInterval;
		Point2D		shape[4];

	public:
		snowball(Point2D pos, Point2D vel, Point2D acc, bool mov, float mas, Point2D f);
		~snowball(){};
		
		void setShape2Square(float m);
		void checkSnow();

		int update(keyEvent ke, GraphicsM * pGraphicsModule, float time);
		int draw(GraphicsM * gm);
		int dispBuffUpdate();		
};

#endif