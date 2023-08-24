#include <vector>
#include <math.h>
#include "Crab.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Time.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Crab::Crab(GameObject* parent)
    :GameObject(parent, "Crab"), hModel_(-1), fallFlag(false),
    prevPos(0.0f, 0.0f, 0.0f), pSyari(nullptr), pStage(nullptr), hSyariModel(0),
    hGroundModel(0)
{
}

//�f�X�g���N�^
Crab::~Crab()
{
}

//������
void Crab::Initialize()
{
    //�����ʒu�̐ݒ�
    transform_.position_.y = SYARI_SIZE_Y + MAGURO_SIZE_Y;

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Crab.fbx");
    assert(hModel_ >= 0);

    //�����蔻��̐���
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 0.5f, 3));
    AddCollider(collision);
}

//�X�V
void Crab::Update()
{
    //�I�u�W�F�N�g��T���āA�|�C���^�ɓ����
    FindAllObject();

    //�e���_�̈ʒu�𒲂ׂ�
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
    }

    //��ԒႢ�Ƃ���ƍ����Ƃ����T��
    int lowest = 0;
    int highest = 0;
    for (int i = 1; i < sizeof(vertexBonePos) / sizeof(XMFLOAT3); i++)
    {
        if (vertexBonePos[lowest].y > vertexBonePos[i].y)
        {
            lowest = i;
        }
        if (vertexBonePos[highest].y < vertexBonePos[i].y)
        {
            highest = i;
        }
    }

    RayCastData nowLowPosData;                    //��ԒႢ�p���烌�C���΂��āA���ƂԂ��邩�𒲂ׂ�
    nowLowPosData.start = vertexBonePos[lowest]/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //���C�̕���
    nowLowPosData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &nowLowPosData); //���C�𔭎�

    if (!nowLowPosData.hit)
    {
        /* SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
         pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);*/
    }

    //�V�����̕������Z
    PhysicalOperation();

    prevPos = transform_.position_;//�����̍��̏ꏊ��1f�O�̏ꏊ�ϐ��ɓ����
}

//�`��
void Crab::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Crab::Release()
{
}

//�����ɓ�������
void Crab::OnCollision(GameObject* pTarget)
{
}

//�I�u�W�F�N�g��T���āA�|�C���^�ɓ����
void Crab::FindAllObject()
{
    pSyari = (Syari*)FindObject("Syari");    //Syari�I�u�W�F�N�g��T��
    hSyariModel = pSyari->GetModelHandle();  //���f���ԍ����擾

    pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
    hGroundModel = pStage->GetModelHandle(); //���f���ԍ����擾
}

//���C���΂�
RayCastData Crab::DoRay(XMFLOAT3 start, XMFLOAT3 dir, int hModel)
{
    RayCastData rayData;
    rayData.start = start;
    rayData.dir = dir;
    Model::RayCast(hModel, &rayData);
    return rayData;
}

void Crab::PhysicalOperation()
{
    RayCastData syariData = DoRay(GetParentPos(), XMFLOAT3(0, -1, 0), hSyariModel);
    //�}�O�����V�����̏�ɏ���Ă�����
    //if (!syariData.hit)
    {
        if ((int)pSyari->GetRotate().z % ROTATE_MAX > FALL_ANGLE)
        {
            transform_.position_.x -= FALL_SPEED * ((int)pSyari->GetRotate().z % ROTATE_MAX);
        }
        if ((int)pSyari->GetRotate().z % ROTATE_MAX < -FALL_ANGLE)
        {
            transform_.position_.x -= FALL_SPEED * ((int)pSyari->GetRotate().z % ROTATE_MAX);
        }
        if ((int)pSyari->GetRotate().x % ROTATE_MAX > FALL_ANGLE)
        {
            transform_.position_.z += FALL_SPEED * ((int)pSyari->GetRotate().x % ROTATE_MAX);
        }
        if ((int)pSyari->GetRotate().x % ROTATE_MAX < -FALL_ANGLE)
        {
            transform_.position_.z += FALL_SPEED * ((int)pSyari->GetRotate().x % ROTATE_MAX);
        }
    }

    XMFLOAT3 fSyariToCrabVec;

    if (abs(transform_.position_.x) > SYARI_SIZE_X || abs(transform_.position_.z) > SYARI_SIZE_Z)
    {
        //�������Ă���
        transform_.position_.y -= 0.1;
    }
    //���ɃV�������Ȃ�������
}




