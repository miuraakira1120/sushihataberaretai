#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Cannon : public GameObject
{
    int hModel_;    //���f���ԍ�
    const float CANNON_SIZE_Y = 1.0f;
    unsigned int timer;
public:
    //�R���X�g���N�^
    Cannon(GameObject* parent);

    //�f�X�g���N�^
    ~Cannon();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};