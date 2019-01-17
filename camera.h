#pragma once
#include "gameNode.h"

class playerManager;

class camera : public gameNode
{
private:
	playerManager* _playerManager;

	image* _mapimage;

	POINTFLOAT _camera;

	bool change;

	float Distance;
	float angle;

public:
	camera();
	~camera();

	HRESULT init();
	void release();
	void update(float playerX, float playerY, int choice, float changespeed);
	void render();

	POINTFLOAT getCameraPos() { return _camera; }

	float getCameraX() { return _camera.x; }
	float getCameraY() { return _camera.y; }

	//ī�޶� ��ȯ
	void setChange(bool v) { change = v; }
	//�÷��̾�� �Ÿ� 
	void setDistance(float v) { Distance = v; }
	void setAngle(float v) { Distance = v; }

	void getPlayerManagerAddressLink(playerManager* playerManager) { _playerManager = playerManager; }
};

