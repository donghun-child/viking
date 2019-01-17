#include "stdafx.h"
#include "menu.h"


menu::menu()
{
}


menu::~menu()
{
}

HRESULT menu::init()
{
	IMAGEMANAGER->addImage("메뉴", "image/menu.bmp", 1000, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메뉴선택", "image/menuselect.bmp", 50, 50, true, RGB(255, 0, 255));

	_menuSelect_X = 320;
	_menuSelect_Y = 525;
	_menuQuit = false;
	return S_OK;
}

void menu::release()
{
}

void menu::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_menuSelect_Y == 590) _menuSelect_Y = 525;
		else _menuSelect_Y = 590;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (_menuSelect_Y == 525) _menuQuit = true;
		else PostQuitMessage(0);
	}

}

void menu::render()
{
	IMAGEMANAGER->findImage("메뉴")->render(getMemDC());
	IMAGEMANAGER->findImage("메뉴선택")->render(getMemDC(), _menuSelect_X, _menuSelect_Y);
}
