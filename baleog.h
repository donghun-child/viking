#pragma once
#include "gameNode.h"
#include "arrow.h"

struct baleogPlayer
{
	float x, y;
	image* baleogImage;
	image* arrowImage;
	RECT baleogRc;
	float speed;
};


enum BALEOGSTATE //���α� ����
{
	BALEOG_RIGHT_STOP, //������ �⺻����
	BALEOG_LEFT_STOP, //���� �⺻����
	BALEOG_RIGHT_MOVE, //������ ������
	BALEOG_LEFT_MOVE, //���� ������
	BALEOG_UP_MOVE, //��ٸ� Ż��� ���� ������
	BALEOG_DOWN_MOVE, //��ٸ� Ż��� �Ʒ��� ������
	BALEOG_RIGHT_SWORD_ATTACK_ONE, //������ ù��° ���� �˰���
	BALEOG_LEFT_SWORD_ATTACK_ONE, //���� ù��° ���� �˰���
	BALEOG_RIGHT_SWORD_ATTACK_TWO, //������ �ι�° ���� �˰���
	BALEOG_LEFT_SWORD_ATTACK_TWO, //���� �ι�° ���� �˰���
	BALEOG_RIGHT_ARROW_ATTACK, //������ ȭ�����
	BALEOG_LEFT_ARROW_ATTACK, //���� ȭ�����
};

enum BALEOGINFO // ���α� ������
{
	BALEOG_X = WINSIZEX / 2,
	BALEOG_Y = WINSIZEY / 2,
	BALEOG_SPEED = 5,
};

class baleog : public gameNode
{
private:
	BALEOGSTATE _baleogState;
	baleogPlayer _baleogPlayer;
	
	arrow* _arrow;
	animation* _baleogMotion; //���α� ��� ����� �� �ִϸ��̼�

	int _rndAttack;

	bool _isLadderColision; //��ٸ� �浹�ߴ�
	bool _arrowFireStop;

public:
	baleog();
	~baleog();

	HRESULT init();
	void release();
	void update(float baleogX, float baleogY);
	void render();

	void keySetting(float baleogX, float baleogY); //Ű����
	void arrowAttack(); //ȭ�����
	void swordAttack(); //�˰���
	void arrowFire(); //����� �������� ȭ�� �߻��� �Լ�

	//�ݹ��Լ� �ҷ��� �Լ�
	static void rightFire(void* obj);
	static void leftFire(void* obj);

public:
	//���α� ���� ������ ������
	BALEOGSTATE getBaleogState() { return _baleogState; }
	void setBaleogState(BALEOGSTATE state) { _baleogState = state; }

	//���α� �ִϸ��̼� ������ ������
	animation* getBaleogMotion() {return _baleogMotion;}
	void setBaleogMotion(animation* motion) {_baleogMotion = motion;}

	//��ٸ� �浹�ߴ��� ������ ������
	bool getLadderCollision() {return _isLadderColision;}
	void setLadderCollision(bool collision) {_isLadderColision = collision;}
};

