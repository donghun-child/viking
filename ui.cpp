#include "stdafx.h"
#include "ui.h"


ui::ui()
{
}


ui::~ui()
{
}

HRESULT ui::init()
{
	IMAGEMANAGER->addImage("UI", "image/ui.bmp", 1000, 191, true, RGB(255, 0, 255));

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
}
