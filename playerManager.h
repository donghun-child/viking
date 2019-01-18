#pragma once
#include "gameNode.h"
#include "baleog.h"
#include "olaf.h"
#include "eric.h"

enum Character
{
	ERIC,
	BALEOG,
	OLAF
};

class camera;

class playerManager : public gameNode
{
private:
	camera* _camera;

	RECT _rc[3];

	bool _isDebug;

	baleog* _baleog;
	eric* _eric;
	olaf* _olaf;

	float _x[3];
	float _y[3];
	float _prove_X[3];
	float _prove_Y[3];
	float _viewX[3];
	float _viewY[3];

	float _gravity;
	float _jumpPower;
	bool _isJump;
	float _jumpStartPos;
	int _jumpCount;
	//Á¡ÇÁ È½¼ö
	int _jumpNum;

public:
	playerManager();
	~playerManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//ÇÈ¼¿Ãæµ¹
	void pixelCollisionGreen();
	void pixelCollisionYellow();
	void pixelCollisionEmerald();

	//Áß·Â
	void gravity(int select);

	void getCameraAddressLink(camera* camera) { _camera = camera; }

	float getEricX() { return _x[ERIC]; }
	float getEricY() { return _y[ERIC]; }
	float getBalogX() { return _x[BALEOG]; }
	float getBalogY() { return _y[BALEOG]; }
	float getOlafX() { return _x[OLAF]; }
	float getOlafY() { return _y[OLAF]; }

	void setEricX(float x) { _x[ERIC] = x; }
	void setEricY(float y) { _y[ERIC] = y; }
	void setBalogX(float x) { _x[BALEOG] = x; }
	void setBalogY(float y) { _y[BALEOG] = y; }
	void setOlafX(float x) { _x[OLAF] = x; }
	void setOlafY(float y) { _y[OLAF] = y; }

	bool getIsjump() { return _isJump; }

};

