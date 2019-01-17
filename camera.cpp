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
			if (_camera.x < 0)
			{
				_camera.x = 0;
			}

			if (_camera.x > _mapimage->GetWidth())
			{
				_camera.x = _mapimage->GetWidth();
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
			if (_camera.x < 0)
			{
				_camera.x = 0;
			}

			if (_camera.x > _mapimage->GetWidth())
			{
				_camera.x = _mapimage->GetWidth();
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

			if (_camera.y < 0)
			{
				_camera.y = 0;
			}

			if (_camera.y > _mapimage->GetHeight())
			{
				_camera.y = _mapimage->GetHeight();
			}
		}

		if (_camera.y < playerY)
		{
			_camera.y = _camera.y + sinf(angle) * Distance / changespeed;

			if (_camera.y >= playerY)
			{
				_camera.y = playerY;
			}

			if (_camera.y <0)
			{
				_camera.y = 0;
			}

			if (_camera.y > _mapimage->GetHeight())
			{
				_camera.y = _mapimage->GetHeight();
			}
		}

		if (playerX == _camera.x && playerY == _camera.y)
		{
			change = true;
		}

		if (_camera.x == 0 && _camera.y == 0)
		{
			change = true;
		}

		if (_camera.x == _mapimage->GetWidth()&& _camera.y == _mapimage->GetHeight())
		{
			change = true;
		}

		if (_camera.x == 0 && _camera.y == _mapimage->GetHeight())
		{
			change = true;
		}

		if (_camera.x == _mapimage->GetWidth()&& _camera.y == 0)
		{
			change = true;
		}


	}

	if (change == false)
	{
		if (playerX  >= WINSIZEX / 2 && playerX <= _mapimage->GetWidth())
		{
			_camera.x = playerX - WINSIZEX / 2;
		}
		else if (playerX <= 0)
		{
			_camera.x = 0;
		}
		else if (playerX >= _mapimage->GetWidth())
		{
			_camera.x = _mapimage->GetWidth();
		}


		if (playerY >= WINSIZEY / 2 && playerY <= _mapimage->GetHeight())
		{
			_camera.y = playerY - WINSIZEY / 2;
		}
		else if (playerY <= 0)
		{
			_camera.y = 0;
		}
		else if (playerY >= _mapimage->GetHeight())
		{
			_camera.y = _mapimage->GetHeight();
		}
	}
}

void camera::render()
{
	char str[128];
	sprintf_s(str, "¸Êx : %f, ¸Êy : %f , ½ºÀ§Äª : %d , °Å¸® : %f  ,°¢µµ : %f", _camera.x , _camera.y , change, Distance, angle);
	TextOut(getMemDC(), 100, 260, str, strlen(str));
}
