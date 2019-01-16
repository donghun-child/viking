#include "stdafx.h"
#include "arrow.h"


arrow::arrow()
{
}


arrow::~arrow()
{
}

HRESULT arrow::init(const char * imageName, int arrowMax, float range)
{
	_imageName = imageName;
	_arrowMax = arrowMax;
	_range = range;

	return S_OK;
}

void arrow::release()
{
}

void arrow::update()
{

}

void arrow::render()
{
}

void arrow::arrowFire(float x, float y, float angle, float speed)
{
	tagArrow arrow;
	arrow.arrowImage = IMAGEMANAGER->findImage(_imageName);
	arrow.x = arrow.fireX = x;
	arrow.y = arrow.fireY = y;
	arrow.angle = angle;
	arrow.radius = 
}

void arrow::arrowMove()
{
}
