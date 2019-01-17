#include "stdafx.h"
#include "player3.h"


player3::player3()
{
}


player3::~player3()
{
}

HRESULT player3::init()
{

	_play_x = WINSIZEX / 2 + 200;
	_play_y = WINSIZEY / 2;

	return S_OK;
}

void player3::release()
{
}

void player3::update(POINTFLOAT StagePos, int choice)
{
	_cameraPos = StagePos;


	if (choice == 3)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_play_x < 2950)
			{
				_play_x += 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_play_x > 0)
			{
				_play_x -= 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_play_y > 0)
			{
				_play_y -= 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_play_y += 10;
		}
	}

}

void player3::render()
{
	Rectangle(getMemDC(), _play_x - _cameraPos.x + WINSIZEX / 2, _play_y - _cameraPos.y + WINSIZEY / 2, _play_x + 50 - _cameraPos.x + WINSIZEX / 2, _play_y + 50 - _cameraPos.y + WINSIZEY / 2);

	char str[128];
	sprintf_s(str, " È®ÀÎ¿ë : %f", _play_x);
	TextOut(getMemDC(), 200, 60, str, strlen(str));
}
