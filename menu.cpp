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
	IMAGEMANAGER->addImage("������", "image/theLostVikings.bmp", 1000, 800, true, RGB(255, 0 ,255));
	IMAGEMANAGER->addImage("�޴�", "image/menu.bmp", 1000, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޴�����", "image/menuselect.bmp", 50, 50, true, RGB(255, 0, 255));

	_menuSelect_X = 320;
	_menuSelect_Y = 525;
	_menuGameStart = false;
	_opening = true;

	return S_OK;
}

void menu::release()
{
}

void menu::update()
{
	if (!_opening)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_menuSelect_Y == 590) _menuSelect_Y = 525;
			else _menuSelect_Y = 590;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_menuSelect_Y == 525) _menuGameStart = true;
			else PostQuitMessage(0);
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_opening = false;
		}
	}
}

void menu::render()
{
	if (_opening)
	{
		IMAGEMANAGER->findImage("������")->render(getMemDC());
	}
	else
	{
		IMAGEMANAGER->findImage("�޴�")->render(getMemDC());
		IMAGEMANAGER->findImage("�޴�����")->render(getMemDC(), _menuSelect_X, _menuSelect_Y);
	}
}
