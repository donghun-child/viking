#include "stdafx.h"
#include "baleog.h"


baleog::baleog()
{
}


baleog::~baleog()
{
}

HRESULT baleog::init()
{
	_baleogPlayer.baleogImage = IMAGEMANAGER->addFrameImage("벨로그", "image/Baleog.bmp", 1200, 1950, 8, 13, true, RGB(255, 0, 255));
	_baleogPlayer.x = BALEOG_X;
	_baleogPlayer.y = BALEOG_Y;
	_baleogPlayer.speed = BALEOG_SPEED;
	_baleogPlayer.baleogRc = RectMakeCenter(_baleogPlayer.x, _baleogPlayer.y, _baleogPlayer.baleogImage->getFrameWidth(), _baleogPlayer.baleogImage->getFrameHeight());

	_baleogState = BALEOG_RIGHT_STOP; //처음엔 오른쪽 기본상태로

	int rightStop[] = { 0,1 };
	//KEYANIMANAGER->addArrayFrameAnimation("")


	return S_OK;
}

void baleog::release()
{
}

void baleog::update()
{
}

void baleog::render()
{
}
