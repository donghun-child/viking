#pragma once
#include "gameNode.h"



class camera : public gameNode
{
private:
	image* _mapimage;

	POINTFLOAT _camera;

	float _mapX, _mapY;
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

	float getMapx() { return _mapX; }
	float getMapy() { return _mapY; }

	//ī�޶� ��ȯ
	void setChange(bool v) { change = v; }
	//�÷��̾�� �Ÿ� 
	void setDistance(float v) { Distance = v; }
	void setAngle(float v) { Distance = v; }
};

