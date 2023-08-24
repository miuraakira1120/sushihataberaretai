#pragma once
#include "Engine/GameObject.h"
#include "Button.h"

//���������Ǘ�����N���X
class Slider : public Button
{
	const std::string DEF_CHILD_PATH = "testButton.png";
	std::string childPathName;//�X���C�_�[�̃{�^���̉摜�t�@�C����

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	/// <param name="fileName">�X���C�_�[�̉摜</param>
	Slider(GameObject* parent, std::string fileName);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	/// <param name="fileName">�X���C�_�[�̉摜</param>
	/// <param name="childFileName">�X���C�_�[�̃{�^���̉摜</param>
	Slider(GameObject* parent, std::string fileName, std::string childFileName);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �{�^���������ꂽ���̏���
	/// </summary>
	void Event() override;

};

