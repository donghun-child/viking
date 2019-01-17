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
	if (_padeIn)						//���̵� �� ����
	{
		if (_imageAlphaValue <= 254)
		{
			_imageAlphaValue += 1;
		}
		else							//������ fasle
		{
			_padeIn = false;
		}
	}
	if (_padeOut)						//���� ����
	{
		if (_imageAlphaValue > 0)
		{
			_imageAlphaValue -= 1;
		}
		else							//���̵� �ƿ��� ������ �����׵� ����
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
	if (!_opening)						//������ ����� �޴����� Ű�Է�
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
	else								//������ ���ͽ� ���̵�ƿ� ����
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
		IMAGEMANAGER->findImage("������")->alphaRender(getMemDC(), _imageAlphaValue);
	}
	else if(!_opening)
	{
		IMAGEMANAGER->findImage("�޴�")->alphaRender(getMemDC(), _imageAlphaValue);
		IMAGEMANAGER->findImage("�޴�����")->alphaRender(getMemDC(), _menuSelect_X, _menuSelect_Y, _imageAlphaValue);
	}


}
