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



	return S_OK;
}

void camera::release()
{
}

void camera::update(float playerX, float playerY, int choice, float changespeed)
{
	if (change == true)
	{
		if (_camera.x > playerX)
		{
			_camera.x = _camera.x + cosf(angle) * Distance / changespeed;

			if (_camera.x <= playerX)
			{
				_camera.x = playerX;
			}



			//===============¸Ê ÀÌÅ» ¹æÁö============================//
			if (_camera.x < WINSIZEX / 2)
			{
				_camera.x = WINSIZEX / 2;
			}

			if (_camera.x > _mapimage->GetWidth() - WINSIZEX / 2)
			{
				_camera.x = _mapimage->GetWidth() - WINSIZEX / 2;
			}

		}
		//==========================================================//



		if (_camera.x < playerX)
		{
			_camera.x = _camera.x + cosf(angle) * Distance / changespeed;

			if (_camera.x >= playerX)
			{
				_camera.x = playerX;
			}



			//===============¸Ê ÀÌÅ» ¹æÁö============================//
			if (_camera.x < WINSIZEX / 2)
			{
				_camera.x = WINSIZEX / 2;
			}

			if (_camera.x > _mapimage->GetWidth() - WINSIZEX / 2)
			{
				_camera.x = _mapimage->GetWidth() - WINSIZEX / 2;
			}

		}
		//==========================================================//


		if (_camera.y > playerY)
		{
			_camera.y = _camera.y + sinf(angle) * Distance / changespeed;

			if (_camera.y <= playerY)
			{
				_camera.y = playerY;
			}

			if (_camera.y < WINSIZEY / 2)
			{
				_camera.y = WINSIZEY / 2;
			}

			if (_camera.y > _mapimage->GetHeight() - WINSIZEY / 2)
			{
				_camera.y = _mapimage->GetHeight() - WINSIZEY / 2;
			}
		}

		if (_camera.y < playerY)
		{
			_camera.y = _camera.y + sinf(angle) * Distance / changespeed;

			if (_camera.y >= playerY)
			{
				_camera.y = playerY;
			}

			if (_camera.y < WINSIZEY / 2)
			{
				_camera.y = WINSIZEY / 2;
			}

			if (_camera.y > _mapimage->GetHeight() - WINSIZEY / 2)
			{
				_camera.y = _mapimage->GetHeight() - WINSIZEY / 2;
			}
		}

		if (playerX == _camera.x && playerY == _camera.y)
		{
			change = true;
		}

		if (_camera.x == WINSIZEX / 2 && _camera.y == WINSIZEY / 2)
		{
			change = true;
		}

		if (_camera.x == _mapimage->GetWidth() - WINSIZEX / 2 && _camera.y == _mapimage->GetHeight() - WINSIZEY / 2)
		{
			change = true;
		}

		if (_camera.x == WINSIZEX / 2 && _camera.y == _mapimage->GetHeight() - WINSIZEY / 2)
		{
			change = true;
		}

		if (_camera.x == _mapimage->GetWidth() - WINSIZEX / 2 && _camera.y == WINSIZEY / 2)
		{
			change = true;
		}


	}

	if (change == false)
	{
		if (playerX >= WINSIZEX / 2 && playerX <= _mapimage->GetWidth() - WINSIZEX / 2)
		{
			_camera.x = playerX;
		}
		else if (playerX <= WINSIZEX / 2)
		{
			_camera.x = WINSIZEX / 2;
		}
		else if (playerX >= _mapimage->GetWidth() - WINSIZEX / 2)
		{
			_camera.x = _mapimage->GetWidth() - WINSIZEX / 2;
		}


		if (playerY >= WINSIZEY / 2 && playerY <= _mapimage->GetHeight() - WINSIZEY / 2)
		{
			_camera.y = playerY;
		}
		else if (playerY <= WINSIZEY / 2)
		{
			_camera.y = WINSIZEY / 2;
		}
		else if (playerY >= _mapimage->GetHeight() - WINSIZEY / 2)
		{
			_camera.y = _mapimage->GetHeight() - WINSIZEY / 2;
		}
	}
}

void camera::render()
{
	//char str[128];
	//sprintf_s(str, "¸Êx : %f, ¸Êy : %f , ½ºÀ§Äª : %d , °Å¸® : %f  ,°¢µµ : %f", _camera.x, _camera.y, change, Distance, angle);
	//TextOut(getMemDC(), 100, 160, str, strlen(str));
}
