#include "BackUI.h"
#include "Engine/Image.h"

//�R���X�g���N�^
BackUI::BackUI(GameObject* parent)
    :GameObject(parent, "BackUI"), hPict_(-1)
{
}

//�f�X�g���N�^
BackUI::~BackUI()
{
}

//������
void BackUI::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load(pathName_);
    assert(hPict_ >= 0);
}

//�X�V
void BackUI::Update()
{
}

//�`��
void BackUI::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::SetAlpha(hPict_, 100);
    Image::Draw(hPict_);
}

//�J��
void BackUI::Release()
{
}