#include "Neta.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

namespace
{
    const float FALL_SPEED_LIMIT = 0.7f;    //落下の速度限界 
    const float JUMP_POWER = 0.8f;    //跳躍速度
    const float FALL_SPEED = 0.02f;   //落ちるスピード
}

//コンストラクタ
Neta::Neta(GameObject* parent, const std::string& name, const std::string& pathFilename)
	:GameObject(parent, name, pathFilename), hModel_(-1), gravity(0)
{
}

//描画
void Neta::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//セットアップする関数
void Neta::SetUp()
{
	//モデルをロード
	hModel_ = Model::Load(pathName_);
	assert(hModel_ >= 0);

    //初期位置の設定
    transform_.position_.y = 0.5f + 0.25;
}

//親の親から見た位置を入手
XMFLOAT3 Neta::GetParentPos()
{
	return Math::Float3Add(GetParent()->GetPosition(), transform_.position_);
}

//物理演算
void Neta::PhysicalOperation()
{
}

//落下演出
void Neta::LandingStaging()
{
}

//重力の処理
void Neta::Gravity()
{
    //スピードの上限に達していなければ
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

//基底クラスで設定する更新(Updateの前に呼ぶ)
void Neta::PriUpdate()
{
}
