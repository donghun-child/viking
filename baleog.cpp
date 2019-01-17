#include "stdafx.h"
#include "baleog.h"


baleog::baleog()
{
}


baleog::~baleog()
{
}

HRESULT baleog::init()
{
	_baleogPlayer.baleogImage = IMAGEMANAGER->addFrameImage("벨로그", "image/Baleog.bmp", 0, 0, 1200, 1950, 8, 13, true, RGB(255, 0, 255));
	_baleogPlayer.x = BALEOG_X;
	_baleogPlayer.y = BALEOG_Y;
	_baleogPlayer.speed = BALEOG_SPEED;
	_baleogPlayer.baleogRc = RectMakeCenter(_baleogPlayer.x, _baleogPlayer.y, _baleogPlayer.baleogImage->getFrameWidth(), _baleogPlayer.baleogImage->getFrameHeight());

	_baleogState = BALEOG_RIGHT_STOP; //처음엔 오른쪽 기본상태로

	int rightStop[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "rightStop", "벨로그", rightStop, 2, 6, true);

	int leftStop[] = { 2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "leftStop", "벨로그", leftStop, 2, 6, true);

	int rightMove[] = { 8, 9, 10, 11, 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "rightMove", "벨로그", rightMove, 8, 10, true);

	int leftMove[] = { 23, 22, 21, 20, 19, 18, 17, 16 };
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "leftMove", "벨로그", leftMove, 8, 10, true);

	int rightArrowAttack[] = { 24, 25, 26, 27, 28, 29, 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "rightArrowAttack", "벨로그", rightArrowAttack, 8, 10, false, rightFire, this);

	int leftArrowAttack[] = { 39, 38, 37, 36, 35, 34, 33, 32 };
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "leftArrowAttack", "벨로그", leftArrowAttack, 8, 10, false, leftFire, this);

	int rightSwordAttackOne[] = { 40, 41, 42, 43 };
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "rightSwordAttackOne", "벨로그", rightSwordAttackOne, 4, 10, false, rightFire, this);

	int rightSwordAttackTwo[] = { 44, 45, 46, 47 };
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "rightSwordAttackTwo", "벨로그", rightSwordAttackTwo, 4, 10, false, rightFire, this);

	int leftSwordAttackOne[] = { 55, 54, 53, 52 };
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "leftSwordAttackOne", "벨로그", leftSwordAttackOne, 4, 10, false, leftFire, this);

	int leftSwordAttackTwo[] = { 51, 50, 49, 48 };
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "leftSwordAttackTwo", "벨로그", leftSwordAttackTwo, 4, 10, false, leftFire, this);

	_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightStop");

	IMAGEMANAGER->addFrameImage("화살", "image/bullet.bmp", 85, 20, 5, 2, true, RGB(255, 0, 255));
	_arrow = new arrow;
	_arrow->init("화살", 10, WINSIZEX);

	_rndAttack = RND->getInt(2);
	return S_OK;
}

void baleog::release()
{
}

