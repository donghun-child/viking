#include "stdafx.h"
#include "arrow.h"


arrow::arrow()
{
}


arrow::~arrow()
{
}

HRESULT arrow::init(const char* imageName, int arrowMax, float range)
{
	_arrowState = ARROW_RIGHT_FIRE;

	_imageName = imageName;
	int rightFire[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("È­»ì½ô", "rightFire", imageName, rightFire, 5, 6, true);

	int leftFire[] = { 9, 8, 7, 6, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("È­»ì½ô", "leftFire", imageName, leftFire, 5, 6, true);

	_arrowAni = KEYANIMANAGER->findAnimation("È­»ì½ô", "rightFire");

	_arrowMax = arrowMax;
	_range = range;


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
		_viArrow->arrowImage->aniRender(getMemDC(), _viArrow->arrowRc.left, _viArrow->arrowRc.top, _arrowAni);
	}
}

void arrow::arrowFire(float x, float y, float speed)
{
	if (_vArrow.size() > _arrowMax) return;

	tagArrow arrow;
	arrow.arrowImage = IMAGEMANAGER->findImage(_imageName);
	arrow.x = arrow.fireX = x;
	arrow.y = arrow.fireY = y;
	arrow.radius = arrow.arrowImage->getFrameWidth() / 2;
	arrow.speed = speed;
	arrow.arrowRc = RectMakeCenter(arrow.x, arrow.y, arrow.arrowImage->getFrameWidth(), arrow.arrowImage->getFrameHeight());

	_vArrow.push_back(arrow);
}

void arrow::arrowMove()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
	{

		//¿À¸¥ÂÊ ½ð»óÅÂ
		if (_arrowState == ARROW_RIGHT_FIRE)
		{
			_viArrow->x += _viArrow->speed;
			_arrowAni = KEYANIMANAGER->findAnimation("È­»ì½ô", "rightFire");
			_arrowAni->start();

		}

		//¿ÞÂÊ ½ð»óÅÂ
		if (_arrowState == ARROW_LEFT_FIRE)
		{
			_viArrow->x -= _viArrow->speed;
			_arrowAni = KEYANIMANAGER->findAnimation("È­»ì½ô", "leftFire");
			_arrowAni->start();
		}

		_viArrow->arrowRc = RectMakeCenter(_viArrow->x, _viArrow->y, _viArrow->arrowImage->getFrameWidth(), _viArrow->arrowImage->getFrameHeight());

		if (_range < getDistance(_viArrow->x, _viArrow->y, _viArrow->fireX, _viArrow->fireY))
		{
			_viArrow = _vArrow.erase(_viArrow);
		}
		else _viArrow++;
	}

}
