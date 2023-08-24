#pragma once
#include "Engine/GameObject.h"

class StageBase : public GameObject
{
	int hModel_;    //���f���ԍ�
    const std::string DIRECTORY = ".\\Stage/"; //�X�e�[�W�̃f�B���N�g����

public:
    
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="parent">�e�I�u�W�F�N�g</param>
    /// <param name="name">�X�e�[�W�̖��O</param>
    /// <param name="pathName">���f���̃p�X</param>
    StageBase(GameObject* parent, const std::string& name, const std::string& pathName);

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�n���h�����擾����֐�
    int GetModelHandle() { return hModel_; }
};

