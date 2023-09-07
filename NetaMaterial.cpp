#include "NetaMaterial.h"
#include "Engine/Model.h"
#include "ModelBase.h"
#include "Engine/SphereCollider.h"
#include "Engine/BoxCollider.h"
#include "Tuna.h"
#include "VFX.h"

//�R���X�g���N�^
NetaMaterial::NetaMaterial(GameObject* parent)
    :GameObject(parent, "NetaMaterial"), pInternalModel(nullptr)
{
}

NetaMaterial::NetaMaterial(GameObject* parent, std::string fileName)
{
    internalModelPath = fileName;
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

    //�R���C�_�[������
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), SPHERE_SIZE);
    AddCollider(collision);

    //���^�̃R���C�_�[������i�e�X�g�j
    //BoxCollider* boxCollision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(2, 2, 2));
    //AddCollider(boxCollision);

    //���̃��f���̍쐬
    pInternalModel = CharacterInstantiate<ModelBase>(this, internalModelPath);
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

//�����ɓ���������Ăяo�����֐�
void NetaMaterial::OnCollision(GameObject* pTarget)
{
    //�v���C���[�ɂԂ�������
    if (pTarget->GetName() == "Player")
    {
        //���ɂ��郂�f�����}�O���Ȃ�
        if (internalModelPath == "maguro.fbx")
        {
            //�v���C���[�̎q�I�u�W�F�N�g��ǉ�
            CharacterInstantiate<Tuna>(pTarget, "maguro.fbx");

            //�G�t�F�N�g
            EmitterData starEfect = VFX::SetEmitterDataStar();
            starEfect.position = pTarget->GetPosition();
            VFX::Start(starEfect);

            //���̃��f��������
            pInternalModel->KillMe();

            //���̃��f���̖��O������
            internalModelPath = "";
        }
    }
}
