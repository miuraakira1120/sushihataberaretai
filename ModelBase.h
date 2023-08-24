#pragma once
#include "Engine/GameObject.h"

//���f���̃x�[�X���Ǘ�����N���X
class ModelBase : public GameObject
{
    int hModel_;    //���f���ԍ�
    float scroll;
public:
    //�R���X�g���N�^
    ModelBase(GameObject* parent, std::string filename);

    //�f�X�g���N�^
    ~ModelBase();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};