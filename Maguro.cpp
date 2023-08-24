#include <vector>
#include <math.h>
#include "Maguro.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Time.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "GameManager.h"

namespace
{
    const float FALL_SPEED_LIMIT = 0.7f;    //�����̑��x���E 
    const float JUMP_POWER       = 0.8f;    //�������x
    const float FALL_SPEED       = 0.02f;   //������X�s�[�h
}

//�R���X�g���N�^
Maguro::Maguro(GameObject* parent)
    :GameObject(parent, "Maguro"), hModel_(-1), isLandingMotion(false),
    prevPos(0.0f,0.0f,0.0f), pSyari(nullptr),pStage(nullptr), hSyariModel(0), 
    hGroundModel(-1), gravity(0), isFullFall(false)
{
}

//�f�X�g���N�^
Maguro::~Maguro()
{
}

//������
void Maguro::Initialize()
{
    //�����ʒu�̐ݒ�
    transform_.position_.y = SYARI_SIZE_Y + MAGURO_SIZE_Y;

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("maguro.fbx");
    assert(hModel_ >= 0);

    explosion.textureFileName = "Cloud.png";
    explosion.delay = 0;
    explosion.number = 80;
    explosion.lifeTime = 20;
    explosion.direction = XMFLOAT3(0, 1, 0);
    explosion.directionRnd = XMFLOAT3(90, 90, 90);
    explosion.speed = 0.1f;
    explosion.speedRnd = 0.8;
    explosion.size = XMFLOAT2(1, 1);
    explosion.sizeRnd = XMFLOAT2(0.4, 0.4);
    explosion.scale = XMFLOAT2(1.05, 1.05);
    explosion.color = XMFLOAT4(1, 1, 0.1, 1);
    explosion.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);

    
    //�X�e�[�W�̃��f�����擾
    StageBase* pStage = GameManager::GetNowStage();    //�X�e�[�W�I�u�W�F�N�g��T��
    hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾
}

