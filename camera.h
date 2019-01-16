#pragma once
#include "gameNode.h"
struct tagViking
{
	float x, y;
	float speed;
};

class camera : public gameNode
{
private:
	tagViking _eric;
	tagViking _olaf;
	tagViking _baleog;

	float _camera_X, _camera_Y;

	bool _eric_Pic, _olaf_Pic, _baleog_Pic;



public:
	camera();
	~camera();

	HRESULT init();
	void release();
	void update();
	void render();
	
	float getCameraX() { return _camera_X;}
	float getCameraY() { return _camera_Y; }
};

