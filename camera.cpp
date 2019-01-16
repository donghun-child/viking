#include "stdafx.h"
#include "camera.h"


camera::camera()
{
}


camera::~camera()
{
}

HRESULT camera::init(float x, float y, float speed)
{
	IMAGEMANAGER->addImage("backGround", "image/map.bmp", 3000, 2240, true, RGB(255, 0, 255));
	
	_eric.x = WINSIZEX / 2;
	_eric.y = WINSIZEY / 2;

	_olaf.x = WINSIZEX / 2 + 100;
	_olaf.y = WINSIZEY / 2 ;

	_baleog.x = WINSIZEX / 2 + 200;
	_baleog.y = WINSIZEY / 2;

	_camera_X = 0;
	_camera_Y = 0;

	_viking_Pic = 2;

	_back = false;

	return S_OK;
}

void camera::release()
{
}

void camera::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_viking_Pic == 0)
		{
			_eric.y -= 10;
		}
		else if (_viking_Pic == 1) _olaf.y -= 10;
		else _baleog.y -= 10;

		if (_camera_Y > 0) _camera_Y -= 10;
		else _camera_Y = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_viking_Pic == 0)
		{
			_eric.y += 10;
		}
		else if (_viking_Pic == 1) _olaf.y += 10;
		else _baleog.y += 10;

		if (_camera_Y < 1440) _camera_Y += 10;
		else _camera_Y = 1440;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_viking_Pic == 0)
		{
			_eric.x -= 10;
		}
		else if (_viking_Pic == 1) _olaf.x -= 10;
		else _baleog.x -= 10;

		if (_camera_X > 0) _camera_X -= 10;
		else _camera_X = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_viking_Pic == 0)
		{
			_eric.x += 10;
		}
		else if (_viking_Pic == 1)  _olaf.x += 10;
		else _baleog.x += 10;

		if(_camera_X < 2000) _camera_X += 10;
		else _camera_X = 2000;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
	{
		if(_viking_Pic < 2) _viking_Pic++;
		else  _viking_Pic = 0;

		_back = true;

		switch (_viking_Pic)
		{
		case VIKING_ERIC:
			//_camera_X = _eric.x - WINSIZEX / 2;
			//_camera_Y = _eric.y - WINSIZEY / 2;
			break;
		case VIKING_OLAF:
			_camera_X = _olaf.x - WINSIZEX / 2;
			_camera_Y = _olaf.y - WINSIZEY / 2;
			break;
		case VIKING_BALEOG:
			_camera_X = _baleog.x - WINSIZEX / 2;
			_camera_Y = _baleog.y - WINSIZEY / 2;
			break;
		}
	}

	switch (_viking_Pic)
	{
	case VIKING_ERIC:
		//if(_camera_X > 0 && _camera_X)
		if (_camera_X < _eric.x - WINSIZEX / 2)
		{
			_camera_X += 10.0f;
		}
		else if (_camera_X > _eric.x - WINSIZEX / 2)
		{
			_camera_X -= 10.0f;
		}
		else _camera_X = _eric.x - WINSIZEX / 2;

		if (_camera_Y  > _eric.y - WINSIZEY / 2)
		{
			_camera_Y -= 10.0f;
		}
		else if (_camera_Y < _eric.y - WINSIZEX / 2)
		{
			_camera_Y += 10.0f;
		}

		break;
	//case VIKING_OLAF:
	//	_camera_X = _olaf.x - WINSIZEX / 2;
	//	_camera_Y = _olaf.y - WINSIZEY / 2;
	//	break;
	//case VIKING_BALEOG:
	//	_camera_X = _baleog.x - WINSIZEX / 2;
	//	_camera_Y = _baleog.y - WINSIZEY / 2;
	//	break;
	}
	
}

void camera::render()
{
	IMAGEMANAGER->findImage("backGround")->render(getMemDC(), 0, 0, _camera_X, _camera_Y, WINSIZEX, WINSIZEY);

	char str[128];
	sprintf_s(str, "카메라_X : %f  에릭_X : %f", _camera_X , _eric.x - WINSIZEX / 2);
	TextOut(getMemDC(), 100, 100, str, strlen(str));
	sprintf_s(str, "카메라_Y : %f  에릭_Y : %f", _camera_Y, _eric.y - WINSIZEY / 2);
	TextOut(getMemDC(), 100, 120, str, strlen(str));
	sprintf_s(str, "올라프_X : %f", _olaf.x - WINSIZEX / 2);
	TextOut(getMemDC(), 450, 100, str, strlen(str));
	sprintf_s(str, "올라프_Y : %f", _olaf.y - WINSIZEY / 2);
	TextOut(getMemDC(), 450, 120, str, strlen(str));

	
	Rectangle(getMemDC(), _eric.x + 25 - _camera_X, _eric.y + 25 - _camera_Y, _eric.x - 25 - _camera_X, _eric.y - 25 - _camera_Y);
	Rectangle(getMemDC(), _olaf.x + 25 - _camera_X, _olaf.y + 25 - _camera_Y, _olaf.x - 25 - _camera_X, _olaf.y - 25 - _camera_Y);
	Rectangle(getMemDC(), _baleog.x + 25 - _camera_X, _baleog.y + 25 - _camera_Y, _baleog.x - 25 - _camera_X, _baleog.y - 25 - _camera_Y);
	
}
