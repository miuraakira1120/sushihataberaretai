#pragma once
#include <string>
#include "Button.h"

class PlayerControlButton : public Button
{
private:
	XMFLOAT3 imageSizeDef ;
	XMFLOAT3 imageSizeMag ;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	PlayerControlButton(GameObject* parent, std::string fileName);

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

