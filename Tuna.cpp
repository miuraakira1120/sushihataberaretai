#include "Tuna.h"
#include "Player.h"
#include "Engine/Input.h"
#include "VFX.h"

Tuna::Tuna(GameObject* parent, std::string pathName)
	:Neta(parent, "Tuna", pathName), accumulateTime(0.0f), isSkill(false), skillTime(0), accel(0.0f), accelFlag(false), isFullPower(false)
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
				//エフェクト
				EmitterData chargeEffect = VFX::SetEmitterDataCharge();
				chargeEffect.color = VFX::RED;
				chargeEffect.size = XMFLOAT2(0.1f * accumulateTime, 0.1f * accumulateTime);
				chargeEffect.position = GetParent()->GetPosition();
				VFX::Start(chargeEffect);

				accumulateTime += ACCELERATION_RATE;
			}
			else
			{
				//エフェクト
				EmitterData chargeEffect = VFX::SetEmitterDataCharge();
				chargeEffect.textureFileName = "PaticleAssets/flashA_Y.png";
				chargeEffect.color = VFX::BLUE;
				chargeEffect.size = XMFLOAT2(0.2 * accumulateTime, 0.2 * accumulateTime);
				chargeEffect.position = GetParent()->GetPosition();
				VFX::Start(chargeEffect);

				//スキルを最大まで溜めた
				isFullPower = true;
			}
		}
		//アクティブスキルキーを離したら
		if (Input::IsKeyUp(DIK_E))
		{
			//スキルを発動
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
			//エフェクトの設定
			EmitterData chargeEffect = VFX::SetEmitterDataCharge();
			chargeEffect.size = XMFLOAT2(0.2 * accel, 0.2 * accel);
			chargeEffect.position = GetParent()->GetPosition();
			//青色に
			chargeEffect.color = VFX::BLUE;
			if (isFullPower)
			{
				//青色に
				chargeEffect.textureFileName = "PaticleAssets/flashA_Y.png";
				chargeEffect.color = VFX::BLUE;
			}
			else
			{
				//赤色に
				chargeEffect.color = VFX::RED;
			}			
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
			isFullPower	   = false;
			pPlayer->SetCanMove(true);
		}		
	}
}
