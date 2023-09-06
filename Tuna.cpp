#include "Tuna.h"
#include "Player.h"
#include "Engine/Input.h"
#include "VFX.h"

Tuna::Tuna(GameObject* parent, std::string pathName)
	:Neta(parent, "Tuna", pathName), accumulateTime(0.0f), isSkill(false), skillTime(0), accel(0.0f), accelFlag(false), isFullPower(false)
{
	//transform_.position_.y = PLAYER_SIZE.y + MAGURO_SIZE.y;
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
		//�A�N�e�B�u�X�L���L�[�������Ă�����(�ːi�����߂Ă�����)
		if (Input::IsKey(DIK_E))
		{
			//�v���C���[�̑����s�\�ɂ���
			pPlayer->SetCanMove(false);

			//�ő�܂ł��߂Ă��Ȃ�������
			if (ACCUMULATE_MAX > accumulateTime)
			{
				//�G�t�F�N�g
				EmitterData chargeEffect = VFX::SetEmitterDataCharge();
				chargeEffect.color = VFX::RED;
				chargeEffect.size = XMFLOAT2(0.1f * accumulateTime, 0.1f * accumulateTime);
				chargeEffect.position = GetParent()->GetPosition();
				VFX::Start(chargeEffect);

				accumulateTime += ACCELERATION_RATE;
			}
			else
			{
				//�G�t�F�N�g
				EmitterData chargeEffect = VFX::SetEmitterDataCharge();
				chargeEffect.textureFileName = "PaticleAssets/flashA_Y.png";
				chargeEffect.color = VFX::BLUE;
				chargeEffect.size = XMFLOAT2(0.2 * accumulateTime, 0.2 * accumulateTime);
				chargeEffect.position = GetParent()->GetPosition();
				VFX::Start(chargeEffect);

				//�X�L�����ő�܂ŗ��߂�
				isFullPower = true;
			}
		}
		//�A�N�e�B�u�X�L���L�[�𗣂�����
		if (Input::IsKeyUp(DIK_E))
		{
			//�X�L���𔭓�
			isSkill = true;
		}
	}
	//�X�L���𔭓����Ă�����
	//���߂Ă������Ԃɉ����ēːi����
	else
	{
		pPlayer->SetShouldTakeGravity(false);
		//�X�L������
		//���߂����Ԃɉ����������܂ŉ���
		if (!accelFlag)
		{
			accel = accumulateTime;
			accelFlag = true;
		}
		else
		{
			//�G�t�F�N�g�̐ݒ�
			EmitterData chargeEffect = VFX::SetEmitterDataCharge();
			chargeEffect.size = XMFLOAT2(0.2 * accel, 0.2 * accel);
			chargeEffect.position = GetParent()->GetPosition();
			//�F��
			chargeEffect.color = VFX::BLUE;
			if (isFullPower)
			{
				//�F��
				chargeEffect.textureFileName = "PaticleAssets/flashA_Y.png";
				chargeEffect.color = VFX::BLUE;
			}
			else
			{
				//�ԐF��
				chargeEffect.color = VFX::RED;
			}			
			VFX::Start(chargeEffect);

			accel -= DECELERATION_RATE;
			//�v���C���[���ړ�������
			Player* pPlayer = (Player*)GetParent();
			pPlayer->Move(accel, false);
		}
		
		//���x�����܂ŗ�������
		if (accel < CONSTANT_SPEED)
		{
			//�d�͂��󂯂�悤�ɂ���
			pPlayer->SetShouldTakeGravity(true);
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
			isFullPower	   = false;
			pPlayer->SetCanMove(true);
		}		
	}
}
