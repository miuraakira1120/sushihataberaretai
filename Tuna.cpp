#include "Tuna.h"
#include "Player.h"
#include "Engine/Input.h"

Tuna::Tuna(GameObject* parent, std::string pathName)
	:Neta(parent, "Tuna", pathName), accumulateTime(0.0f), isSkill(false), skillTime(0), accel(0), accelFlag(false)
{
	transform_.position_.y = PLAYER_SIZE.y + MAGURO_SIZE.y;
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
		//アクティブスキルキーを押していたら
		if (Input::IsKey(DIK_E))
		{
			//最大までためていなかったら
			if (ACCUMULATE_MAX > accumulateTime)
			{
				accumulateTime += ACCELERATION_RATE;
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
		//プレイヤーの操作を不可能にする
		//スキル発動

		//ためた時間に応じた速さまで加速
		if (!accelFlag)
		{
			if (accumulateTime > accel)
			{
				//加速度を計算
				accel += ACCELERATION_RATE;

				//プレイヤーを移動させる
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
			
		}		
	}
	
}
