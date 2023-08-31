#include "PlayerBase.h"
#include "Controller.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Controller.h"
#include "OBB.h"
#include "Engine/Global.h"
#include "Maguro.h"
#include <algorithm>
#include "Tuna.h"

namespace
{
    //�萔
    const float         FALL_SPEED_LIMIT = 0.5f;    //�����̑��x���E 
    const float         SPEED_OF_JUMP = 0.4f;       //�������x
    const float         FALL_SPEED = 0.02f;         //������X�s�[�h
    const float         SYARI_SPEED = 0.25f;        //�V�����̃X�s�[�h
    static const int    NUM_OF_THROW = 6;           //����ǂƏՓ˂𔻒肳����Ƃ��ɔ�΂����C�̐�
    static const int    DIRECTION_ARRAY_SIZE = 3;   //�������i�[���ꂽ�z��̃T�C�Y
    const float         ATTENUATION_RATIO = 0.05f;  //������
}


//�R���X�g���N�^
PlayerBase::PlayerBase(GameObject* parent, std::string name, std::string modelFilename)
    :GameObject(parent, name, modelFilename),hModel_(-1), gravity(0.0f), size(PLAYER_SIZE)
{
}

//�`��
void PlayerBase::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�Z�b�g�A�b�v����֐�
void PlayerBase::SetUp()
{
    //���f�������[�h
    hModel_ = Model::Load(pathName_);
    assert(hModel_ >= 0);

    //�J�����̃R���g���[���[��T��
    pController = (Controller*)FindObject("Controller");

    ////����OBB�Փ˔���
    //RayCastData prePosData;
    //prePosData.start = transform_.position_;   //���C�̔��ˈʒu
    //prePosData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���(�^����)
    //Model::RayCast(, &prePosData);  //���C�𔭎�

    //�q�I�u�W�F�N�g�̐���
    //CharacterInstantiate<Tuna>(this, "maguro.fbx");
    //Instantiate<Maguro>(this);
}

//�W�����v
void PlayerBase::Jump()
{
    //���ɂ��Ă�����
    if (state_.isGround)
    {
        //�d�͂��}�C�i�X�ɂȂ邱�Ƃŏ㏸����
        gravity -= SPEED_OF_JUMP;
    }
}

//�ړ�����֐�
void PlayerBase::Move(bool isInverse)
{
    //�J�����̌����ɂ��̃I�u�W�F�N�g��ݒ肷��
    transform_.rotate_.y = pController->GetRotate().y;

    //�v���C���[�̈ړ��x�N�g��
    XMFLOAT3 move = { 0,0,SYARI_SPEED };

    //�ړ��x�N�g���̌^��XMVECTOR�ɕϊ�
    XMVECTOR vMove;
    vMove = XMLoadFloat3(&move);

    //�ړ���������ɉ�]
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vMove = XMVector3TransformCoord(vMove, mRotate);

    //�o�b�N�ɂ���Ȃ�move���t�ɂ���
    if (!isInverse)
    {
        vMove *= -1;
    }

    //vMove��XMFLOAT3�ɕϊ�
    XMFLOAT3 fMove;
    XMStoreFloat3(&fMove, vMove);

    //�V�����̌��ݒn��XMVECTOR�ɕϊ�
    XMVECTOR vPos;
    vPos = XMLoadFloat3(&transform_.position_);

    //�ړ���̍��W���v�Z
    vPos += vMove;

    //���ݒn��transform_.position_�ɑ���
    XMStoreFloat3(&transform_.position_, vPos);
}

//�ړ�����֐�
void PlayerBase::Move(float accel, bool isInverse)
{
    //�J�����̌����ɂ��̃I�u�W�F�N�g��ݒ肷��
    transform_.rotate_.y = pController->GetRotate().y;

    //�v���C���[�̈ړ��x�N�g��
    XMFLOAT3 move = { 0,0,SYARI_SPEED };

    //�ړ��x�N�g���̌^��XMVECTOR�ɕϊ�
    XMVECTOR vMove;
    vMove = XMLoadFloat3(&move);

    //�ړ���������ɉ�]
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vMove = XMVector3TransformCoord(vMove, mRotate);

    //�o�b�N�ɂ���Ȃ�move���t�ɂ���
    if (!isInverse)
    {
        vMove *= -1;
    }

    //vMove��XMFLOAT3�ɕϊ�
    XMFLOAT3 fMove;
    XMStoreFloat3(&fMove, vMove);

    //�V�����̌��ݒn��XMVECTOR�ɕϊ�
    XMVECTOR vPos;
    vPos = XMLoadFloat3(&transform_.position_);

    //�ړ���̍��W���v�Z
    vPos += vMove * accel;

    //���ݒn��transform_.position_�ɑ���
    XMStoreFloat3(&transform_.position_, vPos);
}

