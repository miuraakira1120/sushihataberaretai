#pragma once
#include "Engine/GameObject.h"
#include "StageBase.h"

//�`���[�g���A���V�[�����Ǘ�����N���X
class Stage : public StageBase
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="parent">�e�I�u�W�F�N�g</param>
    /// <param name="path">�\�����郂�f��</param>
    Stage(GameObject* parent, std::string path);

    //�X�V�O�ɌĂԊ֐�
    void SetUp() override;
};

