#include "RedBox.h"
#include "Engine/Model.h"

//�R���X�g���N�^
RedBox::RedBox(GameObject* parent)
    :GameObject(parent, "RedBox"), hModel_(-1)
{
}

//�f�X�g���N�^
RedBox::~RedBox()
{
}

//������
void RedBox::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("RedBox.fbx");
    assert(hModel_ >= 0);

    transform_.scale_ = { 0.25f, 0.25f, 0.25f };
}

//�X�V
void RedBox::Update()
{
}

//�`��
void RedBox::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void RedBox::Release()
{
}

void RedBox::SetPosition(XMFLOAT3 pos_)
{
    transform_.position_ = pos_;
}
