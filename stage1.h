#pragma once
#include "gameNode.h"
#include "camera.h"

class stage1 : public gameNode
{
private:
	camera* _camera;
public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();


};

