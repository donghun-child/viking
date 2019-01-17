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

	_eric_X = WINSIZEX / 2 + 100;
	_eric_Y = WINSIZEY / 2;

	_start_X = _eric_X;
	_start_Y = _eric_Y;

	_ericState = ERIC_RIGHT_STOP;

	_eric_rc = RectMakeCenter(_eric_X, _eric_Y, _ericImage->getFrameWidth(), _ericImage->getFrameHeight());

	int rightStop[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightStop", "eric", rightStop, 2, 6, true);

	int leftStop[] ={2,3};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftStop", "eric", leftStop, 2, 6, true);

	int rightMove[] = { 11,12,13,14,15,16,17,18 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightMove", "eric", rightMove, 8, 6, true);

	int leftMove[] = { 28,28,27,26,25,24,23,22 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftMove", "eric", leftMove, 8, 6, true);

	int rightDashArr[] = { 33, 34, 35, 36, 37, 38, 39, 40 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightDash", "eric", rightDashArr, 8, 10, false, rightDash, this);

	int leftDashArr[] = { 51, 50, 49, 48, 47, 46, 45, 44 };
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftDash", "eric", leftDashArr, 8, 10, false, leftDash, this);

	int rightJumpArr[] = {77, 78, 79, 80};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "rightJump", "eric", rightJumpArr, 4, 8, false, rightJump, this);

	int leftJumpArr[] = {84, 83, 82, 81};
	KEYANIMANAGER->addArrayFrameAnimation("ericName", "leftJump", "eric", leftJumpArr, 4, 8, false, leftJump, this);

	_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightStop");

	_ericJump = new jump;
	_ericJump->init();
	return S_OK;
}

void eric::release()
{
	SAFE_DELETE(_ericJump);
}

void eric::update(POINTFLOAT StagePos, int choice)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_ericState = ERIC_RIGHT_MOVE;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightMove");
		_ericMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _ericState != ERIC_LEFT_MOVE)
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
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _ericState != ERIC_RIGHT_MOVE)
	{
		_ericState = ERIC_LEFT_STOP;
		_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftStop");
		_ericMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_ericJump->Jumping(&_eric_X, &_eric_Y, &_start_X, &_start_Y, 10.0f, 0.5f);
		if (_ericState == ERIC_RIGHT_STOP || _ericState == ERIC_RIGHT_MOVE)
		{
			_ericState = ERIC_RIGHT_JUMP;
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightJump");
			_ericMotion->start();
		}
		else if (_ericState == ERIC_LEFT_STOP || _ericState == ERIC_LEFT_MOVE)
		{
			_ericState = ERIC_LEFT_JUMP;
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftJump");
			_ericMotion->start();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_ericState == ERIC_RIGHT_STOP || _ericState == ERIC_RIGHT_MOVE)
		{
			_ericState = ERIC_RIGHT_DASH;
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "rightDash");
			_ericMotion->start();
		}

		else if (_ericState == ERIC_LEFT_STOP || _ericState == ERIC_LEFT_MOVE)
		{
			_ericState = ERIC_LEFT_DASH;
			_ericMotion = KEYANIMANAGER->findAnimation("ericName", "leftDash");
			_ericMotion->start();
		}
	}

	_ericJump->update();
	_cameraPos = StagePos;
	KEYANIMANAGER->update();
	if (choice == 2)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_eric_X < 2950)
			{
				_eric_X += 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_eric_X > 0)
			{
				_eric_X -= 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_eric_Y > 0)
			{
				_eric_Y -= 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_eric_Y += 10;
		}
	}
}

void eric::render()
{
	Rectangle(getMemDC(), _eric_X - _cameraPos.x + WINSIZEX / 2, _eric_Y - _cameraPos.y + WINSIZEY / 2, _eric_X + 50 - _cameraPos.x + WINSIZEX / 2, _eric_Y + 50 - _cameraPos.y + WINSIZEY / 2);
	char str[128];
	sprintf_s(str, "에릭 확인 : %f ", _eric_X);
	TextOut(getMemDC(), 200, 70, str, strlen(str));

	_ericImage->aniRender(getMemDC(), _eric_X, _eric_Y, _ericMotion);
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