void baleog::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _baleogState != BALEOG_LEFT_ARROW_ATTACK && _baleogState != BALEOG_RIGHT_ARROW_ATTACK)
	{
		_baleogState = BALEOG_RIGHT_MOVE; //오른쪽 움직임 상태로 전환

		_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightMove"); //모션 바꿔주고
		_baleogMotion->start(); //모션 시작
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _baleogState != BALEOG_LEFT_MOVE && _baleogState != BALEOG_LEFT_ARROW_ATTACK && _baleogState != BALEOG_RIGHT_ARROW_ATTACK && _baleogState != BALEOG_LEFT_SWORD_ATTACK_ONE && _baleogState != BALEOG_LEFT_SWORD_ATTACK_TWO && _baleogState != BALEOG_RIGHT_SWORD_ATTACK_ONE && _baleogState != BALEOG_RIGHT_SWORD_ATTACK_TWO)
	{
		_baleogState = BALEOG_RIGHT_STOP;
		_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightStop");
		_baleogMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _baleogState != BALEOG_LEFT_ARROW_ATTACK && _baleogState != BALEOG_RIGHT_ARROW_ATTACK)
	{
		_baleogState = BALEOG_LEFT_MOVE;

		_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftMove");
		_baleogMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _baleogState != BALEOG_RIGHT_MOVE && _baleogState != BALEOG_LEFT_ARROW_ATTACK && _baleogState != BALEOG_RIGHT_ARROW_ATTACK && _baleogState != BALEOG_LEFT_SWORD_ATTACK_ONE && _baleogState != BALEOG_LEFT_SWORD_ATTACK_TWO && _baleogState != BALEOG_RIGHT_SWORD_ATTACK_ONE && _baleogState != BALEOG_RIGHT_SWORD_ATTACK_TWO)
	{
		_baleogState = BALEOG_LEFT_STOP;
		_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftStop");
		_baleogMotion->start();
	}

	//if (_arrow->getVArrow().size() == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('S') && (_baleogState == BALEOG_LEFT_STOP || _baleogState == BALEOG_LEFT_MOVE || _baleogState == BALEOG_RIGHT_STOP || _baleogState == BALEOG_RIGHT_MOVE))
		{
			if (_baleogState == BALEOG_RIGHT_STOP || _baleogState == BALEOG_RIGHT_MOVE)
			{
				_baleogState = BALEOG_RIGHT_ARROW_ATTACK;
				_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightArrowAttack");
				_baleogMotion->start();
				if (_baleogState == BALEOG_RIGHT_ARROW_ATTACK)
				{
					_arrow->arrowFire(_baleogPlayer.x, _baleogPlayer.y + 20, 10, PI2);
					_arrow->setArrowState(ARROW_RIGHT_FIRE);
				}

			}
			else if (_baleogState == BALEOG_LEFT_STOP || _baleogState == BALEOG_LEFT_MOVE)
			{
				_baleogState = BALEOG_LEFT_ARROW_ATTACK;
				_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftArrowAttack");
				_baleogMotion->start();
				if (_baleogState == BALEOG_LEFT_ARROW_ATTACK)
				{
					_arrow->arrowFire(_baleogPlayer.x, _baleogPlayer.y + 20, 10, PI);
					_arrow->setArrowState(ARROW_LEFT_FIRE);
				}
			}


		}
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_baleogState == BALEOG_RIGHT_STOP || _baleogState == BALEOG_RIGHT_MOVE)
		{
			_rndAttack = RND->getInt(2);

			if (_rndAttack == 0)
			{
				_baleogState = BALEOG_RIGHT_SWORD_ATTACK_ONE;
				_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightSwordAttackOne");
				_baleogMotion->start();
			}
			else if (_rndAttack == 1)
			{
				_baleogState = BALEOG_RIGHT_SWORD_ATTACK_TWO;
				_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightSwordAttackTwo");
				_baleogMotion->start();
			}
		}
		else if (_baleogState == BALEOG_LEFT_STOP || _baleogState == BALEOG_LEFT_MOVE)
		{
			_rndAttack = RND->getInt(2);

			if (_rndAttack == 0)
			{
				_baleogState = BALEOG_LEFT_SWORD_ATTACK_ONE;
				_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftSwordAttackOne");
				_baleogMotion->start();
			}
			else if (_rndAttack == 1)
			{
				_baleogState = BALEOG_LEFT_SWORD_ATTACK_TWO;
				_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftSwordAttackTwo");
				_baleogMotion->start();
			}
		}
	}

	_arrow->update();

	_baleogPlayer.baleogRc = RectMakeCenter(_baleogPlayer.x, _baleogPlayer.y, _baleogPlayer.baleogImage->getFrameWidth(), _baleogPlayer.baleogImage->getFrameHeight());

	KEYANIMANAGER->update();

}

void baleog::render()
{
	char str[128];
	sprintf_s(str, "벨로그 상태 : %d", _baleogState);
	TextOut(getMemDC(), 100, 100, str, strlen(str));

	sprintf_s(str, "벨로그 스피드 : %d", _baleogPlayer.speed);
	TextOut(getMemDC(), 100, 120, str, strlen(str));

	sprintf_s(str, "랜덤어택 : %d", _rndAttack);
	TextOut(getMemDC(), 100, 140, str, strlen(str));

	_baleogPlayer.baleogImage->aniRender(getMemDC(), _baleogPlayer.baleogRc.left, _baleogPlayer.baleogRc.top, _baleogMotion);
	_arrow->render();
}

void baleog::rightFire(void* obj)
{
	baleog* baleogPlayer = (baleog*)obj;
	baleogPlayer->setBaleogState(BALEOG_RIGHT_STOP);
	baleogPlayer->setBaleogMotion(KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightStop"));
	baleogPlayer->getBaleogMotion()->start();
}

void baleog::leftFire(void * obj)
{
	baleog* baleogPlayer = (baleog*)obj;
	baleogPlayer->setBaleogState(BALEOG_LEFT_STOP);
	baleogPlayer->setBaleogMotion(KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftStop"));
	baleogPlayer->getBaleogMotion()->start();
}


