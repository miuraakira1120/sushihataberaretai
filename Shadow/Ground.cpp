#include "Ground.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground")
{
}

//�f�X�g���N�^
Ground::~Ground()
{
}

//������
void Ground::Initialize()
{
    hModel_ = Model::Load("Ground.fbx");
    transform_.position_.y = -3.0f;
}

//�X�V
void Ground::Update()
{
}

//�`��
void Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Ground::Release()
{
}