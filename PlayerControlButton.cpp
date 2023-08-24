#include "PlayerControlButton.h"
#include "Engine/Direct3D.h"

PlayerControlButton::PlayerControlButton(GameObject* parent, std::string fileName)
	:Button(parent, "PlayerControlButton"), imageSizeDef(1.0f,1.0f,1.0f),imageSizeMag(1.1f,1.1f,1.1f)
{
	pathName_ = fileName;
}

void PlayerControlButton::Initialize()
{
	imageSizeDef = transform_.scale_;
	imageSizeMag = Math::Float3Mul(imageSizeDef, 1.1f);

	//�O�g���͂��悤�ȃV�F�[�_�[���
	SetImage(pathName_, Direct3D::SHADER_2D);

}

void PlayerControlButton::Event()
{
	//�v���C���[�̃{�^�������ς���UI��@�\���o��
}

void PlayerControlButton::PreUpdate()
{
	//�I�΂�Ă�����摜���g�傷��
	if (GetValue())
	{
		transform_.scale_ = imageSizeMag;
	}
	else
	{
		transform_.scale_ = imageSizeDef;
	}
}
