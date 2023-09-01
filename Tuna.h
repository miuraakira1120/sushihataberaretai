#pragma once
#include "Neta.h"
#include "Engine/GameObject.h"

class Tuna : public Neta
{
	//スキルをためる時間の最大値
	const float ACCUMULATE_MAX = 4.0f;

	//スキルの発動時間
	const int SKILL_TIME_ACCEL = 30;
	const int SKILL_TIME_KEEP  = 45;
	const int SKILL_TIME_DECEL = 35;
	const int SKILL_TIME = SKILL_TIME_ACCEL + SKILL_TIME_KEEP + SKILL_TIME_DECEL;

	//一定以下の速度になったら落ちる
	const float CONSTANT_SPEED = 2.0f;

	//加速率
	const float ACCELERATION_RATE = 0.02f;

	//減速率
	const float DECELERATION_RATE = 0.05f;

	//現在ためているスキルの時間
	float accumulateTime;

	//スキル発動中に使う時間
	int skillTime;

	//スキルを発動しているかどうか
	bool isSkill;

	//スキル使用中の加速度
	float accel;

	//スキル使用中に使うフラグ
	bool accelFlag;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	/// <param name="pathName">モデルのファイル名</param>
	Tuna(GameObject* parent, std::string pathName);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 固有のスキル
	/// マグロ:突進
	/// </summary>
	virtual void Skill() override;
};

