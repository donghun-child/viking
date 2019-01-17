#pragma once
#include "gameNode.h"
class eric : public gameNode
{

private:

	RECT _eric_rc;
	float _eric_x, _eric_y;
	POINTFLOAT _cameraPos;

public:
	eric();
	~eric();

	HRESULT init();
	void release();
	void update(POINTFLOAT StagePos, int choice);
	void render();


	float getplayerX() { return _eric_x; }
	float getplayerY() { return _eric_y; }
};

