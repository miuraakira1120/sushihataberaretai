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

	//外枠を囲うようなシェーダー作る
	SetImage(pathName_, Direct3D::SHADER_2D);

}

void PlayerControlButton::Event()
{
	//プレイヤーのボタン操作を変えるUIや機能を出す
}

void PlayerControlButton::PreUpdate()
{
	//選ばれていたら画像を拡大する
	if (GetValue())
	{
		transform_.scale_ = imageSizeMag;
	}
	else
	{
		transform_.scale_ = imageSizeDef;
	}
}