//�d�͂̏���
void PlayerBase::Gravity()
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

//�Փ˂��Ă��邩���ׂ�
bool PlayerBase::CheckIfCollided(int hStageModel, XMFLOAT3 vec, XMFLOAT3 rayPos, float& length)
{
    //�V�����̌��ݒn��XMVECTOR�ɕϊ�
    XMVECTOR vPos;
    vPos = XMLoadFloat3(&transform_.position_);

    //OBB�Ɏg�p����x�N�g���̌����쐬
    XMFLOAT3 fBoneDir[DIRECTION_ARRAY_SIZE] =
    {
        {size.x, 0, 0},
        {0, size.y, 0},
        {0, 0, size.z},
    };

    //OBB�Ɏg�p����x�N�g�����쐬
    //DIRECTION�̕����[�v����
    std::vector<XMVECTOR> dirVec;
    for (int i = 0; i < DIRECTION_ARRAY_SIZE; i++)
    {
        //fBoneDir��XMVECTOR�ɕϊ�
        XMVECTOR vBoneDir = XMLoadFloat3(&fBoneDir[i]);

        //BoneDir���s�񂍂ŕό`
        vBoneDir = XMVector3TransformCoord(vBoneDir, transform_.changeMatRotate_);	

        //vBoneDir�Ƀ|�W�V�����𑫂�
        vBoneDir += vPos;

        //XMFLOAT3�ɒ���
        XMStoreFloat3(&fBoneDir[i], vBoneDir);

        //���X�g�ɒǉ�����
        dirVec.push_back(vBoneDir - vPos);
    }

    //OBB�Ɏg�p����x�N�g���̒������擾
    std::vector<float> fLength;
    for (int i = 0; i < fLength.size() - 1; i++)
    {
        //���X�g�ɒǉ�����
        fLength.push_back(XMVectorGetX(XMVector3Length(dirVec[i])));
    }

    //�v���C���[��OBB��ݒ�
    OBB prayerOBB;
    prayerOBB.SetOBBAll(vPos, dirVec, fLength);

    //����OBB�Փ˔���
    RayCastData prayerOBBData;
    prayerOBBData.start = rayPos;   //���C�̔��ˈʒu
    prayerOBBData.dir = vec;                      //���C�̕���
    Model::RayCast(hStageModel, &prayerOBBData);  //���C�𔭎�

    float len;
    //���C���������Ă��āA�Փ˂��Ă�����
    if (prayerOBBData.hit && prayerOBB.OBBvsPlane(prayerOBB, prayerOBBData.pos, prayerOBBData.normal, &len))
    {
        XMVECTOR vVec = XMLoadFloat3(&vec);
        vVec = XMVector3Normalize(vVec);
        XMVECTOR dot = XMVector3Dot(vVec, -prayerOBBData.normal);
        //len *= (1 - XMVectorGetX(dot));
        len *= std::clamp(XMVectorGetX(dot), 0.0f, 1.0f);
        length = len;
        return TRUE;
    }
    return FALSE;
}

//�p����n�ʂ̖@���ɓY�킹��
void PlayerBase::PostureGroundFollow(int hStageModel)
{
    //rotate_���g�킸�ɉ�]
    //��]�v�Z��ς���(��������Ȃ��Ɖ�]���Ȃ�)
    transform_.SetRotateMode(TRANS_NONROTATE);

    //�e���ɑ΂���x�N�g�������߂�
    XMMATRIX rotateX, rotateY, rotateZ;
    rotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    rotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    rotateZ = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

    //��]�s������߂�
    XMMATRIX m = rotateZ * rotateX * rotateY;

    //y���̃x�N�g�����擾
    XMFLOAT3 fUpVec = { 0, size.y, 0 };

    //XMFLOAT3�ɕϊ�
    XMVECTOR vUpVec = XMLoadFloat3(&fUpVec);

    //vUpVec���s�񂍂ŕό`
    vUpVec = XMVector3TransformCoord(vUpVec, m);

    //���ݒn��XMVECTOR�^�ɕϊ�����
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //fBoneDirVec��vUpVec�̋t�x�N�g��������
    XMFLOAT3 fBoneDirVec;
    XMStoreFloat3(&fBoneDirVec, -vUpVec);

    RayCastData GroundData;                               //�V�����̈ʒu���烌�C���΂��āA�S�[���ƂԂ��邩�𒲂ׂ�
    GroundData.start = transform_.position_;              //���C�̔��ˈʒu
    GroundData.dir = fBoneDirVec;                         //���C�̕���
    Model::RayCast(hStageModel, &GroundData);             //���C�𔭎�

    XMVECTOR nor = XMVector3Normalize(GroundData.normal); //�@��
    XMVECTOR up = XMVector3Normalize(vUpVec);             //��x�N�g��

    //�O�ς�0���Ƃ܂����̂Ŋm�F
    if (XMVectorGetX(nor) != XMVectorGetX(up) || XMVectorGetY(nor) != XMVectorGetY(up) || XMVectorGetZ(nor) != XMVectorGetZ(up))
    {
        //�x�N�g���Ԃ̃��W�A���p�x���߂�
        float dot = XMVectorGetX(XMVector3Dot(XMVector3Normalize(nor), XMVector3Normalize(up)));

        //�O�ϋ��߂�
        XMVECTOR cross = XMVector3Cross(nor, up);

        if (dot >= -1 && dot != 0 && dot <= 1)
        {
            XMMATRIX y;
            y = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
            //��]�s�񋁂߂�
            transform_.changeMatRotate_ = y * XMMatrixRotationAxis(cross, -acos(dot));
        }
    }
    else
    {
        XMMATRIX x, y, z;
        x = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
        y = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        z = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));
        XMMATRIX mat = z * x * y;
        transform_.changeMatRotate_ = mat;
    }
}

