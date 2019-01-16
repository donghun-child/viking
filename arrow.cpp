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
	_currentFrameX = _currentFrameY = 0;

	return S_OK;
}

void arrow::release()
{
}

void arrow::update()
{
	arrowMove();
}

void arrow::render()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end(); _viArrow++)
	{
		//_viArrow->arrowImage->frameRender(getMemDC(), _viArrow->arrowRc.left, _viArrow->arrowRc.top,);
	}
}

void arrow::arrowFire(float x, float y, float angle, float speed)
{
	if(_vArrow.size() > _arrowMax) return;

	tagArrow arrow;
	arrow.arrowImage = IMAGEMANAGER->findImage(_imageName);
	arrow.x = arrow.fireX = x;
	arrow.y = arrow.fireY = y;
	arrow.angle = angle;
	arrow.radius = arrow.arrowImage->getFrameWidth() / 2;
	arrow.speed = speed;
	arrow.arrowRc = RectMakeCenter(arrow.x, arrow.y, arrow.arrowImage->getFrameWidth(), arrow.arrowImage->getFrameHeight());

	_vArrow.push_back(arrow);
}

void arrow::arrowMove()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
	{

	}
}
