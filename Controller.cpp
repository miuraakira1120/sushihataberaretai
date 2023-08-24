#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Syari.h"
#include "Maguro.h"
#include "Engine/Direct3D.h"
#include "Engine/Image.h"
#include "GameManager.h"

namespace
{
    const float CAMERA_SPEED = 3.0f;
    const float DOWN_ANGLE_LIMIT = 20.0f;
    const float UP_ANGLE_LIMIT = -10.0f;
    const float PAD_SPEED = 3.0f;
    const float CAMERA_SIZE = 0.1f;//�J�����̓����蔻��̑傫��

    const float MOVED_FOV = XM_PIDIV4 * 1.1f; // �v���C���[���ړ����Ă��鎞��FoV
    const float FOV = XM_PIDIV4; // �v���C���[�������~�܂��Ă��鎞��FoV
}

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller"), cameraAngle(0.0f, 4.0f, 20.0f),cameraDistance(15.0f)
{
}

//�f�X�g���N�^
Controller::~Controller()
{
}

//������
void Controller::Initialize()
{
}

//�X�V
void Controller::Update()
{
    //�J�����̏œ_��Controller�I�u�W�F�N�g��
    //���L�[�ŉ�]
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_S) && transform_.rotate_.x > UP_ANGLE_LIMIT)
    {
        transform_.rotate_.x -= CAMERA_SPEED; 
    }
    if (Input::IsKey(DIK_W) && transform_.rotate_.x < DOWN_ANGLE_LIMIT)
    {
        transform_.rotate_.x += CAMERA_SPEED; 
    }

    XMFLOAT3 stickR = { Input::GetPadStickR().y, Input::GetPadStickR().x, 0 };
    transform_.rotate_ = Math::Float3Add(Math::Float3Mul( stickR, PAD_SPEED, PAD_SPEED, PAD_SPEED), transform_.rotate_);
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}

XMFLOAT3 Controller::GetPosition()
{
    return transform_.position_;
}

XMFLOAT3 Controller::GetRotate()
{
    return transform_.rotate_;
}

//�R���g���[���[�ŃJ��������]�֐�
void Controller::SetCameraPos(XMFLOAT3 position)
{
    //�ŏI�I�ȃJ�����̈ʒu
    XMFLOAT3 camPos;

    //�J�����̈ʒu�̐ݒ�
    //������ݒ�
    XMVECTOR vCam = XMVectorSet(cameraAngle.x, cameraAngle.y, cameraAngle.z, 0.0f);

    //�R���g���[���[�̊p�x�ɂ���ăJ�����̈ʒu��ς���
    XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vCam = XMVector3TransformCoord(vCam, mRotate);

    //���K�����ăJ�����̈ʒu�𒲐�
    vCam = XMVector3Normalize(vCam);

    //�J�����̃x�N�g��
    XMFLOAT3 camVec;
    XMStoreFloat3(&camVec, vCam);

    //���ݒn��XMVECTOR�ɕϊ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //�X�e�[�W�̃��f���ԍ����擾
    StageBase* pStage = GameManager::GetNowStage();    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();       //���f���ԍ����擾

    //���C���΂��ăR���g���[���[�ƃJ�����̊ԂɃX�e�[�W�̃��f�������邩�m�F
    RayCastData data;
    data.start = transform_.position_;   //���C�̔��ˈʒu
    data.dir = camVec;                   //���C�̕���
    Model::RayCast(hGroundModel, &data); //���C�𔭎�

    //���C����Q���ɓ���������
    if (data.hit)
    {
        //�J��������Փ˓_�܂ł̋���
        XMFLOAT3 fDist = Math::Float3Sub(data.pos, transform_.position_);
        XMVECTOR vLength = XMLoadFloat3(&fDist);
        vLength = XMVector3Length(vLength);
        float length = XMVectorGetX(vLength) - CAMERA_SIZE;

        //�����I�ɂԂ����Ă�����
        if (length <= cameraDistance)
        {
            //�J�����̋������v�Z
            vCam *= length;

            //�ŏI�I�ȃJ�����̈ʒu
            XMStoreFloat3(&camPos, vCam + vPos);
        }
        else
        {
            //�J�����̋������v�Z
            vCam *= cameraDistance;

            //�ŏI�I�ȃJ�����̈ʒu
            XMStoreFloat3(&camPos, vCam + vPos);
        }
    }
    else
    {
        //�J�����̋������v�Z
        vCam *= cameraDistance;
        //�ŏI�I�ȃJ�����̈ʒu
        XMStoreFloat3(&camPos, vCam + vPos);

        //�J�����̈ʒu��ς���
        Camera::SetPosition(camPos);
    }

    Camera::SetPosition(camPos);
    transform_.position_ = position;

    //�J�����̏œ_��ς���
    Camera::SetTarget(transform_.position_);

    
}

//���[�v���g�p���ăR���g���[���[�ŃJ��������]������֐�
void Controller::SetCameraLerpPos(XMFLOAT3 position, float attenRate)
{
    //XMVECTOR�ɕϊ�
    //���B����ׂ��ʒu
    XMVECTOR vReachPosition = XMLoadFloat3(&position);

    //���ݒn
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //Lerp����
    XMVECTOR vCamPos = XMVectorLerp(vPos, vReachPosition, attenRate);

    //XMFLOAT3�ɕϊ�
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vCamPos);

    //�R���g���[���[�ŃJ��������]
    SetCameraPos(camPos);
}

//���[�v��FoV�g�p���ăR���g���[���[�ŃJ��������]������֐�
void Controller::ChangeFovMove(bool isMoved)
{
    //FoV�̐ݒ�
    float fov = isMoved ? MOVED_FOV : FOV;
    Camera::SetFOV(fov);
}

//�J�����̈ʒu���ǂƏՓ˂��Ă��邩��Ԃ�
bool Controller::IsCameraCollision()
{
    return false;
}

//�J�����̋����̃Z�b�^�[
void Controller::SetCameraDistance(float distance)
{
    cameraDistance = distance;
}

//�J�����̋����̃Q�b�^�[
float Controller::GetCameraDistance()
{
    return cameraDistance;
}
