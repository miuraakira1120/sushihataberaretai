#include "Torus.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Torus::Torus(GameObject* parent)
    :GameObject(parent, "Torus")
{
}

//�f�X�g���N�^
Torus::~Torus()
{
}

//������
void Torus::Initialize()
{
    hModel_ = Model::Load("Torus.fbx");
    transform_.position_.y = 2.0f;
        
}

//�X�V
void Torus::Update()
{
    static int time = 0;
    time++;

    transform_.position_.x = sin((float)time / 50)*5;
    transform_.rotate_.z = time * 5;


}

//�`��
void Torus::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Torus::Release()
{
}