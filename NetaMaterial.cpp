#include "NetaMaterial.h"
#include "Engine/Model.h"
#include "ModelBase.h"

//�R���X�g���N�^
NetaMaterial::NetaMaterial(GameObject* parent)
    :GameObject(parent, "NetaMaterial"), pInternalModel(nullptr)
{
}

//�f�X�g���N�^
NetaMaterial::~NetaMaterial()
{
}

//������
void NetaMaterial::Initialize()
{
    pathName_ = "TransparentSphere.fbx";
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load(pathName_, MODEL_ALPHA);
    assert(hModel_ >= 0);

    //���̃��f���̍쐬
    pInternalModel = CharacterInstantiate<ModelBase>(this, "maguro.fbx");
    pInternalModel->SetScale(INTERNAL_MODEL_SCALE, INTERNAL_MODEL_SCALE, INTERNAL_MODEL_SCALE);
}

//�X�V
void NetaMaterial::Update()
{
    //�������f���̉�]
    pInternalModel->SetRotate(Math::Float3Add(pInternalModel->GetRotate(), INTERNAL_MODEL_ROTATE));
}

//�`��
void NetaMaterial::Draw()
{
    Transform trans = pInternalModel->GetTransform();
    Model::SetTransform(pInternalModel->GetModelHandle(), trans);
    Model::Draw(pInternalModel->GetModelHandle());

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void NetaMaterial::Release()
{
}