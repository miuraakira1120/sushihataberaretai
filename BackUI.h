#pragma once
#pragma once
#include "Engine/GameObject.h"

//UI�̔w�i
class BackUI : public GameObject
{
    int hPict_;

public:
    //�R���X�g���N�^
    BackUI(GameObject* parent);

    //�f�X�g���N�^
    ~BackUI();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};