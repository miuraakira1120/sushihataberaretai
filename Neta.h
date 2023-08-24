#pragma once
#include "Engine/GameObject.h"

class Neta : public GameObject
{
private:
    int   hModel_;               //���f���ԍ�
    float gravity;               //���󂯂Ă���d�̗͂�(�}�C�i�X�Ȃ�d�͂�U��؂��ď�ɍs��)
public:
    //�R���X�g���N�^
	Neta(GameObject* parent, const std::string& name, const std::string& pathFilename);

    //������
    virtual void Initialize() {};

    //�X�V
    virtual void Update() {};

    //�`��
    virtual void Draw();

    //�J��
    virtual void Release() {};

    //�Z�b�g�A�b�v����֐�
    virtual void SetUp();

    //�ŗL�̃X�L��
    virtual void Skill() {};

    //�e�̐e���猩���ʒu�����
    XMFLOAT3 GetParentPos();

    //�������Z
    void PhysicalOperation();

    /// <summary>
    /// �������o
    /// </summary>
    void LandingStaging();

    /// <summary>
    /// �d�͂̏���
    /// </summary>
    void Gravity();

    /// <summary>
    /// ���N���X�Őݒ肷��X�V(Update�̑O�ɌĂ�)
    /// </summary>
    void PriUpdate();
};

