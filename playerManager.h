#pragma once
#include "gameNode.h"
#include "baleog.h"
#include "olaf.h"
#include "eric.h"
#include "camera.h"
#include "arrow.h"

enum Character
{
	ERIC,
	BALEOG,
	OLAF
};

struct object //사다리
{
	RECT rc;
	float x, y;
	float viewX, viewY;
};


class item;

class playerManager : public gameNode
{
private:
	camera* _camera;

	RECT _rc[3];

	bool _isDebug;

	object _ladder[5]; //사다리
	object _deadZone[3];
	baleog* _baleog;
	eric* _eric;
	olaf* _olaf;
	arrow* _arrow;

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

	bool _isArrowFireStop;

	bool _isGravity;

	bool _isCameraMode;
	bool _isLadderCollision;
	bool _gravityStop;

	int _ladderChoice;
	int _wallcheck;

	int _deadTime;
	float _deadTum;
	bool _isDead[3];
	float _moveTime, _moveWorldTime;

	bool _isButt; //박치기했니
	int _buttTime;

	float _buttAngle;

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

	//사다리 충돌
	void ladderCollision();

	//데드존 충돌
	void deadZoneCollision();

	//픽셀충돌
	void pixelCollisionGreen();
	void pixelCollisionYellow();
	void pixelCollisionEmerald();
	void pixelCollisionRed();

	//중력
	void jumpGravity(int select);

	//벨로그 화살
	void baleogArrow();

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

	RECT getEricRect() {return _rc[ERIC]; }
	RECT getBaleogRect() { return _rc[BALEOG]; }
	RECT getOlafRect() { return _rc[OLAF]; }

	void setGravity(bool gravity) {_isGravity = gravity;}

	eric* getEric() {return _eric;}
	void setJumpNum(int jumpNum) {_jumpNum = jumpNum;}
};

