#pragma once
#include "gameNode.h"
#include "playerManager.h"


class stage1 : public gameNode
{
private:
	playerManager* _playerManager;

	bool _isPixel;


public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();

	void viewPixel();
	



};

