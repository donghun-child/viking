#pragma once
#include "gameNode.h"
class player3 : public gameNode
{

private:

	RECT _play_rc;
	float _play_x, _play_y;
	POINTFLOAT _cameraPos;


public:
	player3();
	~player3();


	HRESULT init();
	void release();
	void update(POINTFLOAT StagePos, int choice);
	void render();



	float getplayerX() { return _play_x; }
	float getplayerY() { return _play_y; }
};
