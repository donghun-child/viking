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

	int upMove[] = {56, 57, 58, 59};
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "upMove", "벨로그", upMove, 4, 10, true);

	int downMove[] = {59, 58, 57, 56};
	KEYANIMANAGER->addArrayFrameAnimation("벨로그캐릭터", "downMove", "벨로그", downMove, 4, 10, true);

	_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightStop");

	IMAGEMANAGER->addFrameImage("화살", "image/bullet.bmp", 85, 20, 5, 2, true, RGB(255, 0, 255));
	_arrow = new arrow;
	_arrow->init("화살", 0, 600);

	_rndAttack = RND->getInt(2);

	_arrowFireStop = false;
	_isLadderColision = false;

	return S_OK;
}

void baleog::release()
{
}

void baleog::update(float baleogX, float baleogY)
{
	//키셋팅
	keySetting(baleogX, baleogY);

	//화살공격
	arrowAttack();

	//검공격
	swordAttack();

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

	sprintf_s(str, "프레임이미지 x좌표 : %d", _baleogMotion->getFramePos().x);
	TextOut(getMemDC(), 100, 140, str, strlen(str));

	_baleogPlayer.baleogImage->aniRender(getMemDC(), _baleogPlayer.baleogRc.left, _baleogPlayer.baleogRc.top, _baleogMotion);
	_arrow->render();
}

void baleog::keySetting(float baleogX, float baleogY)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _baleogState != BALEOG_LEFT_ARROW_ATTACK && _baleogState != BALEOG_RIGHT_ARROW_ATTACK)
	{
		_baleogState = BALEOG_RIGHT_MOVE; //오른쪽 움직임 상태로 전환
		_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightMove"); //모션 바꿔주고
		_baleogMotion->start(); //모션 시작
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _baleogState != BALEOG_LEFT_MOVE && _baleogState != BALEOG_LEFT_ARROW_ATTACK && _baleogState != BALEOG_RIGHT_ARROW_ATTACK && _baleogState != BALEOG_LEFT_SWORD_ATTACK_ONE && _baleogState != BALEOG_LEFT_SWORD_ATTACK_TWO && _baleogState != BALEOG_RIGHT_SWORD_ATTACK_ONE && _baleogState != BALEOG_RIGHT_SWORD_ATTACK_TWO && _baleogState != BALEOG_UP_MOVE && _baleogState != BALEOG_DOWN_MOVE)
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
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _baleogState != BALEOG_RIGHT_MOVE && _baleogState != BALEOG_LEFT_ARROW_ATTACK && _baleogState != BALEOG_RIGHT_ARROW_ATTACK && _baleogState != BALEOG_LEFT_SWORD_ATTACK_ONE && _baleogState != BALEOG_LEFT_SWORD_ATTACK_TWO && _baleogState != BALEOG_RIGHT_SWORD_ATTACK_ONE && _baleogState != BALEOG_RIGHT_SWORD_ATTACK_TWO && _baleogState != BALEOG_UP_MOVE && _baleogState != BALEOG_DOWN_MOVE)
	{
		_baleogState = BALEOG_LEFT_STOP;
		_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftStop");
		_baleogMotion->start();
	}

	//사다리 충돌했을경우만 오르락 내리락 하기위함.
	if (_isLadderColision == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_baleogState = BALEOG_UP_MOVE;
			_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "upMove");
			_baleogMotion->start();
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_UP) && _baleogState != BALEOG_RIGHT_MOVE && _baleogState != BALEOG_LEFT_MOVE)
		{
			_baleogMotion->pause();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_baleogState = BALEOG_DOWN_MOVE;
			_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "downMove");
			_baleogMotion->start();
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && _baleogState != BALEOG_RIGHT_MOVE && _baleogState != BALEOG_LEFT_MOVE)
		{
			_baleogMotion->pause();
		}
	}


	switch (_baleogState)
	{
	case BALEOG_RIGHT_MOVE:
		baleogX += _baleogPlayer.speed;
		break;
	case BALEOG_LEFT_MOVE:
		baleogX -= _baleogPlayer.speed;
		break;
	case BALEOG_UP_MOVE:
		if (KEYMANAGER->isStayKeyDown(VK_UP)) baleogY -= _baleogPlayer.speed;
		break;
	case BALEOG_DOWN_MOVE:
		if (KEYMANAGER->isStayKeyDown(VK_DOWN)) baleogY += _baleogPlayer.speed;
		break;
	}

}

void baleog::arrowAttack()
{
	//화살공격
	if (_arrow->getVArrow().size() == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('S') && (_baleogState == BALEOG_LEFT_STOP || _baleogState == BALEOG_LEFT_MOVE || _baleogState == BALEOG_RIGHT_STOP || _baleogState == BALEOG_RIGHT_MOVE))
		{
			if (_baleogState == BALEOG_RIGHT_STOP || _baleogState == BALEOG_RIGHT_MOVE)
			{
				_baleogState = BALEOG_RIGHT_ARROW_ATTACK;
				_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightArrowAttack");
				_baleogMotion->start();
			}
			else if (_baleogState == BALEOG_LEFT_STOP || _baleogState == BALEOG_LEFT_MOVE)
			{
				_baleogState = BALEOG_LEFT_ARROW_ATTACK;
				_baleogMotion = KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftArrowAttack");
				_baleogMotion->start();
			}
	
		}
		else if (KEYMANAGER->isOnceKeyUp('S'))
		{
			_arrowFireStop = false;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			if (_baleogMotion->getFramePos().x == 750 && _baleogState == BALEOG_RIGHT_ARROW_ATTACK)
			{
				_baleogMotion->pause();
				_arrowFireStop = true;
			}
			else if (_baleogMotion->getFramePos().x == 300 && _baleogState == BALEOG_LEFT_ARROW_ATTACK)
			{
				_baleogMotion->pause();
				_arrowFireStop = true;
			}
		}
		else if (_arrowFireStop == false)
		{
			arrowFire();
		}
	}
}

void baleog::swordAttack()
{
	//검공격
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_rndAttack = RND->getInt(2); //랜덤공격값 받기위함
		if (_baleogState == BALEOG_RIGHT_STOP || _baleogState == BALEOG_RIGHT_MOVE)
		{
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
}

void baleog::arrowFire()
{
	if (_baleogState == BALEOG_RIGHT_ARROW_ATTACK)
	{
		if (_baleogMotion->getFramePos().x == 750)
		{
			_arrow->arrowFire(_baleogPlayer.x, _baleogPlayer.y + 20, 10, PI2);
			_arrow->setArrowState(ARROW_RIGHT_FIRE);
			_baleogMotion->resume();
		}
	}
	else if (_baleogState == BALEOG_LEFT_ARROW_ATTACK)
	{
		if (_baleogMotion->getFramePos().x == 300)
		{
			_arrow->arrowFire(_baleogPlayer.x, _baleogPlayer.y + 20, 10, PI);
			_arrow->setArrowState(ARROW_LEFT_FIRE);
			_baleogMotion->resume();
		}
	}
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