//���̃I�u�W�F�N�g�ɃJ�������Z�b�g����
void PlayerBase::SetCameraController(XMFLOAT3 shiftPos)
{
    //���̃I�u�W�F�N�g�ŃJ�������䂷��Ȃ�
    if (state_.isCamControll)
    {
        //���`��Ԃ��g�p���ăJ�����̈ʒu��ύX
        pController->SetCameraLerpPos(transform_.position_, ATTENUATION_RATIO);
    }
}

//�n�ʂɂ߂荞�񂾎��̏���
void PlayerBase::RevertProcess(int hStageModel)
{
    //�n�ʂɂ��Ă��Ȃ����Ƃɂ���
    state_.isGround = false;

    //�{�[���̈ʒu���擾
    const std::string vertexName[8] = {
        "Vertex_Hight_Right_Front",
        "Vertex_Hight_Right_Back",
        "Vertex_Hight_Left_Front",
        "Vertex_Hight_Left_Back",
        "Vertex_Low_Right_Front",
        "Vertex_Low_Right_Back",
        "Vertex_Low_Left_Front",
        "Vertex_Low_Left_Back"
    };

    const int VERMAX = COUNTOF(vertexName);
    XMFLOAT3 vertexBonePos[VERMAX];

    //�e���_�̈ʒu�𒲂ׂ�
    for (int i = 0; i < VERMAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
    }
     
    //���C�����������΂�
    //���C�����[�v

    XMMATRIX x, y, z;
    x = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    y = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    z = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));
    XMMATRIX mat = z * x * y;

   //�^���ւ̃x�N�g����p��
    XMVECTOR vec[NUM_OF_THROW] =
    {
        XMVECTOR{0,-1,0,0},//��
        XMVECTOR{0, 1,0,0}, //��
        XMVECTOR{1,0,0,0 }, //�E
        XMVECTOR{-1,0,0,0},//��
        XMVECTOR{0,0,-1,0},//��O
        XMVECTOR{0,0, 1,0}, //��
    };

    XMFLOAT3 fVec[NUM_OF_THROW];
    for (int i = 0; i < NUM_OF_THROW; i++)
    {
        XMFLOAT3 tmp;
        XMStoreFloat3(&tmp, XMVector3TransformCoord(vec[i], mat));
        fVec[i] = tmp;
    }

    //���C�̃X�^�[�g�n�_
    XMFLOAT3 pos = transform_.position_;

    for (int i = 0; i < NUM_OF_THROW; i++)
    {
        float length;
        //�Փ˂��Ă��邩���ׂ�
        if (CheckIfCollided(hStageModel, fVec[i], pos, length))
        {
            //vec��XMVECTOR�ɕϊ�
            XMVECTOR vector = XMLoadFloat3(&fVec[i]);

            //�t�x�N�g���ɂ���
            vector *= -1;

            //���K��
            vector = XMVector3Normalize(vector);

            //�x�N�g����length�̒����ɂ���
            vector *= length;

            //���ݒn��XMVECTOR�^�ɂ���
            XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

            //���ݒn��vector�̕��ړ�����
            vPos += vector;

            //���ݒn��XMFLOAT3�^�ɂ���
            XMStoreFloat3(&transform_.position_, vPos);

            //�n�ʂɂ��Ă���ꍇ�ɂ�鏈��
            if(i == 0)
            {
                //�n�ʂɂ��Ă���
                state_.isGround = true;
                gravity = 0;
            }
        }
    }  
}

