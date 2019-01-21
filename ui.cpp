#include "stdafx.h"
#include "ui.h"
#include "playerManager.h"


ui::ui()
{
}


ui::~ui()
{
}

HRESULT ui::init()
{
	IMAGEMANAGER->addImage("UI", "image/ui.bmp", 1000, 191, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("profile", "image/profile.bmp", 375, 270, 3, 3, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("life", "image/life.bmp", 105, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("box", "image/box.bmp", 62, 62, true, RGB(255, 0, 255));


	_ericCurrentX = _ericCurrentY = 0;
	_baleogCurrentX = 1;
	_baleogCurrentY = 1;
	_olafCurrentX = 2;
	_olafCurrentY = 1;

	_ericLife = 105;
	_baleogLife = 105;
	_olafLife = 105;


	_ericBox_X = 187; 
	_ericBox_Y = 671;
	_baleogBox_X = 470; 
	_baleogBox_Y = 671;
	_olafBox_X = 751; 
	_olafBox_Y = 671;
	
	_ericCursor = _baleogCursor = _olafCursor = false;
	_oldTime = GetTickCount();

	return S_OK;
}

void ui::release()
{
}

void ui::update(int choice, bool uiChange)
{
	if (uiChange)
	{
		keyControl(choice);
		if (GetTickCount() - _oldTime >= 1 * 400)
		{
			if (choice == 0)
			{
				if (!_ericCursor) _ericCursor = true;
				else _ericCursor = false;
				
			}
			else if (choice == 1)
			{
				if (!_baleogCursor)_baleogCursor = true;
				else _baleogCursor = false;
			}
			else if (choice == 2)
			{
				if (!_olafCursor) _olafCursor = true;
				else _olafCursor = false;
			}
			_oldTime = GetTickCount();
		}
	}
	else
	{
		_ericCursor = _baleogCursor = _olafCursor = false;
	}

}

void ui::render()
{
	IMAGEMANAGER->findImage("UI")->render(getMemDC(), 0, 609);
	IMAGEMANAGER->findImage("profile")->frameRender(getMemDC(), 62, 671, _ericCurrentX, _ericCurrentY);
	IMAGEMANAGER->findImage("profile")->frameRender(getMemDC(), 344, 671, _baleogCurrentX, _baleogCurrentY);
	IMAGEMANAGER->findImage("profile")->frameRender(getMemDC(), 625, 671, _olafCurrentX, _olafCurrentY);
	IMAGEMANAGER->findImage("life")->render(getMemDC(), 70, 770, 0, 0, _ericLife, 25);						// life -35씩 줄이면 피가 하나씩 깍임
	IMAGEMANAGER->findImage("life")->render(getMemDC(), 350, 770, 0, 0, _baleogLife, 25);
	IMAGEMANAGER->findImage("life")->render(getMemDC(), 630, 770, 0, 0, _olafLife, 25);
	if (!_ericCursor)
	{
		IMAGEMANAGER->findImage("box")->render(getMemDC(), _ericBox_X, _ericBox_Y);
	}
	if (!_baleogCursor)
	{
		IMAGEMANAGER->findImage("box")->render(getMemDC(), _baleogBox_X, _baleogBox_Y);
	}
	if (!_olafCursor)
	{
		IMAGEMANAGER->findImage("box")->render(getMemDC(), _olafBox_X, _olafBox_Y);
	}

	//char str[128];
	//sprintf_s(str, "초이스 : %d", _choice);
	//TextOut(getMemDC(), 100, 100, str, strlen(str));
}

void ui::profileUpdate(int choice)
{
	_choice = choice;
	if (choice == 0)
	{
		_ericCurrentX = _ericCurrentY = 0;
		_baleogCurrentX = 1;
		_baleogCurrentY = 1;
		_olafCurrentX = 2;
		_olafCurrentY = 1;
	}
	else if (choice == 1)
	{
		_ericCurrentX = 0;
		_ericCurrentY = 1;
		_baleogCurrentX = 1;
		_baleogCurrentY = 0;
		_olafCurrentX = 2;
		_olafCurrentY = 1;
	}
	else if (choice == 2)
	{
		_ericCurrentX = 0;
		_ericCurrentY = 1;
		_baleogCurrentX = 1;
		_baleogCurrentY = 1;
		_olafCurrentX = 2;
		_olafCurrentY = 0;
	}
}

void ui::keyControl(int choice)
{
	if (choice == 0)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_ericBox_X == 250)
			{
				_ericBox_X = 187;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_ericBox_X == 187)
			{
				_ericBox_X = 250;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_ericBox_Y == 734)
			{
				_ericBox_Y = 671;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_ericBox_Y == 671)
			{
				_ericBox_Y = 734;
			}
		}
	}
	else if (choice == 1)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_baleogBox_X == 532)
			{
				_baleogBox_X = 470;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_baleogBox_X == 470)
			{
				_baleogBox_X = 532;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_baleogBox_Y == 734)
			{
				_baleogBox_Y = 671;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_baleogBox_Y == 671)
			{
				_baleogBox_Y = 734;
			}
		}
	}
	else if (choice == 2)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_olafBox_X == 814)
			{
				_olafBox_X = 751;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_olafBox_X == 751)
			{
				_olafBox_X = 814;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_olafBox_Y == 734)
			{
				_olafBox_Y = 671;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_olafBox_Y == 671)
			{
				_olafBox_Y = 734;
			}
		}
	}
}
