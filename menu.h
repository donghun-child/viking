#pragma once
#include "gameNode.h"

class menu : public gameNode
{
private:
	int _menuSelect_X, _menuSelect_Y;
	bool _menuGameStart;					//메뉴 게임 시작 불값

public:
	menu();
	~menu();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getMenuQuit() { return _menuGameStart; }
};

