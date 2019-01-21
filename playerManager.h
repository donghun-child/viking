#pragma once
#include "gameNode.h"
#include "baleog.h"
#include "olaf.h"
#include "eric.h"
#include "camera.h"


enum Character
{
	ERIC,
	BALEOG,
	OLAF
};

class item;

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

	RECT _camerc;
	float _camerc_x;
	float _camerc_y;
	float _cameview_x;
	float _cameview_y;

	Character _choice;
	float _gravity;
	float _jumpPower;
	bool _isJump;
	int _jumpCount;
	//점프 횟수
	int _jumpNum;

	item* _item;

	int _attckCount;
	bool _isAttack;

public:
	playerManager();
	~playerManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//캐릭터 선택
	void characterChoice();
	void characterMove();
	void characterChange();

	//픽셀충돌
	void pixelCollisionGreen();
	void pixelCollisionYellow();
	void pixelCollisionEmerald();
	void pixelCollisionRed();

	//중력
	void jumpGravity(int select);

	void getCameraAddressLink(camera* camera) { _camera = camera; }
	void getItemLinkAddress(item* item) { _item = item; }




	float getEricX() { return _x[ERIC]; };
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

	camera* getCamera() { return _camera; }

	Character getChoice() {return _choice;}
	void setChoice(Character choice) {_choice = choice;}


};

