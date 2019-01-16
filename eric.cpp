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
	_ericimg = IMAGEMANAGER->addFrameImage("eric", "image\\eric.bmp", 0, 0, 1729, 2200, 11, 14, true, RGB(255, 0, 255));

	_ericDirection = ERIC_DIRECTION_RIGHT_STOP;

	_eric_x = 100;
	_eric_y = 100;

	_eric_rc = RectMakeCenter(_eric_x, _eric_y, _ericimg->getFrameWidth(), _ericimg->getFrameHeight());


	int rightStop[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation(_ericName, "ericRightStop", "eric", rightStop, 2, 6, true);
	int leftStop[] = { 2,3 };
	KEYANIMANAGER->addArrayFrameAnimation(_ericName, "ericLeftStop", "eric", leftStop, 2, 6, true);
	int rightMove[] = { 11,12,13,14,15,16,17,18};
	KEYANIMANAGER->addArrayFrameAnimation(_ericName, "ericRightMove", "eric", rightMove, 8, 6, true);
	int leftMove[] = { 28,28,27,26,25,24,23,22 };
	KEYANIMANAGER->addArrayFrameAnimation(_ericName, "ericLeftMove", "eric", leftMove, 8, 6, true);

	_ericMotion = KEYANIMANAGER->findAnimation(_ericName, "ericRightStop");

	_changeMode = false;


	return S_OK;
}

HRESULT eric::init(string name)
{
	_ericName = name;
	init();
	return S_OK;
}

void eric::release()
{
}

void eric::update()
{
}

void eric::render()
{
}

void eric::ericMovement()
{
}

