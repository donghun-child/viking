#pragma once
#include "gameNode.h"

class menu : public gameNode
{
private:
	int _menuSelect_X, _menuSelect_Y;
	int _imageAlphaValue;

	bool _padeIn, _padeOut;					//페이드 인, 페이드 아웃 효과 
	bool _menuGameStart;					//메뉴 게임 시작 불값
	bool _opening;
public:
	menu();
	~menu();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getMenuQuit() { return _menuGameStart; }
};

