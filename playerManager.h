#pragma once
#include "gameNode.h"

class playerManager : public gameNode
{
private:
	RECT _rc[3];


public:
	playerManager();
	~playerManager();

	HRESULT init();
	void release();
	void update();
	void render();
};

