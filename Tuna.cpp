#include "Tuna.h"
#include "Player.h"
#include "Engine/Input.h"
#include "VFX.h"

Tuna::Tuna(GameObject* parent, std::string pathName)
	:Neta(parent, "Tuna", pathName), accumulateTime(0.0f), isSkill(false), skillTime(0), accel(0.0f), accelFlag(false)
{
	//transform_.position_.y = PLAYER_SIZE.y + MAGURO_SIZE.y;
}

//更新
void Tuna::Update()
{
	Skill();
	//重力の処理
	//Gravity();
}

//固有のスキル
void Tuna::Skill()
{
	//スキルを発動していなかったら
	if (isSkill == false)
	{
		//アクティブスキルキーを押していたら(突進をためていたら)
		if (Input::IsKey(DIK_E))
		{
			//プレイヤーの操作を不可能にする
			pPlayer->SetCanMove(false);

			//最大までためていなかったら
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
		//アクティブスキルキーを離したら
		if (Input::IsKeyUp(DIK_E))
		{
			isSkill = true;
		}
	}
	//スキルを発動していたら
	//ためていた時間に応じて突進する
	else
	{
		pPlayer->SetShouldTakeGravity(false);
		//スキル発動
		//ためた時間に応じた速さまで加速
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
			//プレイヤーを移動させる
			Player* pPlayer = (Player*)GetParent();
			pPlayer->Move(accel, false);
		}
		
		//速度が一定まで落ちたら
		if (accel < CONSTANT_SPEED)
		{
			//重力を受けるようにする
			pPlayer->SetShouldTakeGravity(true);
		}
		//突進が終わったら
		if (accel < 0)
		{
			//ためていた時間をリセットする
			//プレイヤーの操作を可能にする
			accumulateTime = 0;
			accel		   = 0;
			skillTime	   = 0;
			accelFlag	   = false;
			isSkill		   = false;
			pPlayer->SetCanMove(true);
		}		
	}
}
