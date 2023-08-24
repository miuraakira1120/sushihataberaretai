#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

namespace ButtonManager
{
    //�{�^���̎��
    enum ButtonKinds
    {
        SCENE_CHANGE_BUTTON,
        PLAYER_CONTROL_BUTTON,
        SLIDER,
        MOVE_BY_MOUTH_BUTTON,
        BUTTON_KINDS_MAX
    };

    /// <summary>
    /// �{�^���I�u�W�F�N�g�̐����Ə����ݒ�
    /// </summary>
    /// <param name="pParent">�e�I�u�W�F�N�g</param>
    /// <param name="pChild">�q�I�u�W�F�N�g</param>
    /// <param name="position">�����ʒu</param>
    /// <param name="interval">�����Ԋu</param>
    void InstantiateButton(GameObject* pParent, GameObject* pChild, XMFLOAT3& position, const XMFLOAT3& interval);

    /// <summary>
    /// ��ʑJ�ڃ{�^���̍쐬
    /// </summary>
    /// <param name="pParent">�e�I�u�W�F�N�g</param>
    /// <param name="position">�{�^���̈ʒu</param>
    /// <param name="name">�J�ڐ�̖��O</param>
    /// <param name="fileName">�\��������摜�̖��O</param>
    /// <returns>�{�^���̃|�C���^</returns>
    GameObject* CreateSceneChangeButton(GameObject* pParent, XMFLOAT3 position, SCENE_ID name, std::string imageName);


    /// <summary>
    /// �v���C���[�̃{�^���z�u��ς���{�^���̍쐬
    /// </summary>
    /// <param name="pParent">�e�I�u�W�F�N�g</param>
    /// <param name="position">�{�^���̈ʒu</param>
    /// <param name="fileName">�\��������摜�̖��O</param>
    /// <returns>�{�^���̃|�C���^</returns>
    GameObject* CreatePlayerControlButton(GameObject* pParent, XMFLOAT3 position, std::string imageName);

    /// <summary>
    /// �X���C�_�[�̍쐬
    /// </summary>
    /// <param name="pParent">�e�I�u�W�F�N�g</param>
    /// <param name="position">�{�^���̈ʒu</param>
    /// <param name="imageName">�\��������摜�̖��O</param>
    /// <param name="childImageName">�X���[�_�[�̃{�^���ɕ\��������摜�̖��O</param>
    /// <returns>�X���C�_�[�̃|�C���^</returns>
    GameObject* CreateSliderButton(GameObject* pParent, XMFLOAT3 position, std::string imageName, std::string childImageName);

    /// <summary>
    /// �}�E�X�ɂ���ē����{�^���̍쐬
    /// </summary>
    /// <param name="pParent">�e�I�u�W�F�N�g</param>
    /// <param name="position">�{�^���̈ʒu</param>
    /// <param name="imageName">�\��������摜�̖��O</param>
    /// <returns>���̃{�^���̃|�C���^</returns>
    GameObject* CreateMoveByMouthButton(GameObject* pParent, XMFLOAT3 position, std::string imageName);

};

//�{�^���쐬�菇
//�P�@�{�^���N���X�����
//�Q�@Create�֐����쐬
//�R�@ButtonKinds�ɒǉ�
//���Create�֐����Ăׂ΂���

//Imgui�ɒǉ���

