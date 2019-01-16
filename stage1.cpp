#include "stdafx.h"
#include "stage1.h"


stage1::stage1()
{
}


stage1::~stage1()
{
}

HRESULT stage1::init()
{
	IMAGEMANAGER->addImage("backGround", "image/map.bmp", 3000, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixel", "image/pixel.bmp", 3100, 2240, true, RGB(255, 0, 255));



	return S_OK;
}

void stage1::release()
{
}

void stage1::update()
{


}

void stage1::render()
{
	IMAGEMANAGER->render("backGround", getMemDC(), 0, 0);
	if (KEYMANAGER->isToggleKey(VK_SHIFT))
	{
		IMAGEMANAGER->render("pixel", getMemDC(), -50, 0);
	}
}