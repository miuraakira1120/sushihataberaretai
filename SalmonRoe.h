#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class SalmonRoe : public GameObject
{
    const float SALMONROE_SIZE_Y = 0.6;
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    SalmonRoe(GameObject* parent);

    //�f�X�g���N�^
    ~SalmonRoe();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};