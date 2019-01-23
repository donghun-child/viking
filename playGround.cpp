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
	SCENEMANAGER->update();
}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//===========================================================
	SCENEMANAGER->render();


	TIMEMANAGER->render(getMemDC());
	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

