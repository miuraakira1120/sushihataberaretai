#pragma once
#include "PlayerBase.h"
class Player : public PlayerBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="parent">�e�I�u�W�F�N�g</param>
    /// <param name="name">�I�u�W�F�N�g�̖��O</param>
    /// <param name="pathName"></param>
    Player(GameObject* parent, std::string pathName);

    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update() override;
};

