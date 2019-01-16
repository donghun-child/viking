#include "stdafx.h"
#include "camera.h"


camera::camera()
{
}


camera::~camera()
{
}

HRESULT camera::init()
{
	IMAGEMANAGER->addImage("backGround", "image/map.bmp", 3000, 2240, true, RGB(255, 0, 255));
	
	_eric.x = _eric.y = _eric.speed = 0;
	_olaf.x = _olaf.y = _olaf.speed = 0;
	_baleog.x = _baleog.y = _baleog.speed = 0;

	_camera_X = 0;
	_camera_Y = 0;

	return S_OK;
}

void camera::release()
{
}

void camera::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_camera_Y -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_camera_Y += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_camera_X -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_camera_X += 3;
	}
}

void camera::render()
{
	IMAGEMANAGER->findImage("backGround")->render(getMemDC(), 0, 0, _camera_X, _camera_Y, WINSIZEX, WINSIZEY);
}
