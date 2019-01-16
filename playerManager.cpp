#include "stdafx.h"
#include "playerManager.h"


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
		_y[i] = 65;
	}

	for (int i = 0; i < 3; ++i)
	{
		_rc[i] = RectMake(_x[i], _y[i], 100, 100);
	}

	_isDebug = true;

	for (int i = 0; i < 3; ++i)
	{
		//센터
		_prove_X[i] = (_rc[i].right - _rc[i].left)/2 + _rc[i].left;
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

	pixelCollision();


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
			Rectangle(getMemDC(), _rc[0]);
		}
	}

	char str[100];
	sprintf_s(str, "%d", _prove_Y[BALEOG]);
	TextOut(getMemDC(), 300, 100, str, strlen(str));
}

void playerManager::pixelCollision()
{
	for (int i = _prove_Y[BALEOG] - 50; i < _prove_Y[BALEOG] + 50; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), _x[BALEOG], i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 0)
		{
			_y[i] = i - 100;

			break;
		}
	}
}
