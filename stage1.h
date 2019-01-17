#pragma once
#include "gameNode.h"
#include "camera.h"
#include "playerManager.h"
#include "olaf.h"
#include "eric.h"
#include "player3.h"

class stage1 : public gameNode
{
private:
	camera* _camera;
	playerManager* _playerManager;

	bool _isPixel;

	int _choice;

public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();



};

