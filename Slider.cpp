#include "Slider.h"
#include "Engine/Image.h"

Slider::Slider(GameObject* parent, std::string fileName)
	:Button(parent, "Slider"), childPathName(DEF_CHILD_PATH)
{
}

// �R���X�g���N�^
Slider::Slider(GameObject* parent, std::string fileName, std::string childFileName)
    :Button(parent, "Slider"), childPathName(childFileName)
{
}

void Slider::Initialize()
{
	//�摜���Z�b�g����
	SetImage(pathName_, Direct3D::SHADER_2D);

	//�}�E�X�ɂ���ē����{�^�����쐬
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	ButtonManager::CreateMoveByMouthButton(this, pos, childPathName);
}

void Slider::Event()
{
}
