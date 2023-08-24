#include "Goal.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "Syari.h"

//�R���X�g���N�^
Goal::Goal(GameObject* parent)
    :GameObject(parent, "Goal"), hModel_(-1)
{
}

//�f�X�g���N�^
Goal::~Goal()
{
}

//������
void Goal::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Dishes.fbx");
    assert(hModel_ >= 0);
    //transform_.position_ = { 14.0f, -34.0f, -33.0f};
    //transform_.scale_ = { 2.5f, 0.25f , 2.5f };
    transform_.position_ = {5.5,13,174.5};
}

//�X�V
void Goal::Update()
{
    transform_.rotate_.y += 0.5f;

    Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾

    Syari* pSyari = (Syari*)FindObject("Syari");    //�X�e�[�W�I�u�W�F�N�g��T��
    hGroundModel = pSyari->GetModelHandle();    //���f���ԍ����擾

    RayCastData data;
    data.start = transform_.position_;   //���C�̔��ˈʒu
    data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &data); //���C�𔭎�

    //���C������������
    if (data.hit)
    {
        //���̕��ʒu��������
        //transform_.position_.y -= data.dist;
    }

}

//�`��
void Goal::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Goal::Release()
{
}