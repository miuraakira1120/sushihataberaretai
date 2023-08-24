#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class RedBox : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    RedBox(GameObject* parent);

    //�f�X�g���N�^
    ~RedBox();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetPosition(XMFLOAT3 pos_);
};