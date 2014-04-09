#include "appearance.h"

appearance::appearance()
{

}

appearance::~appearance()
{

}

void appearance::setShape2Square()
{
	shape[0].x = 0.0F;	shape[0].y = 0.0F;
    shape[1].x = 10.0F;	shape[1].y = 0.0F;
    shape[2].x = 10.0F;	shape[2].y = 10.0F;
    shape[3].x = 0.0F;	shape[3].y = 10.0F;
}