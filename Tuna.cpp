#include "Tuna.h"
#include "Player.h"
#include "Engine/Input.h"

Tuna::Tuna(GameObject* parent, std::string pathName)
	:Neta(parent, "Tuna", pathName), accumulateTime(0.0f), isSkill(false), skillTime(0), accel(0), accelFlag(false)
{
	transform_.position_.y = PLAYER_SIZE.y + MAGURO_SIZE.y;
}

//�X�V
void Tuna::Update()
{
	Skill();
	//�d�͂̏���
	//Gravity();
}

//�ŗL�̃X�L��
void Tuna::Skill()
{
	//�X�L���𔭓����Ă��Ȃ�������
	if (isSkill == false)
	{
		//�A�N�e�B�u�X�L���L�[�������Ă�����
		if (Input::IsKey(DIK_E))
		{
			//�ő�܂ł��߂Ă��Ȃ�������
			if (ACCUMULATE_MAX > accumulateTime)
			{
				accumulateTime += ACCELERATION_RATE;
			}
		}
		//�A�N�e�B�u�X�L���L�[�𗣂�����
		if (Input::IsKeyUp(DIK_E))
		{
			isSkill = true;
		}
	}
	//�X�L���𔭓����Ă�����
	//���߂Ă������Ԃɉ����ēːi����
	else
	{
		//�v���C���[�̑����s�\�ɂ���
		//�X�L������

		//���߂����Ԃɉ����������܂ŉ���
		if (!accelFlag)
		{
			if (accumulateTime > accel)
			{
				//�����x���v�Z
				accel += ACCELERATION_RATE;

				//�v���C���[���ړ�������
				Player* pPlayer = (Player*)GetParent();
				pPlayer->Move(accel, false);
			}
			else
			{
				accelFlag = true;
			}
		}
		else
		{
			accel -= DECELERATION_RATE;
		}
		
		//�ːi���I�������
		if (accel < 0)
		{
			//���߂Ă������Ԃ����Z�b�g����
			//�v���C���[�̑�����\�ɂ���
			accumulateTime = 0;
			accel		   = 0;
			skillTime	   = 0;
			accelFlag	   = false;
			isSkill		   = false;
			
		}		
	}
	
}
