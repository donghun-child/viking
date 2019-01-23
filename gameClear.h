#pragma once
#include "gameNode.h"

class gameClear : public gameNode
{


public:
	gameClear();
	~gameClear();

	HRESULT init();
	void release();
	void update();
	void render();
};

