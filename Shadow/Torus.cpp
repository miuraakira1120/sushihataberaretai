#include "Torus.h"
#include "Engine/Model.h"

//コンストラクタ
Torus::Torus(GameObject* parent)
    :GameObject(parent, "Torus")
{
}

//デストラクタ
Torus::~Torus()
{
}

//初期化
void Torus::Initialize()
{
    hModel_ = Model::Load("Torus.fbx");
    transform_.position_.y = 2.0f;
        
}

//更新
void Torus::Update()
{
    static int time = 0;
    time++;

    transform_.position_.x = sin((float)time / 50)*5;
    transform_.rotate_.z = time * 5;


}

//描画
void Torus::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Torus::Release()
{
}