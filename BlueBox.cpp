#include "BlueBox.h"
#include "Engine/Model.h"

//�R���X�g���N�^
BlueBox::BlueBox(GameObject* parent)
    :GameObject(parent, "BlueBox"), hModel_(-1)
{
}

//�f�X�g���N�^
BlueBox::~BlueBox()
{
}

//������
void BlueBox::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("BlueBox.fbx");
    assert(hModel_ >= 0);

    transform_.scale_ = { 0.25f, 0.25f, 0.25f };
}

//�X�V
void BlueBox::Update()
{
}

//�`��
void BlueBox::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void BlueBox::Release()
{
}

void BlueBox::SetPosition(XMFLOAT3 pos_)
{
    transform_.position_ = pos_;
}
