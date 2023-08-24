#pragma once
#include "Engine/GameObject.h"


//���������Ǘ�����N���X
class Ball : public GameObject
{
    //�萔
    const float SPEED_LIMIT = 2.0f;  //�����̑��x���E
    const float FALL_SPEED = 0.02f; //������X�s�[�h
    const float BALL_SIZE = 0.5f;

    int hModel_;    //���f���ԍ�
    XMFLOAT3 fMove;
    bool isGround;   //�n�ʂɐݒu���Ă��邩
    float accel;//���ǂꂾ���������邩
    bool isPrevRayHit;
    int count;

    XMVECTOR vMoved;

    XMFLOAT3 prevPos;//
public:
    //�R���X�g���N�^
    Ball(GameObject* parent);

    //�f�X�g���N�^
    ~Ball();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�Z�b�^�[
    void SetMove(XMFLOAT3 move);
    void SetPosition(XMFLOAT3 pos);

};