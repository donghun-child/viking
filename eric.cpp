#include "stdafx.h"
#include "eric.h"


eric::eric()
{
}


eric::~eric()
{
}

HRESULT eric::init()
{
	return S_OK;

	_eric_x = WINSIZEX / 2 + 100;
	_eric_y = WINSIZEY / 2;

	//_eric_rc = RectMakeCenter(_eric_x, _eric_y, 50, 50);
}

void eric::release()
{
}

void eric::update(POINTFLOAT StagePos, int choice)
{
	_cameraPos = StagePos;


	if (choice == 2)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_eric_x < 2950)
			{
				_eric_x += 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_eric_x > 0)
			{
				_eric_x -= 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_eric_y > 0)
			{
				_eric_y -= 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_eric_y += 10;
		}
	}
}

void eric::render()
{
	Rectangle(getMemDC(), _eric_x - _cameraPos.x + WINSIZEX / 2, _eric_y - _cameraPos.y + WINSIZEY / 2, _eric_x + 50 - _cameraPos.x + WINSIZEX / 2, _eric_y + 50 - _cameraPos.y + WINSIZEY / 2);
	char str[128];
	sprintf_s(str, "에릭 확인 : %f ", _eric_x);
	TextOut(getMemDC(), 200, 70, str, strlen(str));
}
