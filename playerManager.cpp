#include "stdafx.h"
#include "playerManager.h"
#include "camera.h"


playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}

HRESULT playerManager::init()
{
	for (int i = 0; i < 3; ++i)
	{
		_x[i] = 30 + 120 * i;
		_y[i] = 75;
	}

	for (int i = 0; i < 3; ++i)
	{
		_rc[i] = RectMake(_x[i], _y[i], 100, 100);
	}

	_isDebug = false;

	for (int i = 0; i < 3; ++i)
	{
		//센터
		_prove_X[i] = (_rc[i].right - _rc[i].left) / 2 + _rc[i].left;
		_prove_Y[i] = _rc[i].bottom;
	}

	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update()
{
	//캐릭터박스 보이기용
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		if (_isDebug)
		{
			_isDebug = false;
		}
		else
		{
			_isDebug = true;
		}
	}

	pixelCollisionGreen();
	pixelCollisionYellow();
	pixelCollisionEmerald();

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_x[0] -= 3;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_x[0] += 3;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_y[0] += 3;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_y[0] -= 3;
	}


	//갱신
	for (int i = 0; i < 3; ++i)
	{
		_rc[i] = RectMake(_x[i], _y[i], 100, 100);
		_prove_X[i] = _x[i] + 50;
		_prove_Y[i] = _y[i] + 100;
	}
}

void playerManager::render()
{
	if (_isDebug)
	{
		for (int i = 0; i < 3; ++i)
		{
			Rectangle(getMemDC(), _rc[i]);
		}
	}

	//char str[100];
	//sprintf_s(str, "_x : %d", _x[0]);
	//TextOut(getMemDC(), 300, 100, str, strlen(str));
	//
	//sprintf_s(str, "_prove_X : %d", _prove_X[0]);
	//TextOut(getMemDC(), 300, 120, str, strlen(str));
	//
	//sprintf_s(str, "_y : %d", _y[BALEOG]);
	//TextOut(getMemDC(), 300, 140, str, strlen(str));
}

void playerManager::pixelCollisionGreen()
{
	//위로 올라서게
	
	//벨로그
	for (int i = _prove_Y[BALEOG] - 5; i < _prove_Y[BALEOG] + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), _x[BALEOG] + 50 + _camera->getCameraX(), i + _camera->getCameraY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 0)
		{
			_y[BALEOG] = i - 100;

			break;
		}
	}
	//에릭
	for (int i = _prove_Y[ERIC] - 5; i < _prove_Y[ERIC] + 10; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), _x[ERIC] + 50 + _camera->getCameraX(), i + _camera->getCameraY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 0)
		{
			_y[ERIC] = i - 100;

			break;
		}
	}
	//올라프
	for (int i = _prove_Y[OLAF] - 5; i < _prove_Y[OLAF] + 10; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), _x[OLAF] + 50 + _camera->getCameraX(), i + _camera->getCameraY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 0)
		{
			_y[OLAF] = i - 100;

			break;
		}
	}
}

void playerManager::pixelCollisionYellow()
{
	//왼쪽벽

	//벨로그
	for (int i = _prove_X[BALEOG] -45; i > _prove_X[BALEOG] - 50; --i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i + _camera->getCameraX(), _y[BALEOG] + 50 + _camera->getCameraY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 255 && b == 0)
		{
			_x[BALEOG] = i;

			break;
		}
	}
	//에릭
	for (int i = _prove_X[ERIC] - 45; i > _prove_X[ERIC] - 50; --i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i + _camera->getCameraX(), _y[ERIC] + 50 + _camera->getCameraY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 255 && b == 0)
		{
			_x[ERIC] = i;

			break;
		}
	}
	//올라프
	for (int i = _prove_X[OLAF] - 45; i > _prove_X[OLAF] - 50; --i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i + _camera->getCameraX(), _y[OLAF] + 50 + _camera->getCameraY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 255 && b == 0)
		{
			_x[OLAF] = i;

			break;
		}
	}
}

void playerManager::pixelCollisionEmerald()
{
	//오른쪽벽

	//벨로그
	for (int i = _prove_X[BALEOG] + 45; i < _prove_X[BALEOG] + 50; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i + _camera->getCameraX(), _y[BALEOG] + 50 + _camera->getCameraY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_x[BALEOG] = i - 100;

			break;
		}
	}
	//에릭
	for (int i = _prove_X[ERIC] + 45; i < _prove_X[ERIC] + 50; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i + _camera->getCameraX(), _y[ERIC] + 50 + _camera->getCameraY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_x[ERIC] = i - 100;

			break;
		}
	}
	//올라프
	for (int i = _prove_X[OLAF] + 45; i < _prove_X[OLAF] + 50; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i + _camera->getCameraX(), _y[OLAF] + 50 + _camera->getCameraY());

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_x[OLAF] = i - 100;

			break;
		}
	}
}
