#include "MoveByMouthButton.h"
#include "Engine/Direct3D.h"

MoveByMouthButton::MoveByMouthButton(GameObject* parent, std::string fileName)
	:Button(parent, "MoveByMouthButton")
{
	pathName_ = fileName;
}

void MoveByMouthButton::Initialize()
{
	//画像をセットする
	SetImage(pathName_, Direct3D::SHADER_2D);

}

void MoveByMouthButton::Event()
{
}

void MoveByMouthButton::PreUpdate()
{
}