//�X�V
void Maguro::Update()
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
    nowLowPosData.start = { vertexBonePos[lowest].x,vertexBonePos[lowest].y + 3,vertexBonePos[lowest].z };  /*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //���C�̕���
    nowLowPosData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &nowLowPosData); //���C�𔭎�

    RayCastData nowHightPosData;                    //��ԒႢ�p���烌�C���΂��āA���ƂԂ��邩�𒲂ׂ�
    nowHightPosData.start = vertexBonePos[highest]/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //���C�̕���
    nowHightPosData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &nowHightPosData); //���C�𔭎�

    if (nowLowPosData.pos.y >= vertexBonePos[lowest].y)
    {
       //SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
       //pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);

        //�^�[�Q�b�g�����̃I�u�W�F�N�g�ɕύX
        Camera::SetTarget(Math::Float3Sub(transform_.position_, GetParent()->GetPosition()));

        //�����G�t�F�N�g�̃G�~�b�^�[��ݒu
        explosion.position = transform_.position_;
        VFX::Start(explosion);	

        //�v���C���[�ɃJ������Ǐ]������悤�ɂ���
        //pSyari->SetIsCamControll(true);

        //���̃I�u�W�F�N�g���폜����
        KillMe();
    }

#if _DEBUG
    if (Input::IsKey(DIK_T))
    {
        transform_.position_.z += 0.1f;
    }
#endif

    //�V�����̕������Z
    if (!isLandingMotion)
    {
        PhysicalOperation();
    }
    else
    {
        //�������o
        LandingStaging();
    }

    prevPos = transform_.position_;//�����̍��̏ꏊ��1f�O�̏ꏊ�ϐ��ɓ����
}

//�`��
void Maguro::Draw()
{
    if (!isLandingMotion)
    {
        Model::SetTransform(hModel_, transform_);
        Model::Draw(hModel_);
    }
    else
    {
        Transform trans = transform_;
        trans.position_ = Math::Float3Sub(transform_.position_, GetParent()->GetPosition());
        Model::SetTransform(hModel_, trans);
        Model::Draw(hModel_);
    }
}

//�J��
void Maguro::Release()
{
}

//�����ɓ�������
void Maguro::OnCollision(GameObject* pTarget)
{ 
}

//�I�u�W�F�N�g��T���āA�|�C���^�ɓ����
void Maguro::FindAllObject()
{
    //�X�e�[�W�̃��f�����擾
    StageBase* pStage = GameManager::GetNowStage();    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾
}

//���C���΂�
RayCastData Maguro::DoRay(XMFLOAT3 start, XMFLOAT3 dir, int hModel)
{
    RayCastData rayData;
    rayData.start = start;
    rayData.dir = dir;
    Model::RayCast(hModel, &rayData);
    return rayData;
}

void Maguro::PhysicalOperation()
{
    //�e�̃|�C���^���擾
    pSyari = (Syari*)GetParent();

    //���f���ԍ����擾
    hSyariModel = pSyari->GetModelHandle();

   /* RayCastData syariData = DoRay(GetParentPos(), XMFLOAT3(0, -1, 0), hSyariModel);*/
    XMFLOAT3 syariUpDistanceDifference = pSyari->GetUpDistanceDifference();
    //�}�O�����V�����̏�ɏ���Ă�����
    //if (!syariData.hit)
    {
        //�E�Ǝ�O�̂ق�������΁{
        //���̉��ق�������΁|
        if (syariUpDistanceDifference.z > FALL_ANGLE || syariUpDistanceDifference.z < FALL_ANGLE)
        {
            if (syariUpDistanceDifference.z > FALL_ANGLE > 0)
            {
                transform_.position_.x += FALL_SPEED * abs(syariUpDistanceDifference.z);
            }
            else
            {
                transform_.position_.x -= FALL_SPEED * abs(syariUpDistanceDifference.z);
            }
        }
        if (syariUpDistanceDifference.x > FALL_ANGLE || syariUpDistanceDifference.x < FALL_ANGLE)
        {
            if (syariUpDistanceDifference.x > FALL_ANGLE > 0)
            {
                transform_.position_.z -= FALL_SPEED * abs(syariUpDistanceDifference.x);
            }
            else
            {
                transform_.position_.z += FALL_SPEED * abs(syariUpDistanceDifference.x);
            }
        }
    }

    if (abs(transform_.position_.x) > SYARI_SIZE_X || abs(transform_.position_.z) > SYARI_SIZE_Z)
    {
        //�v���C���[�ɃJ������Ǐ]�����Ȃ�����
        //pSyari->SetIsCamControll(false);

        //�v���C���[�̓��͂��󂯕t���Ȃ�����
        //pSyari->SetCanMove(false);

        //�������o
        isLandingMotion = true;

        //�e�̐e��e�ɂ��Ĉړ�����
        transform_.ChangeParentRotate(0);
        transform_.SetRotateMode(TRANS_CHANGEPARENT_MODE);

        //�e�I�u�W�F�N�g�̈ʒu�Ɉړ�
        transform_.position_ = Math::Float3Add(GetParent()->GetPosition(), transform_.position_);
        transform_.position_.y += SYARI_SIZE_Y;

        //��яオ��
        gravity -= JUMP_POWER;
    }
}

//�������o
void Maguro::LandingStaging()
{
    //�^�[�Q�b�g�����̃I�u�W�F�N�g�ɕύX
    Camera::SetTarget(transform_.position_);

    //�d�͂̏���
    Gravity();

    //�������̉�]���o
    RotationStaging();
}

//�������̉�]���o
void Maguro::RotationStaging()
{
    transform_.rotate_ = Math::Float3Add(ROTATE_STAGING_ANGE, transform_.rotate_);
}

//�d�͂̏���
void Maguro::Gravity()
{
    //�X�s�[�h�̏���ɒB���Ă��Ȃ����
    if (FALL_SPEED_LIMIT >= gravity)
    {
        gravity += FALL_SPEED;
        transform_.position_.y -= gravity;
    }
    else
    {
        transform_.position_.y -= FALL_SPEED_LIMIT;
    }
}




