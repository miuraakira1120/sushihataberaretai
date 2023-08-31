#include "Neta.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

namespace
{
    const float FALL_SPEED_LIMIT = 0.7f;    //�����̑��x���E 
    const float JUMP_POWER = 0.8f;    //�������x
    const float FALL_SPEED = 0.02f;   //������X�s�[�h
}

//�R���X�g���N�^
Neta::Neta(GameObject* parent, const std::string& name, const std::string& pathFilename)
	:GameObject(parent, name, pathFilename), hModel_(-1), gravity(0), pPlayer(nullptr)
{
    this->SetTag("neta");
}

//�`��
void Neta::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�Z�b�g�A�b�v����֐�
void Neta::SetUp()
{
	//���f�������[�h
	hModel_ = Model::Load(pathName_);
	assert(hModel_ >= 0);

    //�����ʒu�̐ݒ�
    transform_.position_.y = PLAYER_SIZE.y + NETA_SIZE.y;

    //PlayerBase�^��Player�̃|�C���^
    pPlayer = (PlayerBase*)GetParent();
}

//�e�̐e���猩���ʒu�����
XMFLOAT3 Neta::GetParentPos()
{
	return Math::Float3Add(GetParent()->GetPosition(), transform_.position_);
}

//�������Z
void Neta::PhysicalOperation()
{
}

//�������o
void Neta::LandingStaging()
{
}

//�d�͂̏���
void Neta::Gravity()
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

//���N���X�Őݒ肷��X�V(Update�̑O�ɌĂ�)
void Neta::PriUpdate()
{
}
