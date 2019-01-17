#pragma once
#include "gameNode.h"

enum Character
{
	BALEOG,
	ERIC,
	OLAF
};

class camera;

class playerManager : public gameNode
{
private:
	camera* _camera;

	RECT _rc[3];

	bool _isDebug;


	int _x[3];
	int _y[3];
	int _prove_X[3];
	int _prove_Y[3];


public:
	playerManager();
	~playerManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void pixelCollisionGreen();
	void pixelCollisionYellow();
	void pixelCollisionEmerald();

	void getCameraAddressLink(camera* camera) { _camera = camera; }
};

