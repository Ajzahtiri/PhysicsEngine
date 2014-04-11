#pragma once
#include	"dataTypes.h"		/* include file for custom data types */
#include	"graphics.h"		/* include file for graphics module */
#include	"definitions.h"

class boundingBox
{
	protected:
		float x, y, width, height, left, right, top, bottom;
		Point2D tlc;
		Point2D trc;
		Point2D blc;
		Point2D brc;
		Point2D vel;

	public:
		boundingBox();
		~boundingBox(){};
		void	initBox(float x, float y, float w, float h);

		bool	checkSlopes(Point2D sl, Point2D sr, Point2D st);
		int		checkWallCollisions();		
		bool	checkFlats();

		void	setX(float xx)
		{
			x = xx;
		}
		void	setY(float yy)
		{
			y = yy;
		}
		float	getX()
		{
			return x;
		}
		float	getY() 
		{
			return y;
		}

		void	setWidth(float w)
		{
			width = w;
		}
		void	setHeight(float h)
		{
			height = h;
		}
		float	getWidth()
		{
			return width;
		}
		float	getHeight()
		{
			return height;
		}

		void	setLeft(float l)
		{
			left = l;
		}
		void	setRight(float r)
		{
			right = r;
		}
		void	setTop(float t)
		{
			top = t;
		}
		void	setBottom(float b)
		{
			bottom = b;
		}
		float	getLeft()
		{
			return left;
		}
		float	getRight()
		{
			return right;
		}
		float	getTop()
		{
			return top;
		}
		float	getBottom()
		{
			return bottom;
		}

		float	getTlcX()
		{
			return tlc.x;
		}
		float	getTlcY()
		{
			return tlc.y;
		}
		float	getTrcX()
		{
			return trc.x;
		}
		float	getTrcY()
		{
			return trc.y;
		}
		float	getBlcX()
		{
			return blc.x;
		}
		float	getBlcY()
		{
			return blc.y;
		}
		float	getBrcX()
		{
			return brc.x;
		}
		float	getBrcY()
		{
			return brc.y;
		}
	
};