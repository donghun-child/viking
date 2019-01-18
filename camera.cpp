#include "stdafx.h"
#include "camera.h"
#include "playerManager.h"


camera::camera()
{
}


camera::~camera()
{
}

HRESULT camera::init()
{
	_mapimage = IMAGEMANAGER->findImage("backGround");

	_camera.x = 0;
	_camera.y = 0;
	_time = 0.0f;

	_change = false;


	return S_OK;
}

void camera::release()
{
}

void camera::update(float playerX, float playerY)
{
	if (!_change)
	{
		//4모서리에 있을때
		if (playerX < WINSIZEX / 2 && playerY < WINSIZEY / 2)
		{
			_camera.x = 0;
			_camera.y = 0;
		}
		else if (playerX > 3000 - WINSIZEX / 2 && playerY < WINSIZEY / 2)
		{
			_camera.x = 3000 - WINSIZEX;
			_camera.y = 0;
		}
		else if (playerX < WINSIZEX / 2 && playerY > 2240 - WINSIZEY / 2)
		{
			_camera.x = 0;
			_camera.y = 2240 - WINSIZEY;
		}
		else if (playerX > 3000 - WINSIZEX / 2 && playerY > 2240 - WINSIZEY / 2)
		{
			_camera.x = 3000 - WINSIZEX;
			_camera.y = 2240 - WINSIZEY;
		}
		//x좌표예외처리
		else if (playerX < WINSIZEX / 2)
		{
			_camera.x = 0;
			_camera.y = playerY - WINSIZEY / 2;
		}
		else if (playerX > 3000 - WINSIZEX / 2)
		{
			_camera.x = 3000 - WINSIZEX;
			_camera.y = playerY - WINSIZEY / 2;
		}
		//y좌표예외처리
		else if (playerY < WINSIZEY / 2)
		{
			_camera.x = playerX - WINSIZEX / 2;
			_camera.y = 0;
		}
		else if (playerY > 2240 - WINSIZEY / 2)
		{
			_camera.x = playerX - WINSIZEX / 2;
			_camera.y = 2240 - WINSIZEY;
		}
		//기본상태
		else
		{
			_camera.x = playerX - WINSIZEX / 2;
			_camera.y = playerY - WINSIZEY / 2;
		}
	}
	else
	{
		//changeMoving();
	}
}

void camera::render()
{
	//char str[100];
	//sprintf_s(str, "카메라 x : %f", _camera.x);
	//TextOut(getMemDC(), 500, 20, str, strlen(str));
	//sprintf_s(str, "카메라 y : %f", _camera.y);
	//TextOut(getMemDC(), 500, 40, str, strlen(str));
}

//스테이지1에 함수 있음

//void camera::cameraChange(float orizinX, float orizinY, float newX, float newY)
//{
//	_change = true;
//	_orizin = cameraPos(orizinX, orizinY);
//	_new = cameraPos(newX, newY);
//
//	_Distance = getDistance(_orizin.x, _orizin.y, _new.x, _new.y);
//	_angle = getAngle(_orizin.x, _orizin.y, _new.x, _new.y);
//	_worldTime = TIMEMANAGER->getWorldTime();
//	_time = 0.f;
//}
//
//void camera::changeMoving()
//{
//	if (!_change) return;
//
//	float elapsedTime = TIMEMANAGER->getElpasedTime();
//
//	float moveSpeed = (elapsedTime / _time) * _Distance;
//
//	_camera.x = _orizin.x + cosf(_angle) * moveSpeed;
//	_camera.y = _orizin.y + -sinf(_angle) * moveSpeed;
//
//	if (_time + _worldTime <= TIMEMANAGER->getWorldTime())
//	{
//		_worldTime = TIMEMANAGER->getWorldTime();
//
//		_camera.x = _new.x;
//		_camera.y = _new.y;
//
//		_change = false;
//	}
//}
//
//POINTFLOAT camera::cameraPos(float x, float y)
//{
//	//4모서리에 있을때
//	if (x < WINSIZEX / 2 && y < WINSIZEY / 2)
//	{
//		_point .x = 0;
//		_point .y = 0;
//
//		return _point;
//	}
//	else if (x > 3000 - WINSIZEX / 2 && y < WINSIZEY / 2)
//	{
//		_point.x = 3000 - WINSIZEX;
//		_point.y = 0;
//
//		return _point;
//	}
//	else if (x < WINSIZEX / 2 && y > 2240 - WINSIZEY / 2)
//	{
//		_point.x = 0;
//		_point.y = 2240 - WINSIZEY;
//
//		return _point;
//	}
//	else if (x > 3000 - WINSIZEX / 2 && y > 2240 - WINSIZEY / 2)
//	{
//		_point.x = 3000 - WINSIZEX;
//		_point.y = 2240 - WINSIZEY;
//
//		return _point;
//	}
//	//x좌표예외처리
//	else if (x < WINSIZEX / 2)
//	{
//		_point.x = 0;
//		_point.y = y - WINSIZEY / 2;
//
//		return _point;
//	}
//	else if (x > 3000 - WINSIZEX / 2)
//	{
//		_point.x = 3000 - WINSIZEX;
//		_point.y = y - WINSIZEY / 2;
//
//		return _point;
//	}
//	//y좌표예외처리
//	else if (y < WINSIZEY / 2)
//	{
//		_point.x = x - WINSIZEX / 2;
//		_point.y = 0;
//
//		return _point;
//	}
//	else if (y > 2240 - WINSIZEY / 2)
//	{
//		_point.x = x - WINSIZEX / 2;
//		_point.y = 2240 - WINSIZEY;
//
//		return _point;
//	}
//	//기본상태
//	else
//	{
//		_point.x = x - WINSIZEX / 2;
//		_point.y = y - WINSIZEY / 2;
//
//		return _point;
//	}
//}


