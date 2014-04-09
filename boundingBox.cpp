#include "boundingBox.h"

boundingBox::boundingBox()
{

}

boundingBox::~boundingBox()
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

bool boundingBox::checkCollision(boundingBox b)
{
	if (b.getLeft() > left && b.getLeft() < right && b.getTop() > top && b.getTop() < bottom)
	{
		return true;
	}

	else if (b.getRight() > left && b.getRight() < right && b.getTop() > top && b.getTop() < bottom)
	{
		return true;
	}

	else if (b.getLeft() > left && b.getLeft() < right && b.getBottom() > top && b.getBottom() < bottom)
	{
		return true;
	}

	else if (b.getRight() > left && b.getRight() < right && b.getBottom() > top && b.getBottom() < bottom)
	{
		return true;
	}

	else
	{
		return false;
	}
}