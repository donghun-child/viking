#pragma once
#include "gameNode.h"

enum VikingCharacter
{
	VIKING_ERIC,
	VIKING_OLAF,
	VIKING_BALEOG
};

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

	float _camera_X, _camera_Y;					// Ä«¸Þ¶ó X,Y
	int _viking_Pic;
	bool _back;

public:
	camera();
	~camera();

	HRESULT init(float x, float y, float speed);
	void release();
	void update();
	void render();
	
	float getCameraX() { return _camera_X;}				
	float getCameraY() { return _camera_Y; }
};

