#include "Ball.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1),fMove(), isPrevRayHit(true),count(0)
{
}

//�f�X�g���N�^
Ball::~Ball()
{
}

//������
void Ball::Initialize()
{
    hModel_ = Model::Load("Ball.fbx");
    assert(hModel_ >= 0); 

    //�����蔻���ǉ�
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.0f);
    AddCollider(collision);

    vMoved = {0,0,0,0};
    prevPos = transform_.position_;
}

//�X�V
void Ball::Update()
{
    Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾

    RayCastData posLowData;                    
    posLowData.start = transform_.position_;   //���C�̕���
    posLowData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &posLowData); //���C�𔭎�

    //RayCastData posRightData;
    //posRightData.start = transform_.position_;   //���C�̕���
    //posRightData.dir = XMFLOAT3(1, 0, 0);       //���C�̕���
    //Model::RayCast(hGroundModel, &posRightData); //���C�𔭎�

    //RayCastData posLeftData;
    //posLeftData.start = transform_.position_;   //���C�̕���
    //posLeftData.dir = XMFLOAT3(-1, 0, 0);       //���C�̕���
    //Model::RayCast(hGroundModel, &posLeftData); //���C�𔭎�

    //RayCastData posFrontData;
    //posFrontData.start = transform_.position_;   //���C�̕���
    //posFrontData.dir = XMFLOAT3(0, 0, -1);       //���C�̕���
    //Model::RayCast(hGroundModel, &posFrontData); //���C�𔭎�

    //RayCastData posBackData;
    //posBackData.start = transform_.position_;   //���C�̕���
    //posBackData.dir = XMFLOAT3(0, 0, 1);       //���C�̕���
    //Model::RayCast(hGroundModel, &posBackData); //���C�𔭎�

    transform_.position_ = Math::Float3Add(transform_.position_, fMove);
    //�������ɒn�ʂ���������
    if (posLowData.hit && posLowData.dist - BALL_SIZE > accel)
    {
        //�ڒn�t���O���U�ɂ���
        isGround = false;

        //�d��
        if (SPEED_LIMIT >= accel)
        {
            accel += FALL_SPEED;
            transform_.position_.y -= accel;
        }
        else
        {
            transform_.position_.y -= SPEED_LIMIT;
        }
    }
    else if(isPrevRayHit) //�������ɒn�ʂ��Ȃ�������
    {
        if (++count >= 5)
        {
            KillMe();
        }
        accel = 0.0f;
        transform_.position_.y -= posLowData.dist - BALL_SIZE;
        //�ڒn�t���O��^�ɂ���
        isGround = true;
    }

   isPrevRayHit = posLowData.hit;

   //if (posRightData.hit && posRightData.dist < BALL_SIZE)
   //{
   //    fMove.x *= -1;
   //}
   //if (posLeftData.hit && posLeftData.dist < BALL_SIZE)
   //{
   //    fMove.x *= -1;
   //}
   //if (posFrontData.hit && posFrontData.dist < BALL_SIZE)
   //{
   //    fMove.z *= -1;
   //}
   //if (posBackData.hit && posBackData.dist < BALL_SIZE)
   //{
   //    fMove.z *= -1;
   //}

   XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
   XMVECTOR vPrevPos = XMLoadFloat3(&prevPos);
   vMoved = vPos - vPrevPos;
   SetMoved(vMoved);

   prevPos = transform_.position_;

}

//�`��
void Ball::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Ball::Release()
{
}

void Ball::SetMove(XMFLOAT3 move)
{
    fMove = move;
}

void Ball::SetPosition(XMFLOAT3 pos)
{
    transform_.position_ = pos;
}
