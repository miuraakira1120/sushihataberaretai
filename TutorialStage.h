#pragma once
#include "Engine/GameObject.h"
#include "StageBase.h"

//�`���[�g���A���V�[�����Ǘ�����N���X
class TutorialStage : public StageBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	/// <param name="path">�\�����郂�f��</param>
	TutorialStage(GameObject* parent, std::string path);
};
