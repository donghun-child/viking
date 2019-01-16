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
	_baleogPlayer.baleogImage = IMAGEMANAGER->addFrameImage("벨로그", "image/Baleog.bmp", 1200, 1950, 8, 13, true, RGB(255, 0, 255));
	_baleogPlayer.x = BALEOG_X;
	_baleogPlayer.y = BALEOG_Y;
	_baleogPlayer.speed = BALEOG_SPEED;
	_baleogPlayer.baleogRc = RectMakeCenter(_baleogPlayer.x, _baleogPlayer.y, _baleogPlayer.baleogImage->getFrameWidth(), _baleogPlayer.baleogImage->getFrameHeight());

	_baleogState = BALEOG_RIGHT_STOP; //처음엔 오른쪽 기본상태로

	int rightStop[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation(_name, "rightStop", "벨로그", rightStop, 2, 6, true);

	int leftStop[] = { 2,3 };
	KEYANIMANAGER->addArrayFrameAnimation(_name, "leftStop", "벨로그", leftStop, 2, 6, true);

	int rightMove[] = {8, 9, 10, 11, 12, 13, 14, 15};
	KEYANIMANAGER->addArrayFrameAnimation(_name, "rightMove", "벨로그", rightMove, 8, 10, true);

	int leftMove[] = { 23, 22, 21, 20, 19, 18, 17, 16 };
	KEYANIMANAGER->addArrayFrameAnimation(_name, "leftMove", "벨로그", leftMove, 8, 10, true);

	int rightArrowAttack[] = { 24, 25, 26, 27, 28, 29, 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation(_name, "rightArrowAttack", "벨로그", rightArrowAttack, 8, 10, false, rightFire, this);

	int leftArrowAttack[] = { 39, 38, 37, 36, 35, 34, 33, 32 };
	KEYANIMANAGER->addArrayFrameAnimation(_name, "leftArrowAttack", "벨로그", leftArrowAttack, 8, 10, false, leftFire, this);

	int rightSwordAttackOne[] = {40, 41, 42, 43};
	KEYANIMANAGER->addArrayFrameAnimation(_name, "rightSwordAttackOne", "벨로그" , rightSwordAttackOne, 4, 10, false, rightFire, this);

	int rightSwordAttackTwo[] = {44, 45, 46, 47};
	KEYANIMANAGER->addArrayFrameAnimation(_name, "rightSwordAttackTwo", "벨로그", rightSwordAttackTwo, 4, 10, false, rightFire, this);

	int leftSwordAttackOne[] = {55, 54, 53, 52};
	KEYANIMANAGER->addArrayFrameAnimation(_name, "leftSwordAttackOne", "벨로그", leftSwordAttackOne, 4, 10, false, leftFire, this);

	int leftSwordAttackTwo[] = {51, 50, 49, 48};
	KEYANIMANAGER->addArrayFrameAnimation(_name, "leftSwordAttackTwo", "벨로그", leftSwordAttackTwo, 4, 10, false, leftFire, this);

	return S_OK;
}

HRESULT baleog::init(string name)
{
	_name = name;
	init();
	return S_OK;
}

void baleog::release()
{
}

void baleog::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_baleogState = BALEOG_RIGHT_MOVE; //오른쪽 움직임 상태로 전환
		_baleogMotion = KEYANIMANAGER->findAnimation(_name, "rightMove"); //모션 바꿔주고
		_baleogMotion->start(); //모션 시작
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_baleogState = BALEOG_RIGHT_STOP;
		_baleogMotion = KEYANIMANAGER->findAnimation(_name, "rightStop");
		_baleogMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_baleogState = BALEOG_LEFT_MOVE;
		_baleogMotion = KEYANIMANAGER->findAnimation(_name, "leftMove");
		_baleogMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_baleogState = BALEOG_LEFT_STOP;
		_baleogMotion = KEYANIMANAGER->findAnimation(_name, "leftStop");
		_baleogMotion->start();
	}


	switch (_baleogState)
	{
	case BALEOG_RIGHT_MOVE:
		_baleogPlayer.x += _baleogPlayer.speed;
		break;
	case BALEOG_LEFT_MOVE:
		_baleogPlayer.x -= _baleogPlayer.speed;
		break;
	case BALEOG_RIGHT_ARROW_ATTACK:
		break;
	}


}

void baleog::render()
{
}

void baleog::rightFire(void* obj)
{
	baleog* baleogPlayer = (baleog*)obj;
	baleogPlayer->setBaleogState(BALEOG_RIGHT_STOP);
	baleogPlayer->setBaleogMotion(KEYANIMANAGER->findAnimation(baleogPlayer->getName(), "rightStop"));
	baleogPlayer->getBaleogMotion()->start();
}

void baleog::leftFire(void * obj)
{
	baleog* baleogPlayer = (baleog*)obj;
	baleogPlayer->setBaleogState(BALEOG_LEFT_STOP);
	baleogPlayer->setBaleogMotion(KEYANIMANAGER->findAnimation(baleogPlayer->getName(), "leftStop"));
	baleogPlayer->getBaleogMotion()->start();
}


