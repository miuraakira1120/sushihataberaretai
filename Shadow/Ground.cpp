#include "Ground.h"
#include "Engine/Model.h"

//コンストラクタ
Ground::Ground(GameObject* parent)
    :GameObject(parent, "Ground")
{
}

//デストラクタ
Ground::~Ground()
{
}

//初期化
void Ground::Initialize()
{
    hModel_ = Model::Load("Ground.fbx");
    transform_.position_.y = -3.0f;
}

//更新
void Ground::Update()
{
}

//描画
void Ground::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Ground::Release()
{
}