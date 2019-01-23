#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);

	_sound = new sound;
	_sound->init();

	_menu = new menu;
	_menu->init();
	SCENEMANAGER->addScene("menu", _menu);
	_stage1 = new stage1;
	SCENEMANAGER->addScene("stage1", _stage1);

	_gameOver = new gameOver;
	SCENEMANAGER->addScene("gameOver", _gameOver);

	_gameClear = new gameClear;
	SCENEMANAGER->addScene("gameClear", _gameClear);

	SCENEMANAGER->changeScene("stage1");

	_gameOverCount = 0;
	_isGameOver = false;
	_isGameClear = false;
	
	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	SAFE_DELETE(_sound);

	SCENEMANAGER->release();

}


void playGround::update()
{
	gameNode::update();
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) PostQuitMessage(0);

	

	if (_menu->getMenuQuit())
	{
		SCENEMANAGER->changeScene("stage1");
	}
	
	if (_isGameOver == false)
	{
		if (_stage1->getPlayerManager()->getEricDead() == true &&
			_stage1->getPlayerManager()->getBaleogDead() == true &&
			_stage1->getPlayerManager()->getOlafDead() == true)
		{
			_gameOverCount++;
			if (_gameOverCount == 80)
			{
				_isGameOver = true;
				SCENEMANAGER->changeScene("gameOver");
			}
		}
	}
	if (_isGameClear == false)
	{
		if (IntersectRect(&temp, &_stage1->getPlayerManager()->getEricRect(), &_end) && IntersectRect(&temp, &_stage1->getPlayerManager()->getBaleogRect(), &_end) && IntersectRect(&temp, &_stage1->getPlayerManager()->getOlafRect(), &_end))
		{
	
			SCENEMANAGER->changeScene("gameClear");
			_isGameClear = true;
		}
	}
	if (_isGameClear == false)
	{
		_end = RectMake(2580 - _stage1->getPlayerManager()->getCamera()->getCameraX(), 1130 - _stage1->getPlayerManager()->getCamera()->getCameraY(), 130, 130);
	}

	SCENEMANAGER->update();

	


}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//===========================================================
	SCENEMANAGER->render();
	//Rectangle(getMemDC(), _end);


	TIMEMANAGER->render(getMemDC());
	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

