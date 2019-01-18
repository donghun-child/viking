#pragma once
#include "gameNode.h"
#include "camera.h"
#include "playerManager.h"

#define CAMERA_CHANGING_SPEED 1.5f

class stage1 : public gameNode
{
private:
	camera* _camera;
	playerManager* _playerManager;

	bool _isPixel;

	int _choice;
	int _jumpCount;

	bool _changing;
	int _count;

	float elapsedTime;
	float moveSpeed;

	//카메라
	POINTFLOAT _orizin;
	POINTFLOAT _new;
	float _Distance;
	float _angle;
	float _speed;
	float _time;
	float _worldTime;

public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();

	void viewPixel();
	void characterChoice();
	void characterMove();
	void characterChange();

	//카메라
	void cameraChange(float orizinX, float orizinY, float newX, float newY);
	POINTFLOAT cameraPos(float x, float y);
	void changeMoving();

};

