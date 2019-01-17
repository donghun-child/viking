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
	_ericImage = IMAGEMANAGER->addFrameImage("eric", "image/eric.bmp", 0, 0, 1729, 2200, 11, 14, true, RGB(255, 0, 255));

	_eric_x = WINSIZEX / 2 + 100;
	_eric_y = WINSIZEY / 2;

	_ericState = ERIC_RIGHT_STOP;

	_eric_rc = RectMakeCenter(_eric_x, _eric_y, _ericImage->getFrameWidth(), _ericImage->getFrameHeight());

	int rightStop[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightStop", "eric", rightStop, 2, 6, true);

	int leftStop[] ={2,3};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftStop", "eric", leftStop, 2, 6, true);

	int rightMove[] = { 11,12,13,14,15,16,17,18 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightMove", "eric", rightMove, 8, 6, true);

	int leftMove[] = { 28,28,27,26,25,24,23,22 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftMove", "eric", leftMove, 8, 6, true);

	int rightDash[] = { 32, 33, 34, 35, 36, 37, 38, 39 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightDash", "eric", rightDash, 8, 10, false, rightDash, this);

	int leftDash[] = { 50, 49, 48, 47, 46, 45, 44, 43 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftDash", "eric", leftDash, 8, 10, false, leftDash, this);

	int rightJump[] = {76, 77, 78, 79};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightJump", "eric", rightJump, 4, 8, false, rightJump, this);

	int leftJump[] = {83, 82, 81, 80};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftJump", "eric", leftJump, 4, 8, false, leftJump, this);

	_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightStop");

	return S_OK;
}

void eric::release()
{
}

void eric::update(POINTFLOAT StagePos, int choice)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_ericState = ERIC_RIGHT_MOVE;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightMove");
		_ericMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_ericState = ERIC_RIGHT_STOP;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightStop");
		_ericMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_ericState = ERIC_LEFT_MOVE;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftMove");
		_ericMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_ericState = ERIC_LEFT_STOP;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftStop");
		_ericMotion->start();
	}


	_cameraPos = StagePos;

	if (choice == 2)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_eric_x < 2950)
			{
				_eric_x += 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_eric_x > 0)
			{
				_eric_x -= 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_eric_y > 0)
			{
				_eric_y -= 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_eric_y += 10;
		}
	}
}

void eric::render()
{
	Rectangle(getMemDC(), _eric_x - _cameraPos.x + WINSIZEX / 2, _eric_y - _cameraPos.y + WINSIZEY / 2, _eric_x + 50 - _cameraPos.x + WINSIZEX / 2, _eric_y + 50 - _cameraPos.y + WINSIZEY / 2);
	char str[128];
	sprintf_s(str, "에릭 확인 : %f ", _eric_x);
	TextOut(getMemDC(), 200, 70, str, strlen(str));
}

void eric::rightDash(void* obj)
{
	eric* e = (eric*)obj;
	e->setEricState(ERIC_RIGHT_STOP);
	e->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "rightStop"));
	e->getEricMotion()->start();
	
}

void eric::leftDash(void* obj)
{
	eric* e = (eric*)obj;
	e->setEricState(ERIC_LEFT_STOP);
	e->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "leftStop"));
	e->getEricMotion()->start();
}

void eric::rightJump(void* obj)
{
	eric* e = (eric*)obj;
	e->setEricState(ERIC_RIGHT_STOP);
	e->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "rightStop"));
	e->getEricMotion()->start();
}

void eric::leftJump(void* obj)
{
	eric* e = (eric*)obj;
	e->setEricState(ERIC_LEFT_STOP);
	e->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "leftStop"));
	e->getEricMotion()->start();
}
