#pragma once
#include <string>
#include "Button.h"
#include "Engine/SceneManager.h"

class ChangeSceneButton : public Button
{
private:
	const XMFLOAT3 IMAGE_SIZE_DEF = { 1.0f, 1.0f, 1.0f };
	const XMFLOAT3 IMAGE_SIZE_MAG = { 1.1f, 1.1f, 1.0f };

	SCENE_ID changeSceneName;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	ChangeSceneButton(GameObject* parent, SCENE_ID name, std::string fileName);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �{�^���������ꂽ���̏���
	/// </summary>
	void Event() override;

	/// <summary>
	/// �J�ڐ�̃V�[���̖��O�̃Z�b�^�[
	/// </summary>
	/// <param name="name"></param>
	void SetChangeSceneName(SCENE_ID name);

	/// <summary>
	/// Update�֐��̑O�ɌĂ΂��֐�
	/// </summary>
	void PreUpdate() override;
};

