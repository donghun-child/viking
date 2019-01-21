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
	IMAGEMANAGER->addImage("life", "image/life.bmp", 25, 25, true, RGB(255, 0, 255));


	_ericCurrentX = _ericCurrentY = 0;
	_baleogCurrentX = 1;
	_baleogCurrentY = 1;
	_olafCurrentX = 2;
	_olafCurrentY = 1;

	return S_OK;
}

void ui::release()
{
}

void ui::update()
{
}

void ui::render()
{
	IMAGEMANAGER->findImage("UI")->render(getMemDC(), 0, 609);
	IMAGEMANAGER->findImage("profile")->frameRender(getMemDC(), 62, 671, _ericCurrentX, _ericCurrentY);
	IMAGEMANAGER->findImage("profile")->frameRender(getMemDC(), 344, 671, _baleogCurrentX, _baleogCurrentY);
	IMAGEMANAGER->findImage("profile")->frameRender(getMemDC(), 625, 671, _olafCurrentX, _olafCurrentY);
	IMAGEMANAGER->findImage("life")->render(getMemDC(), 100, 600);


	//char str[128];
	//sprintf_s(str, "√ ¿ÃΩ∫ : %d", _choice);
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
