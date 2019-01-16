#pragma once
#include "gameNode.h"

struct baleogPlayer
{
	float x, y;
	image* baleogImage;
	RECT baleogRc;
	float speed;
};


enum BALEOGSTATE //���α� ����
{
	BALEOG_RIGHT_STOP, //������ �⺻����
	BALEOG_LEFT_STOP, //���� �⺻����
	BALEOG_RIGHT_MOVE, //������ ������
	BALEOG_LEFT_MOVE, //���� ������
	BALEOG_RIGHT_SWORD_ATTACK, //������ �˰���
	BALEOG_LEFT_SWORD_ATTACK, //���� �˰���
	BALEOG_RIGHT_ARROW_ATTACK, //������ ȭ�����
	BALEOG_LEFT_ARROW_ATTACK, //���� ȭ�����
};

enum BALEOGINFO // ���α� ������
{
	BALEOG_X = WINSIZEX / 2,
	BALEOG_Y = WINSIZEY / 2,
	BALEOG_SPEED = 0,
};

class baleog : public gameNode
{
private:
	BALEOGSTATE _baleogState;
	baleogPlayer _baleogPlayer;

	animation* _baleogMotion; //���α� ��� ����� �� �ִϸ��̼�
public:

	baleog();
	~baleog();

	HRESULT init();
	void release();
	void update();
	void render();


};

