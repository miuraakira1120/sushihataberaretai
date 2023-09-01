#include "Tuna.h"
#include "Player.h"
#include "Engine/Input.h"
#include "VFX.h"

Tuna::Tuna(GameObject* parent, std::string pathName)
	:Neta(parent, "Tuna", pathName), accumulateTime(0.0f), isSkill(false), skillTime(0), accel(0.0f), accelFlag(false)
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
				EmitterData chargeEffect;
				chargeEffect.textureFileName = "PaticleAssets/CloudA.png";
				chargeEffect.delay = 0;
				chargeEffect.number = 80;
				chargeEffect.lifeTime = 20;
				chargeEffect.direction = XMFLOAT3(0, 1, 0);
				chargeEffect.directionRnd = XMFLOAT3(90, 90, 90);
				chargeEffect.speed = 0.1f;
				chargeEffect.speedRnd = 0.8;
				chargeEffect.size = XMFLOAT2(0.1f * accumulateTime, 0.1f * accumulateTime);
				chargeEffect.sizeRnd = XMFLOAT2(0.4, 0.4);
				chargeEffect.scale = XMFLOAT2(1.05, 1.05);
				chargeEffect.color = XMFLOAT4(1, 1, 0.1, 1);
				chargeEffect.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);

				chargeEffect.position = GetParent()->GetPosition();
				VFX::Start(chargeEffect);
				accumulateTime += ACCELERATION_RATE;
			}
			else
			{
				EmitterData chargeEffect;
				chargeEffect.textureFileName = "PaticleAssets/flashA_Y.png";
				chargeEffect.delay = 0;
				chargeEffect.number = 80;
				chargeEffect.lifeTime = 20;
				chargeEffect.direction = XMFLOAT3(0, 1, 0);
				chargeEffect.directionRnd = XMFLOAT3(90, 90, 90);
				chargeEffect.speed = 0.1f;
				chargeEffect.speedRnd = 0.8;
				chargeEffect.size = XMFLOAT2(0.2 * accumulateTime, 0.2 * accumulateTime);
				chargeEffect.sizeRnd = XMFLOAT2(0.4, 0.4);
				chargeEffect.scale = XMFLOAT2(1.05, 1.05);
				chargeEffect.color = XMFLOAT4(0.1, 1, 1, 1);
				chargeEffect.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);

				chargeEffect.position = GetParent()->GetPosition();
				VFX::Start(chargeEffect);
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
			EmitterData chargeEffect;
			chargeEffect.textureFileName = "PaticleAssets/flashA_Y.png";
			chargeEffect.delay = 0;
			chargeEffect.number = 80;
			chargeEffect.lifeTime = 20;
			chargeEffect.direction = XMFLOAT3(0, 1, 0);
			chargeEffect.directionRnd = XMFLOAT3(90, 90, 90);
			chargeEffect.speed = 0.1f;
			chargeEffect.speedRnd = 0.8;
			chargeEffect.size = XMFLOAT2(0.2 * accel, 0.2 * accel);
			chargeEffect.sizeRnd = XMFLOAT2(0.4, 0.4);
			chargeEffect.scale = XMFLOAT2(1.05, 1.05);
			chargeEffect.color = XMFLOAT4(0.1, 1, 1, 1);
			chargeEffect.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);

			chargeEffect.position = GetParent()->GetPosition();
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
			pPlayer->SetCanMove(true);
		}		
	}
}
