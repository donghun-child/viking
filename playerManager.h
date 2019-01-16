#pragma once
#include "gameNode.h"

enum Character
{
	BALEOG,
	ERIC,
	OLAF
};

class playerManager : public gameNode
{
private:
	RECT _rc[3];

	bool _isDebug;




public:
	playerManager();
	~playerManager();

	HRESULT init();
	void release();
	void update();
	void render();
};

