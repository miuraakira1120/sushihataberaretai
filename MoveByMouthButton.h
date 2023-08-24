#pragma once
#include <string>
#include "Button.h"

class MoveByMouthButton : public Button
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	MoveByMouthButton(GameObject* parent, std::string fileName);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �{�^���������ꂽ���̏���
	/// </summary>
	void Event() override;

	/// <summary>
	/// Update�֐��̑O�ɌĂ΂��֐�
	/// </summary>
	void PreUpdate() override;
};

