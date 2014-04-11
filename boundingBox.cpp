#include "boundingBox.h"

boundingBox::boundingBox()
{

}

void boundingBox::initBox(float xx, float yy, float w, float h)
{
	x = xx;
	y = yy;
	width = w;
	height = h;
	left = xx;
	top = yy;
	right = xx + width;
	bottom = yy + height;
	tlc.x = xx;
	tlc.y = yy;
	trc.x = xx + width;
	trc.y = yy;
	blc.x = xx;
	blc.y = yy + height;
	brc.x = xx + width;
	brc.y = yy + height;
}

bool boundingBox::checkFlats()
{
	if((bottom >= VIEWPORT_DOWN - 20 && (right >= VIEWPORT_LEFT && left <= 100)) 
		|| (bottom >= VIEWPORT_DOWN - 80 && (right >= 290 && left <= 460))
		|| (bottom >= VIEWPORT_DOWN - 120 && (right >= 180 && left <= 260))
		|| (bottom >= VIEWPORT_DOWN - 180 && (right >= 530 && left <= VIEWPORT_RIGHT))
		|| ((bottom >= VIEWPORT_DOWN - 350 && top <= VIEWPORT_DOWN - 345) && (right >= 0 && left <= 150))
		|| top >= VIEWPORT_DOWN)
	{		
		return true;
	}
	else 
	{
		return false;
	}
}

int boundingBox::checkWallCollisions()
{
	if (left <= VIEWPORT_LEFT)
	{
		return 1;
	}

	if (top <= VIEWPORT_UP)
	{
		return 2;
	}

	if (right >= VIEWPORT_RIGHT)
	{
		return 3;
	}

	if (bottom >= VIEWPORT_DOWN)
	{
		return 4;
	}	
}

bool boundingBox::checkSlopes(Point2D sl, Point2D sr, Point2D st)
{
	bool b1 = false, b2 = false;
	float a, b, c, d, e, f, g, h, i, j, k, l, m, n;
	a = st.x;
	b = st.y;
	c = sl.x;
	d = sl.y;
	e = sr.x;
	f = sr.y;

	if (getBlcY() < b && getBrcY() < b)
	{
		return false;
	}
	else 
	{
		g = getBlcX();
		h = getBlcY();
		
		i = e * (b - d) + f * (c - a) + a * d - b * c;
		j = g * (b - d) + h * (c - a) + a * d - b * c;
		k = a * (f - d) + b * (c - e) + e * d - f * c;
		l = g * (f - d) + h * (c - e) + e * d - f * c;
		m = c * (b - f) + d * (e - a) + a * f - b * e;
		n = g * (b - f) + h * (e - a) + a * f - b * e;

		if (j == 0 || l == 0 || n == 0)
		{
			b1 = true;
		}
		else if((i / j >= 0) && (k / l >= 0) && (m / n >= 0))
		{
			b1 = true;
		}
		else 
		{
			b1 = false;
		}

		g = getBrcX();
		h = getBrcY();

		i = e * (b - d) + f * (c - a) + a * d - b * c;
		j = g * (b - d) + h * (c - a) + a * d - b * c;
		k = a * (f - d) + b * (c - e) + e * d - f * c;
		l = g * (f - d) + h * (c - e) + e * d - f * c;
		m = c * (b - f) + d * (e - a) + a * f - b * e;
		n = g * (b - f) + h * (e - a) + a * f - b * e;

		if (j == 0 || l == 0 || n == 0)
		{
			b2 = true;
		}
		else if ((i / j >= 0) && (k / l >= 0) && (m / n >= 0))
		{
			b2 = true;
		}
		else
		{
			b2 = false;
		}

		//overall test
		if (b1 == true || b2 == true)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
}