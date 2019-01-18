#include "stdafx.h"
#include "olaf.h"


olaf::olaf()
{
}


olaf::~olaf()
{
}

HRESULT olaf::init()
{
	_olafimg = IMAGEMANAGER->addFrameImage("olaf", "image\\olaf.bmp", 0, 0, 1280, 2560, 8, 16, true, RGB(255, 0, 255));

	_olafDirection = OLAF_DIRECTION_RIGHT_STOP;

	_olaf_x = 100;
	_olaf_y = 100;

	_olaf_rc = RectMakeCenter(_olaf_x, _olaf_y, _olafimg->getFrameWidth(), _olafimg->getFrameHeight());


	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafRightStop", "olaf", rightStop, 1, 6, true);
	int rightShieldup[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafRightShield", "olaf", rightShieldup, 1, 6, true);
	int leftStop[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafLeftStop", "olaf", leftStop, 1, 6, true);
	int leftShieldup[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafRightShield", "olaf", leftShieldup, 1, 6, true);
	int rightMove[] = { 8, 9,10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafRightMove", "olaf", rightMove, 8, 6, true);
	int leftMove[] = { 23,22,21,20,19,18,17,16 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafLeftMove", "olaf", leftMove, 8, 6, true);
	int rightShieldUpMove[] = { 24,25,26,27,28,29,30,31 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafRightShieldUpMove", "olaf", rightShieldUpMove, 8, 6, true);
	int leftShieldUpMove[] = { 39,38,37,36,35,34,33,32 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafLeftShieldUpMove", "olaf", leftShieldUpMove, 8, 6, true);
	int SadariUp[] = { 33,34,35,36 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafSadariUp", "olaf", SadariUp, 4, 6, true);


	int rightPush[] = { 64,65,66,67 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafRightPush", "olaf", rightPush, 4, 6, true);
	int leftPush[] = { 68,69,70,71 };
	KEYANIMANAGER->addArrayFrameAnimation(_olafName, "olafLeftPush", "olaf", leftPush, 4, 6, true);

	_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafRightStop");

	_Wax = WINSIZEX / 2;
	_Way = 150;

	_wall = RectMakeCenter(_Wax, _Way, 30, 100);

	num = 0;
	_changeMode = false;

	return S_OK;
}

void olaf::release()
{
}

void olaf::update(POINTFLOAT StagePos, int choice)
{

	_cameraPos = StagePos;

	if (choice == 1)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_olaf_y > 0)
			{
				_olaf_y -= 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{

			_olaf_y += 10;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_olaf_x > 0)
			{
				_olaf_x -= 10;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_olaf_x < 2950)
			{
				_olaf_x += 10;
			}
		}
	}
	olafMovement();

	_olaf_rc = RectMakeCenter(_olaf_x, _olaf_y, _olafimg->getFrameWidth(), _olafimg->getFrameHeight());

	KEYANIMANAGER->update();
}

void olaf::render()
{
	Rectangle(getMemDC(), _olaf_x - _cameraPos.x + WINSIZEX / 2, _olaf_y - _cameraPos.y + WINSIZEY / 2, _olaf_x + 50 - _cameraPos.x + WINSIZEX / 2, _olaf_y + 50 - _cameraPos.y + WINSIZEY / 2);

	char str[128];
	sprintf_s(str, "상태확인 : %d    확인용 : %f", _olafDirection, _olaf_x);
	TextOut(getMemDC(), 200, 40, str, strlen(str));
}

void olaf::olafMovement()
{

	//==========================SHILED CHANGE==========================//
	if (_changeMode == false)
	{
		if (_olafDirection == OLAF_DIRECTION_RIGHT_STOP)
		{
			if (KEYMANAGER->isOnceKeyDown('F') || KEYMANAGER->isOnceKeyDown('D'))
			{
				_olafDirection = OLAF_DIRECTION_RIGHT_SHIELD;
				_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafRightShield");
				_olafMotion->start();
				_changeMode = true;
			}
		}
		else if (_olafDirection == OLAF_DIRECTION_LEFT_STOP)
		{
			if (KEYMANAGER->isOnceKeyDown('F') || KEYMANAGER->isOnceKeyDown('D'))
			{
				_olafDirection = OLAF_DIRECTION_LEFT_SHIELD;
				_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafLeftShield");
				_olafMotion->start();
				_changeMode = true;
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			//_olaf_x += 3;
			_olaf_rc = RectMakeCenter(_olaf_x, _olaf_y, _olafimg->getFrameWidth(), _olafimg->getFrameHeight());
			_olafDirection = OLAF_DIRECTION_RIGHT_MOVE;
			_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafRightMove");
			_olafMotion->start();
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _olafDirection == OLAF_DIRECTION_RIGHT_MOVE)
		{
			_olafDirection = OLAF_DIRECTION_RIGHT_STOP;
			_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafRightStop");
			_olafMotion->start();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			//_olaf_x -= 3;
			_olafDirection = OLAF_DIRECTION_LEFT_MOVE;
			_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafLeftMove");
			_olafMotion->start();
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _olafDirection == OLAF_DIRECTION_LEFT_MOVE)
		{
			_olafDirection = OLAF_DIRECTION_LEFT_STOP;
			_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafLeftStop");
			_olafMotion->start();
		}

	}
	else if (_changeMode == true)
	{
		if (_olafDirection == OLAF_DIRECTION_RIGHT_SHIELD)
		{

			if (KEYMANAGER->isOnceKeyDown('F') || KEYMANAGER->isOnceKeyDown('D'))
			{
				_olafDirection = OLAF_DIRECTION_RIGHT_STOP;
				_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafRightStop");
				_olafMotion->start();
				_changeMode = false;
			}
		}
		else if (_olafDirection == OLAF_DIRECTION_LEFT_SHIELD)
		{
			if (KEYMANAGER->isOnceKeyDown('F') || KEYMANAGER->isOnceKeyDown('D'))
			{
				_olafDirection = OLAF_DIRECTION_LEFT_STOP;
				_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafLeftStop");
				_olafMotion->start();
				_changeMode = false;
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			//	_olaf_x += 3;
			_olafDirection = OLAF_DIRECTION_RIGHT_SHIELD_UP_MOVE;
			_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafRightShieldUpMove");
			_olafMotion->start();
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _olafDirection == OLAF_DIRECTION_RIGHT_SHIELD_UP_MOVE)
		{
			_olafDirection = OLAF_DIRECTION_RIGHT_SHIELD;
			_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafRightStop");
			_olafMotion->start();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			//_olaf_x -= 3;
			_olafDirection = OLAF_DIRECTION_LEFT_SHIELD_UP_MOVE;
			_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafLeftShieldUpMove");
			_olafMotion->start();
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _olafDirection == OLAF_DIRECTION_LEFT_SHIELD_UP_MOVE)
		{
			_olafDirection = OLAF_DIRECTION_LEFT_SHIELD;
			_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafLeftStop");
			_olafMotion->start();
		}

	}


	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_olafDirection = OLAF_DIRECTION_RIGHT_WALL_PUSH;
		_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafRightPush");
		_olafMotion->start();
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_olafDirection = OLAF_DIRECTION_LEFT_WALL_PUSH;
		_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafLeftPush");
		_olafMotion->start();
	}
	//RECT rc;
	//if (IntersectRect(&rc, &_olaf_rc, &_wall))
	//{
	//	_olafDirection = OLAF_DIRECTION_RIGHT_WALL_PUSH;
	//	_olafMotion = KEYANIMANAGER->findAnimation(_olafName, "olafRightPush");
	//	_olafMotion->start();
	//}



	//=================================================================//

}
