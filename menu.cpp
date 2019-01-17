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
	IMAGEMANAGER->addImage("오프닝", "image/theLostVikings.bmp", 1000, 800, true, RGB(255, 0 ,255));
	IMAGEMANAGER->addImage("메뉴", "image/menu.bmp", 1000, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메뉴선택", "image/menuselect.bmp", 50, 50, true, RGB(255, 0, 255));

	_menuSelect_X = 320;
	_menuSelect_Y = 525;
	_imageAlphaValue = 0;

	_menuGameStart = false;
	_opening = true;					
	_padeIn = true;
	_padeOut = false;

	return S_OK;
}

void menu::release()
{
}

void menu::update()
{
	if (_padeIn)						//페이드 인 적용
	{
		if (_imageAlphaValue <= 254)
		{
			_imageAlphaValue += 1;
		}
		else							//끝나면 fasle
		{
			_padeIn = false;
		}
	}
	if (_padeOut)						//위와 동일
	{
		if (_imageAlphaValue > 0)
		{
			_imageAlphaValue -= 1;
		}
		else							//페이드 아웃시 끝나면 오프닝도 종료
		{
			_padeOut = false;
			if (!_opening)
			{
				_menuGameStart = true;
				return;
			}
			_opening = false;
			if (!_opening) _imageAlphaValue = 255;

		}
	}
	if (!_opening)						//오프닝 종료시 메뉴선택 키입력
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_menuSelect_Y == 590) _menuSelect_Y = 525;
			else _menuSelect_Y = 590;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_menuSelect_Y == 525) _padeOut = true;
			else PostQuitMessage(0);
		}
	}
	else								//오프닝 엔터시 페이드아웃 적용
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && !_padeIn)
		{
			_padeOut = true;
		}
	}
}

void menu::render()
{
	if (_opening)					
	{
		IMAGEMANAGER->findImage("오프닝")->alphaRender(getMemDC(), _imageAlphaValue);
	}
	else if(!_opening)
	{
		IMAGEMANAGER->findImage("메뉴")->alphaRender(getMemDC(), _imageAlphaValue);
		IMAGEMANAGER->findImage("메뉴선택")->alphaRender(getMemDC(), _menuSelect_X, _menuSelect_Y, _imageAlphaValue);
	}


}
